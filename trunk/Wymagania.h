#pragma once
#include "Main.h"
#include "Logger\LoggerInterface.h"
#include "PodstawoweParametry.h"
#include <vector>
#include <memory>
#include "parser\ticpp.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "Czas.h"
#include "SzablonKosztow.h"

class Surowce;
class ObiektBazowyInfo;
class WyjatekParseraXML;

class Wymagania :
	virtual public LoggerInterface
{
public:
	typedef Surowce TypCeny;
	typedef SzablonKosztow< TypCeny > Cena;
	typedef vector< Cena::TypObiektu > PrzetworzonaCena;
	typedef vector< Cena > ListaCen;	

	typedef ObiektBazowyInfo TypWymogu;
	typedef SzablonKosztow< TypWymogu > Wymog;
	typedef vector< Wymog::TypObiektu > PrzetworzoneWymogi;
	typedef vector< Wymog > ListaWymogow;

	explicit Wymagania( TiXmlElement* ) throw(WyjatekParseraXML);

	virtual Czas pobierzCzasBudowy( const Ilosc& i, const PodstawoweParametry& )const;

	PrzetworzonaCena PobierzKoszty(const Ilosc&, const PodstawoweParametry& ) const;

	bool czySpelniaKoszty( const Ilosc&, const PodstawoweParametry& ) const;

	PrzetworzoneWymogi listaWarunkow( const PodstawoweParametry& ) const;

	bool czySpelniaWymogi( const PodstawoweParametry& ) const;

	/**
	* Funkcja sprawdzaj¹ca czy zosta³y spe³nione wymagania dla danej planety.
	* \param i - Ilosc elementów. Potrzebne przy sprawdzaniu ceny, aby sprawdziæ czy podana iloœæ elementów spe³nia wymagania.
	*/
	bool czySpelniaWymagania( const Ilosc& i , const PodstawoweParametry& )const;

	string napis() const override;
private:

	ListaCen koszty;

	bool dodajWymog( Wymog& o );
	bool dodajCene( Cena& o );

	ListaWymogow warunki;
	shared_ptr <ZmianaInterfejs> zmCzasuBudowy;
};
