#include "ZleceniaTest.h"
#include "MenedzerTranzakcji.h"
#include "Zlecenie.h"

ZleceniaTest::ZleceniaTest(void)
{
}

ZleceniaTest::~ZleceniaTest(void)
{
}

void ZleceniaTest::startTestow(){
	gra = &(Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
}

void ZleceniaTest::tranzakcja_poprawna(){
	MenedzerTranzakcji tranzakcja;
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(Ilosc(1),Identyfikator(0x0)));

	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(15) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	UNIT_TEST_ASSERT_TRUE(tranzakcja.wykonaj());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(21), statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_cofnieta(){
	MenedzerTranzakcji tranzakcja;
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(Ilosc(1),Identyfikator(0x0)));

	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(15) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Operacja >( ) );
	UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1), statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_throw(){
	MenedzerTranzakcji tranzakcja;
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(Ilosc(1),Identyfikator(0x0)));

	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(15) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(15) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		) );
	Aplikacja::pobierzInstancje().pobierzLogger().zablokujLogiWarn();
	UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
	Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogiWarn();
	UNIT_TEST_ASSERT_EQUAL(Ilosc(1), statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_throw2(){
	MenedzerTranzakcji tranzakcja;
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(Ilosc(1),Identyfikator(0x0)));

	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(2) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(15) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( Ilosc(15) , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		) );
	try{
		Aplikacja::pobierzInstancje().pobierzLogger().zablokujLogiWarn();
		UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
		Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogiWarn();
	}catch(OgolnyWyjatek&){
		Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogiWarn();
		UNIT_TEST_ASSERT_EQUAL(Ilosc(3), statek->pobierzIlosc());
		//Aplikacja::pobierzInstancje().pobierzLogger().error(e.generujKomunikat());
		return;
	}
	UNIT_TEST_ASSERT_FALSE(true);
}
