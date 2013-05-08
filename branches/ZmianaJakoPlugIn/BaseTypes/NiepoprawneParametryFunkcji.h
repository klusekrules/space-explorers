#pragma once
#include "OgolnyWyjatek.h"
#include <vector>

/**
* Wyj¹tek informuje, ¿e parametry maj¹ nie poprawne wartoœci.
*/
class BASETYPES_API NiepoprawneParametryFunkcji :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const IdType idNiepoprawneParametryFunkcji;
		
	template< class... V >
	NiepoprawneParametryFunkcji( const Tekst& tPlik, const IdType& iLinia, const V&... tail )
		: OgolnyWyjatek( tPlik, iLinia, idNiepoprawneParametryFunkcji, tytulNiepoprawneParametryFunkcji, trescNiepoprawneParametryFunkcji )
	{
		vector< string > a;
		stringstream tmp;
		step(a, tail... );
		for ( auto s : a ){
			tmp<< "Parametr - [ " << s << " ] \n";
		}
		parametry = tmp.str();
	}
	
	virtual ~NiepoprawneParametryFunkcji();

	const Tekst& getParametry() const;
	void setParametry ( const Tekst& wwTresc );
	
	Tekst generujKomunikat() const override;

	string toString() const override;

private:

	template< class... V >
	static void step( vector< string >& v, const LoggerInterface &c , const V&... tail ){
		v.push_back(c.toString());
		step(v, tail... );
	}
	
	static void step( vector< string >& v, const LoggerInterface &c ){
		v.push_back(c.toString());
	}

	Tekst parametry;
	static const Tekst tytulNiepoprawneParametryFunkcji;
	static const Tekst trescNiepoprawneParametryFunkcji;
};

