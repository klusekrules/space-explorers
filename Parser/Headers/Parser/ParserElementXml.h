#pragma once
#include "ParserInterfejs.h"
#include "tinyxml2.h"

namespace SPar {
	class PARSER_API ParserElementXml :
		public ParserElement
	{
		friend class ParserDokumentXml;
	public:
		ParserElementXml( tinyxml2::XMLElement* );
		virtual ~ParserElementXml(void) = default;

		bool ustawNazwe(const char*) override;
		const char* pobierzNazwe() const override;

		bool ustawTekst(const char*) override;
		const char* pobierzTekst()const override;

		std::shared_ptr<ParserAtrybut> pobierzAtrybut( const char* ) override;
		std::shared_ptr<ParserAtrybut> tworzAtrybut( const char* , const char* ) override;
		bool usunAtrybut( const char* ) override;

		std::shared_ptr<ParserElement> pobierzElement(const char*) override;
		std::shared_ptr<ParserElement> pobierzNastepnyElement(const char*) const override;
		std::shared_ptr<ParserElement> tworzElement( const char* ) override;
		bool usunElement() override;

		operator bool()const;

		std::string error()const override;

	private:
		tinyxml2::XMLElement* element_ = nullptr;
	};
};
