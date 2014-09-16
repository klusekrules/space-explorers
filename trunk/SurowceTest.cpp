#include "SurowceTest.h"


void SurowceTest::TworzenieSurowcaTest(){
	UNIT_TEST_ASSERT_NULL(krysztal_);
	auto& krysztalInfo = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzSurowce(2);
	krysztal_ = krysztalInfo.tworzEgzemplarz(STyp::Ilosc(500));
	UNIT_TEST_ASSERT_NOTNULL(krysztal_);
	UNIT_TEST_ASSERT_EQUAL(krysztal_->pobierzIlosc(), STyp::Ilosc(500));
	UNIT_TEST_ASSERT_NULL(krysztal2_);
	krysztal2_ = krysztalInfo.tworzEgzemplarz(STyp::Ilosc(250));
	UNIT_TEST_ASSERT_NOTNULL(krysztal2_);
	UNIT_TEST_ASSERT_EQUAL(krysztal2_->pobierzIlosc(), STyp::Ilosc(250));
	UNIT_TEST_ASSERT_NULL(metal_);
	auto& metalInfo = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzSurowce(1);
	metal_ = metalInfo.tworzEgzemplarz(STyp::Ilosc(100));
	UNIT_TEST_ASSERT_NOTNULL(metal_);
	UNIT_TEST_ASSERT_EQUAL(metal_->pobierzIlosc(), STyp::Ilosc(100));
}

void SurowceTest::DodawanieSurowcaTest(){
	UNIT_TEST_ASSERT_NOTNULL(krysztal_);
	UNIT_TEST_ASSERT_NOTNULL(krysztal2_);
	UNIT_TEST_ASSERT_EQUAL((*krysztal_ + *krysztal2_).pobierzIlosc(), STyp::Ilosc(750));
	UNIT_TEST_ASSERT_NOTNULL(metal_);
	UNIT_TEST_ASSERT_THROW(*krysztal_ + *metal_, SpEx::NiezgodnyTypSurowca);
}

SurowceTest::~SurowceTest(){
	if (krysztal_){
		delete krysztal_;
	}
	if (metal_){
		delete metal_;
	}
	if (krysztal2_){
		delete krysztal2_;
	}
}

REJESTRUJ_PACZKE_TESTOW(SurowceTest);