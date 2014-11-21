#include "XmlModul.h"
#include "Logger\Log.h"

namespace SpEx {

	XmlModul::XmlModul(const std::string& plik)
		: plik_(plik), handle_(nullptr)
	{
	}

	XmlModul::~XmlModul(){
	}

	Zasob::SharedPtr XmlModul::Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache){
		return std::make_shared<XmlModul>(parametr);
	}

	bool XmlModul::inicjalizuj(){
		handle_ = std::make_shared<SPar::ParserDokumentXml>();
		return handle_->odczytaj(plik_.c_str());
	}

	bool XmlModul::Rejestruj(ZarzadcaZasobow &fabryka){
		return fabryka.rejestrujInicjalizator(XML_ATRYBUT_TYP_ZASOBU_XML, XmlModul::Tworz);
	}

}