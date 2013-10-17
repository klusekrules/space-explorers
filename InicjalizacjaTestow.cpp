#include "InicjalizacjaDanychTestowych.h"
#include "LogowanieTest.h"
#include "TworzenieObiektowTest.h"
#include "ZapisStanuGryTest.h"
#include "ZleceniaTest.h"
#include "KluczTest.h"
#include "GenerowanieTest.h"

REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(KluczTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(InicjalizacjaDanychTestowych);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(LogowanieTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(GenerowanieTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(ZleceniaTest);
REJESTRUJ_PACZKE_TESTOW_JAKO_INICJALIZACJA(TworzenieObiektowTest);

REJESTRUJ_PACZKE_TESTOW_JAKO_CZYSZCZENIE(ZapisStanuGryTest);
