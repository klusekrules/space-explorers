#pragma once
#include "Logger\LoggerInterface.h"
#include "Base.h"
#include "ObiektBase.h"
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
	public Base,
	virtual public LoggerInterface,
	virtual public Serializacja
{
	friend class Gra;
	friend class Uzytkownik;
public:
	typedef map< IdType , shared_ptr< ObiektBase > > ListaObiektow;
	typedef map< IdType , shared_ptr< Budynek > > ListaBudynkow;
	typedef map< IdType , shared_ptr< Technologia > > ListaTechnologii;
	typedef map< IdType , shared_ptr< Statek > > ListaStatkow;
	typedef map< IdType , shared_ptr< Surowce > > ListaSurowcow;
	typedef map< IdType , shared_ptr< Flota > > ListaFlot;

	Planeta(const IdType& id);
	virtual ~Planeta(void);

	const ObiektBase& pobierzObiekt(const IdType&) const;
	Ilosc pobierzIloscTypowObiektow()const;
	
	bool wybuduj( const IdType&, const Ilosc& );

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	string toString() const override;
	
private:

	bool dodajObiekt( shared_ptr< Budynek > );
	bool dodajObiekt( shared_ptr< Statek > );
	bool dodajObiekt( shared_ptr< Technologia > );
	bool dodajObiekt( shared_ptr< Surowce > );

	IdType dodajFlote();

	bool przeniesDoFloty(const IdType& floty, const IdType& id, const Ilosc&);

	void ustawWlasciciela( Uzytkownik* );
	Uzytkownik* pobierzWlasciciela( void ) const;

	ObiektBase pustyObiektBase;
	ObiektBaseInfo pustyobiekBaseInfo;

	Licznik idFloty;
	Uzytkownik* wlasciciel;

	ListaSurowcow listaSurowcow;
	ListaStatkow listaStatkow;
	ListaTechnologii listaTechnologii;
	ListaBudynkow listaBudynkow;
	ListaObiektow listaObiektow;
	ListaFlot listaFlot;
};

