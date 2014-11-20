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

	XmlBO::ElementWezla ZarzadcaPamieci::pobierzWezelPowiazanZasobow()const{
		if (czyZainicjalizowany_)
			return dokumentPowiazanZasobow_->pobierzElement(nullptr);
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
			throw NieznalezionoPliku(EXCEPTION_PLACE, stos(), Utils::pobierzDebugInfo(), ustawienia.pobierzAdresPlikuStanow());
		}
		dokumentOknaGry_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentOknaGry_->odczytaj(ustawienia.pobierzAdresPlikuOkien().c_str())){
			throw NieznalezionoPliku(EXCEPTION_PLACE, stos(), Utils::pobierzDebugInfo(), ustawienia.pobierzAdresPlikuOkien());
		}
		dokumentPowiazanZasobow_ = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentPowiazanZasobow_->odczytaj(ustawienia.pobierzAdresPlikuPowiazanZasobow().c_str())){
			throw NieznalezionoPliku(EXCEPTION_PLACE, stos(), Utils::pobierzDebugInfo(), ustawienia.pobierzAdresPlikuPowiazanZasobow());
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
				uzytkownik->tworzAtrybut(ATRYBUT_XML_PLANETA_AKTYWNA, std::to_string(STyp::Identyfikator(0)()).c_str());
				dokument->zapisz(plik.c_str());
			}
		}
		else{
			if (!tworzPlik)
				return nullptr;
			XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
			uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_PLANETA_AKTYWNA, std::to_string(STyp::Identyfikator(0)()).c_str());
			dokument->zapisz(plik.c_str());
		}
		nazwaPliku = plik;
		return dokument;
	}

	std::string ZarzadcaPamieci::napis() const{
		SLog::Logger logger(NAZWAKLASY(ZarzadcaPamieci));
		logger.dodajPole(NAZWAPOLA(adresPlikuGry_), NAZWAKLASY2(adresPlikuGry_), adresPlikuGry_);
		logger.dodajPole(NAZWAPOLA(folderPlikuUzytkownika_), NAZWAKLASY2(folderPlikuUzytkownika_), folderPlikuUzytkownika_); 

		std::stringstream streamCzyZainicjalizowany_;
		streamCzyZainicjalizowany_.imbue(std::locale());
		streamCzyZainicjalizowany_ << std::boolalpha << czyZainicjalizowany_;
		logger.dodajPole(NAZWAPOLA(czyZainicjalizowany_), NAZWAKLASY2(czyZainicjalizowany_), streamCzyZainicjalizowany_.str());

		if (dokumentMaszynyStanow_ != nullptr){
			std::stringstream streamPtr;
			streamPtr.imbue(std::locale("C"));
			streamPtr << "0x" << std::hex << (unsigned int)(dokumentMaszynyStanow_.get());
			logger.dodajPole(NAZWAPOLA(dokumentMaszynyStanow_), NAZWAKLASY2(dokumentMaszynyStanow_), streamPtr.str());
		}
		else
			logger.dodajPole(NAZWAPOLA(dokumentMaszynyStanow_), NAZWAKLASY2(dokumentMaszynyStanow_), "nullptr");

		if (dokumentOknaGry_ != nullptr){
			std::stringstream streamPtr;
			streamPtr.imbue(std::locale("C"));
			streamPtr << "0x" << std::hex << (unsigned int)(dokumentOknaGry_.get());
			logger.dodajPole(NAZWAPOLA(dokumentOknaGry_), NAZWAKLASY2(dokumentOknaGry_), streamPtr.str());
		}
		else
			logger.dodajPole(NAZWAPOLA(dokumentOknaGry_), NAZWAKLASY2(dokumentOknaGry_), "nullptr");

		if (dokumentGry_ != nullptr){
			std::stringstream streamPtr;
			streamPtr.imbue(std::locale("C"));
			streamPtr << "0x" << std::hex << (unsigned int)(dokumentGry_.get());
			logger.dodajPole(NAZWAPOLA(dokumentGry_), NAZWAKLASY2(dokumentGry_), streamPtr.str());
		}
		else
			logger.dodajPole(NAZWAPOLA(dokumentGry_), NAZWAKLASY2(dokumentGry_), "nullptr");

		if (dokumentPowiazanZasobow_ != nullptr){
			std::stringstream streamPtr;
			streamPtr.imbue(std::locale("C"));
			streamPtr << "0x" << std::hex << (unsigned int)(dokumentPowiazanZasobow_.get());
			logger.dodajPole(NAZWAPOLA(dokumentPowiazanZasobow_), NAZWAKLASY2(dokumentPowiazanZasobow_), streamPtr.str());
		}
		else
			logger.dodajPole(NAZWAPOLA(dokumentPowiazanZasobow_), NAZWAKLASY2(dokumentPowiazanZasobow_), "nullptr");

		return logger.napis();
	}
}
