#pragma once
namespace se{
	class ParserAtrybut
	{
	public:
		ParserAtrybut( );
		virtual ~ParserAtrybut( );

		virtual bool ustawNazwe( const char* );
		virtual const char* pobierzNazwe( ) const;

		virtual bool ustawWartosc( const char* );
		virtual const char* pobierzWartosc( ) const;

		virtual bool ustawWartoscInt( int );
		virtual int pobierzWartoscInt( ) const;

		virtual bool ustawWartoscUnsignedInt( unsigned int );
		virtual unsigned int pobierzWartoscUnsignedInt( ) const;

		virtual bool ustawWartoscInt64( __int64 );
		virtual __int64 pobierzWartoscInt64( ) const;

		virtual bool ustawWartoscUnsignedInt64( unsigned __int64 );
		virtual unsigned __int64 pobierzWartoscUnsignedInt64( ) const;

		virtual bool ustawWartoscFloat( float );
		virtual float pobierzWartoscFloat( ) const;

		virtual bool ustawWartoscDouble( double );
		virtual double pobierzWartoscDouble( ) const;

		virtual bool ustawWartoscLongDouble( long double );
		virtual long double pobierzWartoscLongDouble( ) const;

		virtual operator bool()const;

	};
};
