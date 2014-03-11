#include "ZleceniaTest.h"
#include "MenedzerTranzakcji.h"
#include "Zlecenie.h"

void ZleceniaTest::startTestow(){
	gra = &(SpEx::Aplikacja::pobierzInstancje().pobierzGre());
	UNIT_TEST_ASSERT_NOTNULL(gra);
}

void ZleceniaTest::tranzakcja_poprawna(){
	SpEx::MenedzerTranzakcji tranzakcja;
	STyp::Ilosc jeden(1);
	std::shared_ptr<SpEx::Statek> statek(gra->pobierzStatek(STyp::Identyfikator(5)).tworzEgzemplarz(SpEx::PodstawoweParametry(jeden)));
	STyp::Ilosc dwa(2);
	STyp::Ilosc pietnascie(15);
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() - i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() *i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() / i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(pietnascie, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() - i)); return true; }
	));
	UNIT_TEST_ASSERT_TRUE(tranzakcja.wykonaj());
	STyp::Ilosc dwadziesciajeden(21);
	UNIT_TEST_ASSERT_EQUAL(dwadziesciajeden, statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_cofnieta(){
	SpEx::MenedzerTranzakcji tranzakcja;
	STyp::Ilosc jeden(1);
	std::shared_ptr<SpEx::Statek> statek(gra->pobierzStatek(STyp::Identyfikator(5)).tworzEgzemplarz(SpEx::PodstawoweParametry(jeden)));
	STyp::Ilosc dwa(2);
	STyp::Ilosc pietnascie(15);
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() - i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() *i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() / i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(pietnascie, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() - i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Operacja >());
	UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
	UNIT_TEST_ASSERT_EQUAL(jeden, statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_throw(){
	SpEx::MenedzerTranzakcji tranzakcja;
	STyp::Ilosc jeden(1);
	std::shared_ptr<SpEx::Statek> statek(gra->pobierzStatek(STyp::Identyfikator(5)).tworzEgzemplarz(SpEx::PodstawoweParametry(jeden)));
	STyp::Ilosc dwa(2);
	STyp::Ilosc pietnascie(15);
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() - i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() *i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() / i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(pietnascie, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() - i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(pietnascie, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst()); }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst()); }
	));
	SpEx::Aplikacja::pobierzInstancje().pobierzLogger().zablokujLogi(SLog::Log::Warning);
	UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
	SpEx::Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogi(SLog::Log::Warning);
	UNIT_TEST_ASSERT_EQUAL(jeden, statek->pobierzIlosc());
}

void ZleceniaTest::tranzakcja_throw2(){
	SpEx::MenedzerTranzakcji tranzakcja;
	STyp::Ilosc jeden(1);
	std::shared_ptr<SpEx::Statek> statek(gra->pobierzStatek(STyp::Identyfikator(5)).tworzEgzemplarz(SpEx::PodstawoweParametry(jeden)));
	STyp::Ilosc dwa(2);
	STyp::Ilosc pietnascie(15);
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst()); }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(dwa, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() *i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() / i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(pietnascie, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() + i)); return true; }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{s->ustawAtrybut(SpEx::PodstawoweParametry::wpisIlosc(s->pobierzIlosc() - i)); return true; }
	));
	tranzakcja.dodaj(std::make_shared< SpEx::Zlecenie< STyp::Ilosc, std::shared_ptr<SpEx::Statek> > >(pietnascie, statek
		, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst()); }
	, [](STyp::Ilosc& i, std::shared_ptr<SpEx::Statek>& s)->bool{throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst()); }
	));
	try{
		SpEx::Aplikacja::pobierzInstancje().pobierzLogger().zablokujLogi(SLog::Log::Warning);
		UNIT_TEST_ASSERT_FALSE(tranzakcja.wykonaj());
		SpEx::Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogi(SLog::Log::Warning);
	}
	catch (STyp::Wyjatek&){
		SpEx::Aplikacja::pobierzInstancje().pobierzLogger().odblokujLogi(SLog::Log::Warning);
		STyp::Ilosc trzy(3);
		UNIT_TEST_ASSERT_EQUAL(trzy, statek->pobierzIlosc());
		return;
	}
	UNIT_TEST_ASSERT_FALSE(true);
}
