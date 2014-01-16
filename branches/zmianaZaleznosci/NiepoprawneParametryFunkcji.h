#pragma once
#include "OgolnyWyjatek.h"
#include <vector>
using std::vector;

/**
* Wyj¹tek informuje, ¿e parametry maj¹ nie poprawne wartoœci.
*/
class NiepoprawneParametryFunkcji :
	virtual public LoggerInterface,
	public OgolnyWyjatek
{
public:
	static const Identyfikator idNiepoprawneParametryFunkcji;
		
	template< class... V >
	NiepoprawneParametryFunkcji( const Tekst& tPlik, const Ilosc& iLinia, const V&... tail )
		: OgolnyWyjatek( tPlik, iLinia, idNiepoprawneParametryFunkcji, tytulNiepoprawneParametryFunkcji, trescNiepoprawneParametryFunkcji )
	{
		vector< std::string > a;
		std::stringstream tmp;
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

	std::string napis() const override;

private:

	template< class... V >
	static void step( vector< std::string >& v, const LoggerInterface &c , const V&... tail ){
		v.push_back(c.napis());
		step(v, tail... );
	}
	
	static void step( vector< std::string >& v, const LoggerInterface &c ){
		v.push_back(c.napis());
	}

	Tekst parametry;
	static const Tekst tytulNiepoprawneParametryFunkcji;
	static const Tekst trescNiepoprawneParametryFunkcji;
};

