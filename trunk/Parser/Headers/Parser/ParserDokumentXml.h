#pragma once
#include "ParserInterfejs.h"
#include "tinyxml2.h"

namespace SPar{
	class PARSER_API ParserDokumentXml :
		public ParserDokument
	{
	public:
		ParserDokumentXml(void) = default;
		virtual ~ParserDokumentXml(void) = default;

		std::shared_ptr<ParserElement> pobierzElement( const char* ) override;
		std::shared_ptr<ParserElement> tworzElement( const char* ) override;
		bool usunElement( std::shared_ptr<ParserElement> ) override;

		bool odczytaj( const char* ) override;
		bool zapisz( const char* ) override;

		operator bool()const override;

		std::string error()const override;
	private:
		tinyxml2::XMLDocument dokument_;
		std::string nazwa_;
	};
};
