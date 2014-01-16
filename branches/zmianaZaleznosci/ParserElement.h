#pragma once
#include <memory>
#include "ParserAtrybut.h"
namespace se{
	class ParserElement
	{
	public:
		ParserElement(void);
		virtual ~ParserElement(void);

		virtual std::shared_ptr<ParserAtrybut> pobierzAtrybut( const char* );
		virtual std::shared_ptr<ParserAtrybut> tworzAtrybut( const char*, const char* );
		virtual bool usunAtrybut( const char* );

		virtual std::shared_ptr<ParserElement> pobierzElement( const char* );
		virtual std::shared_ptr<ParserElement> tworzElement( const char* );
		virtual bool usunElement();

		virtual operator bool()const;
	};
};
