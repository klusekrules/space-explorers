#include "XmlModul.h"
#include "Logger\Log.h"

namespace SpEx {

	const std::string XmlModul::NazwaTypu_ = "xml";

	XmlModul::XmlModul(const std::string& plik)
		: Zasob(plik), handle_(nullptr)
	{
	}

	bool XmlModul::inicjalizuj(){
		handle_ = std::make_shared<SPar::ParserDokumentXml>();
		return handle_->odczytaj(pobierzAdresPliku().c_str());
	}

}