#include "XmlModul.h"
#include "Logger\Log.h"

namespace SpEx {

	const std::string XmlModul::NazwaTypu_ = XML_ATRYBUT_TYP_ZASOBU_XML;

	XmlModul::XmlModul(const std::string& plik)
		: plik_(plik), handle_(nullptr)
	{
	}

	bool XmlModul::inicjalizuj(){
		handle_ = std::make_shared<SPar::ParserDokumentXml>();
		return handle_->odczytaj(plik_.c_str());
	}

}