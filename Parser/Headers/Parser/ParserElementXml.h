#pragma once
#include "ParserElement.h"
#include "tinyxml2.h"

namespace SPar {
	class ParserElementXml :
		public ParserElement
	{
		friend class ParserDokumentXml;
	public:
		ParserElementXml( tinyxml2::XMLElement* );
		virtual ~ParserElementXml(void);

		std::shared_ptr<ParserAtrybut> pobierzAtrybut( const char* ) override;
		std::shared_ptr<ParserAtrybut> tworzAtrybut( const char* , const char* ) override;
		bool usunAtrybut( const char* ) override;

		std::shared_ptr<ParserElement> pobierzElement( const char* ) override;
		std::shared_ptr<ParserElement> tworzElement( const char* ) override;
		bool usunElement() override;

		operator bool()const;
	private:
		tinyxml2::XMLElement* element_;
	};
};
