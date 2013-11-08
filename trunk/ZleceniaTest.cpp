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
	Ilosc jeden(1);
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(jeden,Identyfikator(0x0)));
	Ilosc dwa(2);
	Ilosc pietnascie(15);
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( pietnascie , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	UNIT_TEST_ASSERT_TRUE(tranzakcja.wykonaj());
	Ilosc dwadziesciajeden(21);
	UNIT_TEST_ASSERT_EQUAL(dwadziesciajeden, statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_cofnieta(){
	MenedzerTranzakcji tranzakcja;
	Ilosc jeden(1);
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(jeden,Identyfikator(0x0)));
	Ilosc dwa(2);
	Ilosc pietnascie(15);
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( pietnascie , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Operacja >( ) );
	UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
	UNIT_TEST_ASSERT_EQUAL(jeden, statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_throw(){
	MenedzerTranzakcji tranzakcja;
	Ilosc jeden(1);
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(jeden,Identyfikator(0x0)));
	Ilosc dwa(2);
	Ilosc pietnascie(15);
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( pietnascie , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( pietnascie , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		) );
	Aplikacja::pobierzInstancje().pobierzLogger().zablokujLogi(Log::Warning);
	UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
	Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogi(Log::Warning);
	UNIT_TEST_ASSERT_EQUAL(jeden, statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_throw2(){
	MenedzerTranzakcji tranzakcja;
	Ilosc jeden(1);
	shared_ptr<Statek> statek(gra->pobierzStatek(Identyfikator(0xD)).tworzEgzemplarz(jeden,Identyfikator(0x0)));
	Ilosc dwa(2);
	Ilosc pietnascie(15);	
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( dwa , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()*i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()/i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( pietnascie , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()+i); return true;}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{s->ustawIlosc(s->pobierzIlosc()-i); return true;} 
		) );
	tranzakcja.dodaj( make_shared< Zlecenie< Ilosc , shared_ptr<Statek> > >( pietnascie , statek
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		, [](Ilosc& i , shared_ptr<Statek>& s)->bool{throw OgolnyWyjatek(EXCEPTION_PLACE);}
		) );
	try{
		Aplikacja::pobierzInstancje().pobierzLogger().zablokujLogi(Log::Warning);
		UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
		Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogi(Log::Warning);
	}catch(OgolnyWyjatek&){
		Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogi(Log::Warning);
		Ilosc trzy(3);
		UNIT_TEST_ASSERT_EQUAL(trzy, statek->pobierzIlosc());
		//Aplikacja::pobierzInstancje().pobierzLogger().error(e.generujKomunikat());
		return;
	}
	UNIT_TEST_ASSERT_FALSE(true);
}
