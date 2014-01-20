#pragma once
#include "ParserElement.h"
namespace SPar {
	class PARSER_API ParserDokument
	{
	public:
		ParserDokument(void);
		virtual ~ParserDokument(void);

		virtual std::shared_ptr<ParserElement> pobierzElement( const char* );
		virtual std::shared_ptr<ParserElement> tworzElement( const char* );
		virtual bool usunElement( std::shared_ptr<ParserElement> );

		virtual bool odczytaj( const char* );
		virtual bool zapisz( const char* );

		virtual operator bool()const;
	};
};
