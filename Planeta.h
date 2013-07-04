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

class Planeta:
	public Base,
	virtual public LoggerInterface
{
	friend class Gra;
	friend class Uzytkownik;
public:
	typedef map< IdType , shared_ptr< ObiektBase > > ListaObiektow;
	typedef map< IdType , shared_ptr< Budynek > > ListaBudynkow;
	typedef map< IdType , shared_ptr< Technologia > > ListaTechnologii;
	typedef map< IdType , shared_ptr< Statek > > ListaStatkow;
	typedef map< IdType , shared_ptr< Surowce > > ListaSurowcow;

	Planeta(const IdType& id);
	virtual ~Planeta(void);

	const ObiektBase& pobierzObiekt(const IdType&) const;
	Ilosc pobierzIloscObiektow()const;
	
	bool wybuduj( const IdType&, const Ilosc& );

	string toString() const override;
	
private:

	bool dodajObiekt( shared_ptr< Budynek > );
	bool dodajObiekt( shared_ptr< Statek > );
	bool dodajObiekt( shared_ptr< Technologia > );
	bool dodajObiekt( shared_ptr< Surowce > );

	void ustawWlasciciela( Uzytkownik* );
	Uzytkownik* pobierzWlasciciela( void ) const;

	ObiektBase pustyObiektBase;
	ObiektBaseInfo pustyobiekBaseInfo;

	Uzytkownik* wlasciciel;

	ListaSurowcow listaSurowcow;
	ListaStatkow listaStatkow;
	ListaTechnologii listaTechnologii;
	ListaBudynkow listaBudynkow;
	ListaObiektow listaObiektow;
};

