#include "InicjalizacjaDanychTestowych.h"
#include "LogowanieTest.h"
#include "TworzenieObiektowTest.h"
#include "ZapisStanuGryTest.h"
#include "ZleceniaTest.h"
#include "GenerowanieTest.h"
#include "CzyszczenieDanychTest.h"
#include "ParserTest.h"
#include "SumakontrolnaPlikuTest.h"

REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(SumaKontrolnaPlikuTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(ParserTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(InicjalizacjaDanychTestowych);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(LogowanieTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(GenerowanieTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(ZleceniaTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(TworzenieObiektowTest);

REJESTRUJ_PACZKE_TESTOW_JAKO_CZYSZCZENIE(ZapisStanuGryTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_CZYSZCZENIE(CzyszczenieDanychTest);
