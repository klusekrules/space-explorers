#pragma once
#include "Logger\LoggerInterface.h"
#include "Bazowa.h"
#include "ObiektBazowy.h"
#include "ObiektBaseInfo.h"
#include <map>
#include <memory>
#include "Budynek.h"
#include "Statek.h"
#include "Technologia.h"
#include "Surowce.h"
#include "NiepoprawnaIloscObiektow.h"
#include "Flota.h"
#include "Licznik.h"

class Planeta:
	public Bazowa,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class Gra;
	friend class Uzytkownik;
public:
	typedef map< Identyfikator , shared_ptr< ObiektBazowy > > ListaObiektow;
	typedef map< Identyfikator , shared_ptr< Obiekt > > ListaObiektowZaladunkowych;
	typedef map< Identyfikator , shared_ptr< Budynek > > ListaBudynkow;
	typedef map< Identyfikator , shared_ptr< Technologia > > ListaTechnologii;
	typedef map< Identyfikator , shared_ptr< Statek > > ListaStatkow;
	typedef map< Identyfikator , shared_ptr< Surowce > > ListaSurowcow;
	typedef map< Identyfikator , shared_ptr< Flota > > ListaFlot;

	Planeta(const Identyfikator& id);
	virtual ~Planeta(void);

	const ObiektBazowy& pobierzObiekt(const Identyfikator&) const;
	Ilosc pobierzIloscTypowObiektow()const;

	const Statek& pobierzStatek(const Identyfikator&) const;
	const Technologia& pobierzTechnologie(const Identyfikator&) const;
	const Budynek& pobierzBudynek(const Identyfikator&) const;
	
	bool wybuduj( const Identyfikator&, const Ilosc& );

	Identyfikator dodajFlote();

	bool przeniesDoFloty(const Identyfikator& floty, const Identyfikator& id, const Ilosc&);

	bool dolaczFloteDoPlanety(const Identyfikator&);

	bool dolaczFloteDoPlanety( shared_ptr< Flota >);

	bool zaladujFlote( const Identyfikator& floty, const Identyfikator& id, const Ilosc&);

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	string napis() const override;
	
private:

	bool dodajObiekt( shared_ptr< Budynek > );
	bool dodajObiekt( shared_ptr< Statek > );
	bool dodajObiekt( shared_ptr< Technologia > );
	bool dodajObiekt( shared_ptr< Surowce > );

	bool rozladujStatek( shared_ptr< Statek >);

	void ustawWlasciciela( Uzytkownik* );
	Uzytkownik* pobierzWlasciciela( void ) const;

	shared_ptr<ObiektBazowy> pustyObiektBase;
	ObiektBaseInfo pustyobiekBaseInfo;

	Licznik idFloty;
	Uzytkownik* wlasciciel;

	ListaSurowcow listaSurowcow;
	ListaStatkow listaStatkow;
	ListaTechnologii listaTechnologii;
	ListaBudynkow listaBudynkow;
	ListaObiektow listaObiektow;
	ListaObiektowZaladunkowych listaObiektowZaladunkowych;
	ListaFlot listaFlot;
};

