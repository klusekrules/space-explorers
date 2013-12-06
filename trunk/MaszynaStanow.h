#pragma once
#include "stdafx.h"
#include "Logger\\Log.h"
#include "OknoGry.h"
#include "StanInfo.h"
#include "Zdarzenie.h"
#include "Stan.h"
#include "Singleton.h"
#include "TypyEksportowne.h"


class MaszynaStanow : public se::Singleton<MaszynaStanow>
{
	friend class se::Singleton<MaszynaStanow>;
public:

	class LuaStan{
		friend class MaszynaStanow;
	public:

		LuaStan();

		bool pobierzZdarzenie( struct Zdarzenie_t& );
		bool pobierzPoprzedniStan( struct Stan_t& );
		bool pobierzAktualnyStan( struct Stan_t& );
		bool pobierzNastepnyStan( struct Stan_t& );

	private:
		struct Zdarzenie_t zdarzenie_;
		bool poprawne_zdarzenie_;
		void ustawZdarzenie(const Zdarzenie&);
	
		struct Stan_t poprzedni_;
		bool poprawne_poprzedni_;
		void ustawPoprzedni(const Stan&);
	
		struct Stan_t aktualny_;
		bool poprawne_aktualny_;
		void ustawAktualny(const Stan&);
	
		struct Stan_t nastepny_;
		bool poprawne_nastepny_;
		void ustawNastepny(const Stan&);
	};
	
	~MaszynaStanow();

	void start();

	Stan pobierzStan( OknoGry::StosEkranow& ) const;
	
	Stan pobierzStan( ) const;
	
	void kolejkujZdarzenie( const Zdarzenie &komunikat );

	void wstawZdarzenie( const Zdarzenie &komunikat );

	bool kolejkujOkno( int id );

	void wyczyscKolejkeOkien( );

	void inicjujZamykanie();
	
	LuaStan luaStan_;

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

