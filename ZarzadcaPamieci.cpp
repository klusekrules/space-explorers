#include "ZarzadcaPamieci.h"
#include "definicjeWezlowXML.h"
#include "Parser\ParserDokumentXml.h"
#include "Aplikacja.h"
#include "NieznalezionoPliku.h"

namespace SpEx{

	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelKonfiguracyjnyMaszynyStanow()const{
		if (czyZainicjalizowany_)
			return dokumentMaszynyStanow_->pobierzElement(nullptr);
		else
			return nullptr;
	}

	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelKonfiguracyjnyOknaGry()const{
		if (czyZainicjalizowany_)
			return dokumentOknaGry_->pobierzElement(nullptr);
		else
			return nullptr;
	}

	XmlBO::ElementWezla ZarzadcaPamieci::tworzWezelGry(){
		if (czyZainicjalizowany_){
			dokumentGry_ = std::make_shared<SPar::ParserDokumentXml>();
			return dokumentGry_->tworzElement(WEZEL_XML_ROOT);
		}
		else
			return nullptr;
	}

	bool ZarzadcaPamieci::zapiszWezelGry(){
		if (czyZainicjalizowany_)
			return dokumentGry_->zapisz(adresPlikuGry_.c_str());
		else
			return nullptr;
	}

	XmlBO::ElementWezla ZarzadcaPamieci::otworzWezelGry(){
		if (czyZainicjalizowany_){
			dokumentGry_ = std::make_shared<SPar::ParserDokumentXml>();
			if (!dokumentGry_->odczytaj(adresPlikuGry_.c_str())){
				auto wezel = tworzWezelGry();
				auto gra = wezel->tworzElement(WEZEL_XML_GRA);
				if (!zapiszWezelGry())
					return nullptr;
			}
			return dokumentGry_->pobierzElement(WEZEL_XML_ROOT);
		}
		else
			return nullptr;
	}

	void ZarzadcaPamieci::zaladujPliki(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos){
		adresPlikuGry_ = ustawienia.pobierzAdresPlikuGry();
		folderPlikuUzytkownika_ = ustawienia.pobierzFolderPlikuUzytkownika();
		
		dokumentMaszynyStanow_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentMaszynyStanow_->odczytaj(ustawienia.pobierzAdresPlikuStanow().c_str())){
			throw NieznalezionoPliku(EXCEPTION_PLACE, stos(), ustawienia.pobierzAdresPlikuStanow());
		}
		dokumentOknaGry_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentOknaGry_->odczytaj(ustawienia.pobierzAdresPlikuOkien().c_str())){
			throw NieznalezionoPliku(EXCEPTION_PLACE, stos(), ustawienia.pobierzAdresPlikuOkien());
		}
		czyZainicjalizowany_ = true;
	}
	
	std::shared_ptr<SPar::ParserDokument> ZarzadcaPamieci::plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik) const{
		if (hash.empty() || nazwa.empty() || !czyZainicjalizowany_)
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
}
