#include "ZarzadcaPamieci.h"
#include "definicjeWezlowXML.h"
#include "Parser\ParserDokumentXml.h"
namespace SpEx{
	
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
	
	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelKonfiguracyjnyMaszynyStanow()const{
		return dokumentMaszynyStanow_->pobierzElement(nullptr);
	}

	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelKonfiguracyjnyOknaGry()const{
		return dokumentOknaGry_->pobierzElement(nullptr);
	}

	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelKonfiguracyjny()const{
		return dokumentKonfiguracyjny_->pobierzElement("SpaceGame");
	}

	XmlBO::ElementWezla ZarzadcaPamieci::tworzWezelGry(){
		dokumentGry_ = std::make_shared<SPar::ParserDokumentXml>();
		return dokumentGry_->tworzElement(WEZEL_XML_ROOT);
	}

	bool ZarzadcaPamieci::zapiszWezelGry(){
		return dokumentGry_->zapisz("save\\gra.xml");
	}

	XmlBO::ElementWezla ZarzadcaPamieci::otworzWezelGry(){
		dokumentGry_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentGry_->odczytaj("save\\gra.xml")){
			auto wezel = tworzWezelGry();
			auto gra = wezel->tworzElement(WEZEL_XML_GRA);
			zapiszWezelGry();
		}
		return dokumentGry_->pobierzElement(WEZEL_XML_ROOT);
	}

	void ZarzadcaPamieci::zaladujPliki(){
		dokumentMaszynyStanow_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentMaszynyStanow_->odczytaj("resource\\state.xml")){
			//TODO: Generuj wyj¹tek.
		}
		dokumentOknaGry_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentOknaGry_->odczytaj("resource\\Menu.xml")){
			//TODO: Generuj wyj¹tek.
		}
		dokumentKonfiguracyjny_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentKonfiguracyjny_->odczytaj(nazwaPlikuOpcji_.c_str())){
			//TODO: Generuj wyj¹tek.
		}
	}

	void ZarzadcaPamieci::ustawNazwePlikuOpcji(const std::string& plikOpcji){
		nazwaPlikuOpcji_ = plikOpcji;
	}

	const std::string& ZarzadcaPamieci::pobierzNazwePlikuOpcji() const{
		return nazwaPlikuOpcji_;
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
				struct ZarzadcaPamieci::ObjPlaneta nowaPlaneta = { uklad->pobierzIdentyfikator(), nullptr };
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
		std::string plik("save\\uklad\\");
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
		std::string plik("save\\uklad\\");
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
				}
				if (ukladSloneczny->second.uklad_){
					zapiszUkladSloneczny(ukladSloneczny->second.uklad_);
				}
			}
		}
		return true;
	}

	bool ZarzadcaPamieci::odczytaj(XmlBO::ElementWezla wezel){
		if (!wezel)
			return false;

		if (!generator_.odczytaj(XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_GENERATOR_UKLADOW)))
			return false;
		for (auto galaktyka = wezel->pobierzElement(WEZEL_XML_GALAKTYKA); galaktyka; galaktyka = galaktyka->pobierzNastepnyElement(WEZEL_XML_GALAKTYKA)){
			STyp::Identyfikator idGalaktyki;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(galaktyka, ATRYBUT_XML_IDENTYFIKATOR, idGalaktyki))
				return false;

			std::vector<STyp::Identyfikator> listUkladow;

			for (auto uklad = galaktyka->pobierzElement(WEZEL_XML_UKLAD_SLONECZNY); uklad; uklad = uklad->pobierzNastepnyElement(WEZEL_XML_UKLAD_SLONECZNY)){
				STyp::Identyfikator idUklad;
				if (!XmlBO::WczytajAtrybut<NOTHROW>(uklad, ATRYBUT_XML_IDENTYFIKATOR, idUklad))
					return false;

				std::vector<STyp::Identyfikator> listPlanet;

				for (auto planeta = uklad->pobierzElement(WEZEL_XML_PLANETA); planeta; planeta = planeta->pobierzNastepnyElement(WEZEL_XML_PLANETA)){
					STyp::Identyfikator idPlanety;
					if (!XmlBO::WczytajAtrybut<NOTHROW>(planeta, ATRYBUT_XML_IDENTYFIKATOR, idPlanety))
						return false;

					listPlanet.push_back(idPlanety);
					struct ZarzadcaPamieci::ObjPlaneta nowaPlaneta = { idUklad, nullptr };
					planety_[idPlanety] = nowaPlaneta;

				}
				listUkladow.push_back(idUklad);
				struct ZarzadcaPamieci::ObjUklad nowyUklad = { idGalaktyki, nullptr, listPlanet };
				ukladySloneczne_[idUklad] = nowyUklad;
			}

			struct ZarzadcaPamieci::ObjGalakatyka nowaGalaktyka = { nullptr, listUkladow };
			galaktyki_[idGalaktyki] = nowaGalaktyka;
		}

		return true;
	}

	std::shared_ptr<SPar::ParserDokument> ZarzadcaPamieci::plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik) const{
		if (hash.empty() || nazwa.empty())
			return nullptr;
		std::string plik("save\\");
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
				dokument->zapisz(plik.c_str());
			}
		}
		else{
			if (!tworzPlik)
				return nullptr;
			XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
			uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
			dokument->zapisz(plik.c_str());
		}
		nazwaPliku = plik;
		return dokument;
	}
}
