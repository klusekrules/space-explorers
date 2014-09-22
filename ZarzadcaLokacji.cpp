#include "ZarzadcaLokacji.h"
#include "Parser\ParserDokumentXml.h"
#include "Aplikacja.h"

namespace SpEx {

	std::shared_ptr< Planeta > ZarzadcaLokacji::pobierzPlanete(const STyp::Identyfikator& identyfikator){
		auto planeta = planety_.find(identyfikator);
		if (planeta == planety_.end())
			return nullptr;

		std::call_once(planeta->second.flaga_inicjalizacji_ukladu, &ZarzadcaLokacji::wczytajUkladSloneczny, this, planeta->second.idUkladu_);
		return planeta->second.planeta_;
	}

	std::shared_ptr< Planeta > ZarzadcaLokacji::pobierzIZarezerwujPlanete(const STyp::Identyfikator& identyfikator){
		auto planeta = planety_.find(identyfikator);
		if (planeta == planety_.end())
			return nullptr;
		bool val = true;
		if (!planeta->second.wolna_.compare_exchange_strong(val, false))
			return nullptr;
	
		std::call_once(planeta->second.flaga_inicjalizacji_ukladu, &ZarzadcaLokacji::wczytajUkladSloneczny, this, planeta->second.idUkladu_);
		return planeta->second.planeta_;
	}

	std::shared_ptr< Planeta > ZarzadcaLokacji::pobierzIZarezerwujPlanete(){
		auto planeta = std::find_if(planety_.begin(), planety_.end(), [](const std::pair< const STyp::Identyfikator, ObjPlaneta>& element)->bool{ return element.second.wolna_; });
		if (planeta == planety_.end())
			return nullptr;
		bool val = true;
		if (!planeta->second.wolna_.compare_exchange_strong(val, false))
			return nullptr;

		std::call_once(planeta->second.flaga_inicjalizacji_ukladu, &ZarzadcaLokacji::wczytajUkladSloneczny, this, planeta->second.idUkladu_);
		return planeta->second.planeta_;
	}

	void ZarzadcaLokacji::anulujRezerwacjePlanety(const STyp::Identyfikator& identyfikator){
		auto planeta = planety_.find(identyfikator);
		if (planeta != planety_.end()){
			bool val = false;
			planeta->second.wolna_.compare_exchange_strong(val, true);
		}
	}

	int ZarzadcaLokacji::pobierzIloscGalaktyk() const{
		return static_cast<int>(galaktyki_.size());
	}

	bool ZarzadcaLokacji::generujNowaGalaktyke(){
		auto galaktyka = generator_.generujGalaktyke();
		std::list< std::string > listaPlikow;
		std::list< STyp::Identyfikator > listaUkladow;
		std::list< STyp::Identyfikator > listaPlanet;
		auto czyszczenie = [&](){
			for (auto plik : listaPlikow){
				if (!plik.empty()){
					remove(plik.c_str());
				}
				galaktyki_.erase(galaktyka->pobierzIdentyfikator());
				for (auto& id : listaUkladow){
					ukladySloneczne_.erase(id);
				}
				for (auto& id : listaPlanet){
					planety_.erase(id);
				}
			}
		};

		auto& sGalaktyka = galaktyki_[galaktyka->pobierzIdentyfikator()];
		sGalaktyka.galaktyka_ = nullptr;
		try{
			for (int n = galaktyka->iloscUkladow_; n > 0; --n){
				auto uklad = generator_.generujUklad(galaktyka->pobierzIdentyfikator());
				if (!uklad){
					czyszczenie();
					return false;
				}
				sGalaktyka.uklady_.push_back(uklad->pobierzIdentyfikator());
				auto& sUklad = ukladySloneczne_[uklad->pobierzIdentyfikator()];
				sUklad.idGalaktyki_ = galaktyka->pobierzIdentyfikator();
				sUklad.uklad_ = nullptr;
				listaUkladow.push_back(uklad->pobierzIdentyfikator());

				for (auto planeta : uklad->planety_){
					sUklad.planety_.push_back(planeta.first);
					ObjPlaneta obj = { uklad->pobierzIdentyfikator(), nullptr, true, sUklad.flaga_inicjalizacji_ukladu };
					planety_.emplace(planeta.first, std::move(obj));
					listaPlanet.push_back(planeta.first);
				}
				
				if (!zapiszUkladSloneczny(uklad)){
					czyszczenie();
					return false;
				}
			}
		}
		catch (...){
			czyszczenie();
			throw;
		}
		
		return true;
	}

	bool ZarzadcaLokacji::wczytajUkladSloneczny(const STyp::Identyfikator& identyfikator){
		SPar::ParserDokumentXml dokument;
		auto plik = generujNazwePlikuUkladuSlonecznego(identyfikator);

		if (!dokument.odczytaj(plik.c_str()))
			return false;
		auto root = dokument.pobierzElement(nullptr);
		if (!root)
			return false;
		auto uklad = std::make_shared<UkladSloneczny>(STyp::Identyfikator(), STyp::Identyfikator());
		if (!uklad->odczytaj(root->pobierzElement(nullptr)))
			return false;
		if (identyfikator != uklad->pobierzIdentyfikator())
			return false;
		ukladySloneczne_[uklad->pobierzIdentyfikator()].uklad_ = uklad;
		for (auto planeta : uklad->planety_){
			auto iter = planety_.find(planeta.first);
			if (iter != planety_.end())
				iter->second.planeta_ = planeta.second;
		}
		return true;
	}

	bool ZarzadcaLokacji::zapiszUkladSloneczny(std::shared_ptr<UkladSloneczny> uklad) const{
		SPar::ParserDokumentXml dokument;
		auto plik = generujNazwePlikuUkladuSlonecznego(uklad->pobierzIdentyfikator());

		auto root = dokument.tworzElement(WEZEL_XML_ROOT);
		if (!uklad->zapisz(root))
			return false;

		if (!dokument.zapisz(plik.c_str()))
			return false;
		return true;
	}

	bool ZarzadcaLokacji::zapisz(XmlBO::ElementWezla wezel) const{
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

	bool ZarzadcaLokacji::odczytaj(XmlBO::ElementWezla wezel){

		if (!generator_.odczytaj(XmlBO::ZnajdzWezel<STACKTHROW>(wezel, WEZEL_XML_GENERATOR_UKLADOW)))
			return false;
		XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_GALAKTYKA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla galaktyka)->bool{
			STyp::Identyfikator idGalaktyki;
			if (!XmlBO::WczytajAtrybut<STACKTHROW>(galaktyka, ATRYBUT_XML_IDENTYFIKATOR, idGalaktyki))
				return false;
			auto& sGalaktyka = galaktyki_[idGalaktyki];
			sGalaktyka.galaktyka_ = nullptr;

			if (!XmlBO::ForEach<STACKTHROW>(galaktyka, WEZEL_XML_UKLAD_SLONECZNY, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla uklad)->bool{
				STyp::Identyfikator idUkladu;
				if (!XmlBO::WczytajAtrybut<STACKTHROW>(uklad, ATRYBUT_XML_IDENTYFIKATOR, idUkladu))
					return false;

				sGalaktyka.uklady_.push_back(idUkladu);
				auto& sUklad = ukladySloneczne_[idUkladu];
				sUklad.idGalaktyki_ = idGalaktyki;
				sUklad.uklad_ = nullptr;

				if (!XmlBO::ForEach<STACKTHROW>(uklad, WEZEL_XML_PLANETA, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla planeta)->bool{
					STyp::Identyfikator idPlanety;
					int wolna;
					if (!XmlBO::WczytajAtrybut<STACKTHROW>(planeta, ATRYBUT_XML_IDENTYFIKATOR, idPlanety))
						return false;

					wolna = XmlBO::WczytajAtrybut<int>(planeta, ATRYBUT_XML_WOLNA, -1);
					if (wolna != 0 && wolna != 1)
						return false;

					sUklad.planety_.push_back(idPlanety);
					ObjPlaneta obj = { idUkladu, nullptr, wolna, sUklad.flaga_inicjalizacji_ukladu };
					planety_.emplace(idPlanety, std::move(obj));
					return true;
				})))
					return false;

				return true;
			})))
				return false;

			return true;
		}));

		return true;
	}

	std::string ZarzadcaLokacji::generujNazwePlikuUkladuSlonecznego(const STyp::Identyfikator& id) const{
		std::string plik = folderPlikuUkladu_.c_str();
		plik += id.napis();
		plik += ".xml";
		return std::move(plik);
	}

	void ZarzadcaLokacji::wyczyscDane(){
		galaktyki_.clear();
		ukladySloneczne_.clear();
		planety_.clear();
	}

	void ZarzadcaLokacji::zaladujUstawienia(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos){
		folderPlikuUkladu_ = ustawienia.pobierzFolderPlikuUkladu();
	}
};
