#pragma once
#include "ParserDokument.h"
#include "tinyxml2.h"
#include <string>

namespace se{
	class ParserDokumentXml :
		public ParserDokument
	{
	public:
		ParserDokumentXml(void);
		virtual ~ParserDokumentXml(void);

		std::shared_ptr<ParserElement> pobierzElement( const char* ) override;
		std::shared_ptr<ParserElement> tworzElement( const char* ) override;
		bool usunElement( std::shared_ptr<ParserElement> ) override;

		bool odczytaj( const char* ) override;
		bool zapisz( const char* ) override;

		operator bool()const override;
	private:
		tinyxml2::XMLDocument dokument_;
		std::string nazwa_;
	};
};
