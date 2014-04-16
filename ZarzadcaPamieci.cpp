#include "ZarzadcaPamieci.h"
#include "definicjeWezlowXML.h"
#include "Parser\ParserDokumentXml.h"
#include "Aplikacja.h"
#include "LuaSkrypt.h"
#include "DllSkrypt.h"

namespace SpEx{
	ZarzadcaPamieci::ZarzadcaPamieci(){
		LuaSkrypt::Rejestruj(fabrykaSkryptow_);
		DllSkrypt::Rejestruj(fabrykaSkryptow_);
	}

	std::shared_ptr< Planeta > ZarzadcaPamieci::pobierzPlanete(const STyp::Identyfikator& identyfikator){
		auto planeta = planety_.find(identyfikator);
		if (planeta == planety_.end())
			return nullptr;
		if (!planeta->second.planeta_){
			wczytajUkladSloneczny(planeta->second.idUkladu_);
			return planety_[identyfikator].planeta_;
		}
		return planeta->second.planeta_;
	}

	std::shared_ptr< Planeta > ZarzadcaPamieci::pobierzIZarezerwujPlanete(const STyp::Identyfikator& identyfikator){
		auto planeta = planety_.find(identyfikator);
		if (planeta == planety_.end())
			return nullptr;
		if (!planeta->second.planeta_){
			wczytajUkladSloneczny(planeta->second.idUkladu_);
			planety_[identyfikator].wolna_ = false;
			return planety_[identyfikator].planeta_;
		}
		if (!planeta->second.wolna_)
			return false;
		planeta->second.wolna_ = false;
		return planeta->second.planeta_;
	}

	std::shared_ptr< Planeta > ZarzadcaPamieci::pobierzIZarezerwujPlanete(){
		auto planeta = std::find_if(planety_.begin(), planety_.end(), [](const std::pair< const STyp::Identyfikator, ObjPlaneta>& element)->bool{ return element.second.wolna_; });
		if (planeta == planety_.end())
			return nullptr;
		if (!planeta->second.planeta_){
			wczytajUkladSloneczny(planeta->second.idUkladu_);
			planety_[planeta->first].wolna_ = false;
			return planety_[planeta->first].planeta_;
		}
		planeta->second.wolna_ = false;
		return planeta->second.planeta_;
	}

	void ZarzadcaPamieci::anulujRezerwacjePlanety(const STyp::Identyfikator& identyfikator){
		auto planeta = planety_.find(identyfikator);
		if (planeta != planety_.end())
			planeta->second.wolna_ = true;
	}
	
	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelKonfiguracyjnyMaszynyStanow()const{
		return dokumentMaszynyStanow_->pobierzElement(nullptr);
	}

	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelKonfiguracyjnyOknaGry()const{
		return dokumentOknaGry_->pobierzElement(nullptr);
	}

	XmlBO::ElementWezla ZarzadcaPamieci::tworzWezelGry(){
		dokumentGry_ = std::make_shared<SPar::ParserDokumentXml>();
		return dokumentGry_->tworzElement(WEZEL_XML_ROOT);
	}

	bool ZarzadcaPamieci::zapiszWezelGry(){
		return dokumentGry_->zapisz(adresPlikuGry_.c_str());
	}

	XmlBO::ElementWezla ZarzadcaPamieci::otworzWezelGry(){
		dokumentGry_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentGry_->odczytaj(adresPlikuGry_.c_str())){
			auto wezel = tworzWezelGry();
			auto gra = wezel->tworzElement(WEZEL_XML_GRA);
			zapiszWezelGry();
		}
		return dokumentGry_->pobierzElement(WEZEL_XML_ROOT);
	}

	void ZarzadcaPamieci::zaladujPliki( const UstawieniaAplikacji& ustawienia ){
		adresPlikuGry_ = ustawienia.pobierzAdresPlikuGry();
		folderPlikuUzytkownika_ = ustawienia.pobierzFolderPlikuUzytkownika();
		folderPlikuUkladu_ = ustawienia.pobierzFolderPlikuUkladu();

		dokumentMaszynyStanow_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentMaszynyStanow_->odczytaj(ustawienia.pobierzAdresPlikuStanow().c_str())){
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(),
				STyp::Tekst("B³ad odczytu pliku."),
				STyp::Tekst("Nie powiod³a siê operacja wczytywania danych z pliku: state.xml."));
		}
		dokumentOknaGry_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentOknaGry_->odczytaj(ustawienia.pobierzAdresPlikuOkien().c_str())){
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(),
				STyp::Tekst("B³ad odczytu pliku."),
				STyp::Tekst("Nie powiod³a siê operacja wczytywania danych z pliku: Menu.xml."));
		}
		
	}
	
	int ZarzadcaPamieci::pobierzIloscGalaktyk() const{
		return static_cast<int>(galaktyki_.size());
	}

	bool ZarzadcaPamieci::generujNowaGalaktyke(){
		auto galaktyka = generator_.generujGalaktyke();
		std::vector< STyp::Identyfikator> listaUkladow;
		for (int n = galaktyka->iloscUkladow_; n > 0; --n){
			auto uklad = generator_.generujUklad(galaktyka->pobierzIdentyfikator());
			std::vector< STyp::Identyfikator> listaPlanet;
			for (auto planeta : uklad->planety_){
				listaPlanet.push_back(planeta.first);
				struct ZarzadcaPamieci::ObjPlaneta nowaPlaneta = { uklad->pobierzIdentyfikator(), nullptr, true };
				planety_[planeta.first] = nowaPlaneta;
			}
			listaUkladow.push_back(uklad->pobierzIdentyfikator());
			struct ZarzadcaPamieci::ObjUklad nowyUklad = { galaktyka->pobierzIdentyfikator(), nullptr, listaPlanet };
			ukladySloneczne_[uklad->pobierzIdentyfikator()] = nowyUklad;
			zapiszUkladSloneczny(uklad);
		}
		struct ZarzadcaPamieci::ObjGalakatyka nowaGalaktyka = { nullptr, listaUkladow };
		galaktyki_[galaktyka->pobierzIdentyfikator()] = nowaGalaktyka;
		return true;
	}

	bool ZarzadcaPamieci::wczytajUkladSloneczny(const STyp::Identyfikator& identyfikator){
		SPar::ParserDokumentXml dokument;
		std::string plik = folderPlikuUkladu_.c_str();
		plik += identyfikator.napis();
		plik += ".xml";
		if (!dokument.odczytaj(plik.c_str()))
			return false;
		auto root = dokument.pobierzElement(nullptr);
		if (!root)
			return false;
		auto uklad = std::make_shared<UkladSloneczny>(STyp::Identyfikator(), STyp::Identyfikator());
		if (!uklad->odczytaj(root->pobierzElement(nullptr)))
			return false;
		ukladySloneczne_[uklad->pobierzIdentyfikator()].uklad_ = uklad;
		for (auto planeta : uklad->planety_){
			planety_[planeta.first].planeta_ = planeta.second;
		}
		return true;
	}

	bool ZarzadcaPamieci::zapiszUkladSloneczny(std::shared_ptr<UkladSloneczny> uklad) const{
		SPar::ParserDokumentXml dokument;
		std::string plik = folderPlikuUkladu_.c_str();
		plik += uklad->pobierzIdentyfikator().napis();
		plik += ".xml";

		auto root = dokument.tworzElement(WEZEL_XML_ROOT);
		if (!uklad->zapisz(root))
			return false;
		
		if (!dokument.zapisz(plik.c_str()))
			return false;
		return true;
	}

	bool ZarzadcaPamieci::zapisz(XmlBO::ElementWezla wezel) const{
		if (!wezel)
			return false;
		auto zarzadca = wezel->tworzElement(WEZEL_XML_ZARZADCA);
		if (!generator_.zapisz(zarzadca))
			return false;
		for (auto galaktyka : galaktyki_){
			auto wezelGalaktyka = zarzadca->tworzElement(WEZEL_XML_GALAKTYKA);
			wezelGalaktyka->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, galaktyka.first.napis().c_str());
			for (auto uklad : galaktyka.second.uklady_){
				auto wezelUklad = wezelGalaktyka->tworzElement(WEZEL_XML_UKLAD_SLONECZNY);
				wezelUklad->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, uklad.napis().c_str());
				auto ukladSloneczny = ukladySloneczne_.find(uklad);
				for (auto planeta : ukladSloneczny->second.planety_){
					auto wezelPlaneta = wezelUklad->tworzElement(WEZEL_XML_PLANETA);
					wezelPlaneta->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, planeta.napis().c_str());
					auto objPlaneta = planety_.find(planeta);
					if (objPlaneta != planety_.end())
						wezelPlaneta->tworzAtrybut(ATRYBUT_XML_WOLNA, objPlaneta->second.wolna_ ? "1" : "0");
					else
						wezelPlaneta->tworzAtrybut(ATRYBUT_XML_WOLNA, "1");
				}
				if (ukladSloneczny->second.uklad_){
					zapiszUkladSloneczny(ukladSloneczny->second.uklad_);
				}
			}
		}
		return true;
	}

	bool ZarzadcaPamieci::odczytaj(XmlBO::ElementWezla wezel){

		if (!generator_.odczytaj(XmlBO::ZnajdzWezel<STACKTHROW>(wezel, WEZEL_XML_GENERATOR_UKLADOW)))
			return false;
		XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_GALAKTYKA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla galaktyka)->bool{
			STyp::Identyfikator idGalaktyki;
			if (!XmlBO::WczytajAtrybut<STACKTHROW>(galaktyka, ATRYBUT_XML_IDENTYFIKATOR, idGalaktyki))
				return false;

			std::vector<STyp::Identyfikator> listUkladow;
			if(!XmlBO::ForEach<STACKTHROW>(galaktyka, WEZEL_XML_UKLAD_SLONECZNY, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla uklad)->bool{
				STyp::Identyfikator idUklad;
				if (!XmlBO::WczytajAtrybut<STACKTHROW>(uklad, ATRYBUT_XML_IDENTYFIKATOR, idUklad))
					return false;

				std::vector<STyp::Identyfikator> listPlanet;

				if(!XmlBO::ForEach<STACKTHROW>(uklad, WEZEL_XML_PLANETA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla planeta)->bool{
					STyp::Identyfikator idPlanety;
					int wolna;
					if (!XmlBO::WczytajAtrybut<STACKTHROW>(planeta, ATRYBUT_XML_IDENTYFIKATOR, idPlanety))
						return false;

					wolna = XmlBO::WczytajAtrybut<int>(planeta, ATRYBUT_XML_WOLNA, -1);
					if (wolna != 0 && wolna != 1)
						return false;

					listPlanet.push_back(idPlanety);
					struct ZarzadcaPamieci::ObjPlaneta nowaPlaneta = { idUklad, nullptr, true };
					planety_[idPlanety] = nowaPlaneta;
					return true;
				})))
					return false;

				listUkladow.push_back(idUklad);
				struct ZarzadcaPamieci::ObjUklad nowyUklad = { idGalaktyki, nullptr, listPlanet };
				ukladySloneczne_[idUklad] = nowyUklad;
				return true;
			})))
				return false;

			struct ZarzadcaPamieci::ObjGalakatyka nowaGalaktyka = { nullptr, listUkladow };
			galaktyki_[idGalaktyki] = nowaGalaktyka;
			return true;
		}));

		return true;
	}

	std::shared_ptr<SPar::ParserDokument> ZarzadcaPamieci::plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik) const{
		if (hash.empty() || nazwa.empty())
			return nullptr;
		std::string plik = folderPlikuUzytkownika_.c_str();
		plik.append(nazwa);
		plik.append("_.xml");
		auto dokument = std::make_shared<SPar::ParserDokumentXml>();
		if (dokument->odczytaj(plik.c_str())){
			if (hash != XmlBO::WczytajAtrybut(dokument->pobierzElement(nullptr), "hash", std::string()))
				return nullptr;
			if (tworzPlik){
				dokument = std::make_shared<SPar::ParserDokumentXml>();
				XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
				uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
				uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
				uzytkownik->tworzAtrybut(ATRYBUT_XML_PLANETA_AKTYWNA, STyp::Identyfikator(0).napis().c_str());
				dokument->zapisz(plik.c_str());
			}
		}
		else{
			if (!tworzPlik)
				return nullptr;
			XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
			uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_PLANETA_AKTYWNA, STyp::Identyfikator(0).napis().c_str());
			dokument->zapisz(plik.c_str());
		}
		nazwaPliku = plik;
		return dokument;
	}

	std::shared_ptr<Skrypt> ZarzadcaPamieci::TworzSkrypt(XmlBO::ElementWezla wezel){
		return fabrykaSkryptow_.Tworz(wezel);
	}

	std::shared_ptr<Skrypt> ZarzadcaPamieci::TworzSkrypt(const FabrykaSkryptow::Identyfikator& identyfikator, XmlBO::ElementWezla wezel){
		return fabrykaSkryptow_.Tworz(identyfikator,wezel);
	}
}
