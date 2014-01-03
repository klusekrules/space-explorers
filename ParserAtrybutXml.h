#pragma once
#include "ParserAtrybut.h"
#include "tinyxml2.h"

namespace se{
	class ParserAtrybutXml :
		public ParserAtrybut
	{
	public:
		ParserAtrybutXml( const tinyxml2::XMLAttribute*, tinyxml2::XMLElement* );
		virtual ~ParserAtrybutXml(void);

		bool ustawNazwe( const char* ) override;
		const char* pobierzNazwe( ) const override;

		bool ustawWartosc( const char* ) override;
		const char* pobierzWartosc( ) const override;

		bool ustawWartoscInt( int ) override;
		int pobierzWartoscInt( ) const override;

		bool ustawWartoscUnsignedInt( unsigned int ) override;
		unsigned int pobierzWartoscUnsignedInt( ) const override;

		bool ustawWartoscInt64( __int64 ) override;
		__int64 pobierzWartoscInt64( ) const override;

		bool ustawWartoscUnsignedInt64( unsigned __int64 ) override;
		unsigned __int64 pobierzWartoscUnsignedInt64( ) const override;

		bool ustawWartoscFloat( float ) override;
		float pobierzWartoscFloat( ) const override;

		bool ustawWartoscDouble( double ) override;
		double pobierzWartoscDouble( ) const override;

		bool ustawWartoscLongDouble( long double ) override;
		long double pobierzWartoscLongDouble( ) const override;

		operator bool()const override;
	private:
		const tinyxml2::XMLAttribute* atrybut_;
		tinyxml2::XMLElement* element_;
	};
};
