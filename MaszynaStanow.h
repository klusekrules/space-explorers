#pragma once
#include "stdafx.h"
#include "Logger\\Log.h"
#include "OknoGry.h"
#include "StanInfo.h"
#include "Zdarzenie.h"
#include "Stan.h"
#include "Singleton.h"

class MaszynaStanow : public se::Singleton<MaszynaStanow>
{
	friend class se::Singleton<MaszynaStanow>;
public:
	
	~MaszynaStanow();

	void start();

	Stan pobierzStan( OknoGry::StosEkranow& ) const;
	
	Stan pobierzStan( ) const;
	
	void dodajKomunikat( const Zdarzenie &komunikat );

	bool kolejkujOkno( int id );

	void wyczyscKolejkeOkien( );

	void inicjujZamykanie();

private:
	
	OknoGry watekGraficzny_;

	std::map<Identyfikator,std::shared_ptr<StanInfo> > wszystkieStany_;
	Identyfikator idStanuPoczatkowy_;

	Stan stan_;
	OknoGry::StosEkranow stosEkranow_;
	mutable std::recursive_mutex mutexStanu_;
	
	Stan stanNastepny_;

	std::list<Zdarzenie> kolejkaZdarzen_;
	mutable std::mutex mutexZdarzen_;


	std::atomic_bool wlaczone;


	MaszynaStanow();

	void petlaGlowna();
	void pokazEkranStartowy();

	void dodajKomunikatLogow( Log::TypLogow typ, const std::string& komunikat );

	void przejdzDoNastepnegoStanu();

	bool pobierzKomunikat( Zdarzenie &komunikat );

	std::shared_ptr<StanInfo> pobierzOpisStanu( const Identyfikator& ) const;

	void ustawNastepnyStan(Stan&);

};

