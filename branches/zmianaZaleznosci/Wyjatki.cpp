#include "NiezgodnyTypSurowca.h"
#include "WyjatekParseraXML.h"
#include "WyjatekSTL.h"
#include "BrakAtrybutuXML.h"
#include "BrakMaski.h"
#include "NiezainicjalizowanaKlasa.h"
#include "NiepoprawnaIloscObiektow.h"
#include "BladLaczeniaObiektow.h"
#include "NieznalezionoObiektu.h"
#include "NiepoprawneParametryFunkcji.h"
#include "BladDzieleniaLadowni.h"
#include "NiepowodzenieTranzakcji.h"

namespace SpEx{

	const STyp::Identyfikator	NiezgodnyTypSurowca::idNiezgodnyTypSurowca(0x01);
	const STyp::Tekst		NiezgodnyTypSurowca::tytulNiezgodnyTypSurowcaDomyslny = "Niezgodny Typ Surowca";
	const STyp::Tekst		NiezgodnyTypSurowca::trescNiezgodnyTypSurowcaDomyslny = "Brak zgodnosci typow uzytych surowcow.";

	const STyp::Identyfikator	WyjatekParseraXML::idWyjatekParseraXML(0x02);
	const STyp::Tekst		WyjatekParseraXML::tytulWyjatekParseraXML = "Wyjatek przechwycony z biblioteki ticpp.";
	const STyp::Tekst		WyjatekParseraXML::trescWyjatekParseraXML = "Wykryto wyjatek wyrzucony z biblioteki ticpp o nastepujacej tresci:";
	const STyp::Tekst		WyjatekParseraXML::trescBladStrukturyXml = "Blad struktury pliku xml: ";

	const STyp::Identyfikator	WyjatekSTL::idWyjatekSTL(0x03);
	const STyp::Tekst		WyjatekSTL::tytulWyjatekSTL = "Przechwycono wyjatek STL.";
	const STyp::Tekst		WyjatekSTL::trescWyjatekSTL = "Przechwycony komunikat o wyjatku z biblioteki STL:";

	const STyp::Identyfikator	BrakAtrybutuXML::idBrakAtrybutuXML(0x04);
	const STyp::Tekst		BrakAtrybutuXML::tytulBrakAtrybutuXML = "Brak atrybutu.";
	const STyp::Tekst		BrakAtrybutuXML::trescBrakAtrybutuXML = "Brak szukanego atrybutu w danym elemencie. Nazwa szukanego atrybutu: ";

	const STyp::Identyfikator	BrakMaski::idBrakMaski(0x05);
	const STyp::Tekst		BrakMaski::tytulBrakMaski = "Brak Maski.";
	const STyp::Tekst		BrakMaski::trescBrakMaski = "Nie znaleziono maski: ";

	const STyp::Identyfikator	NiezainicjalizowanaKlasa::idNiezainicjalizowanaKlasa(0x06);
	const STyp::Tekst		NiezainicjalizowanaKlasa::tytulNiezainicjalizowanaKlasa = "Nie zainicjalizowana klasa.";
	const STyp::Tekst		NiezainicjalizowanaKlasa::trescNiezainicjalizowanaKlasa = "Klasa nie zosta³a zainicjalizowana.";

	const STyp::Identyfikator	NiepoprawnaIloscObiektow::idNiepoprawnaIloscObiektow(0x07);
	const STyp::Tekst		NiepoprawnaIloscObiektow::tytulNiepoprawnaIloscObiektow = "Niepoprawna iloœæ obiektów.";
	const STyp::Tekst		NiepoprawnaIloscObiektow::trescNiepoprawnaIloscObiektow = "U¿yta iloœæ obiektów jest zbyt du¿a lub niepoprawna.";

	const STyp::Identyfikator	BladLaczeniaObiektow::idBladLaczeniaObiektow(0x08);
	const STyp::Tekst		BladLaczeniaObiektow::tytulBladLaczeniaObiektow = "B³¹d ³¹czenia obiektów.";
	const STyp::Tekst		BladLaczeniaObiektow::trescBladLaczeniaObiektow = "Nie uda³o siê po³¹czyæ obiektów.";

	const STyp::Identyfikator	NieznalezionoObiektu::idNieznalezionoObiektu(0x09);
	const STyp::Tekst		NieznalezionoObiektu::tytulNieznalezionoObiektu = "Nie znaleziono obiektu.";
	const STyp::Tekst		NieznalezionoObiektu::trescNieznalezionoObiektu = "Obiekt o podanych kluczu nie zosta³ znaleziony.";

	const STyp::Identyfikator	NiepoprawneParametryFunkcji::idNiepoprawneParametryFunkcji(0x0A);
	const STyp::Tekst		NiepoprawneParametryFunkcji::tytulNiepoprawneParametryFunkcji = "Niepoprawne parametry funkcji.";
	const STyp::Tekst		NiepoprawneParametryFunkcji::trescNiepoprawneParametryFunkcji = "Do funkcji zosta³y przekazane niepoprawne parametry.";

	const STyp::Identyfikator	BladDzieleniaLadowni::idBladDzieleniaLadowni(0x0B);
	const STyp::Tekst		BladDzieleniaLadowni::tytulBladDzieleniaLadowni = "B³¹d podczas dzielenia ³adowni.";
	const STyp::Tekst		BladDzieleniaLadowni::trescBladDzieleniaLadowni = "Podczas podzia³u ³adowni wyst¹pi³ nieoczekiwany b³¹d.";

	const STyp::Identyfikator	NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiID(0x0C);
	const STyp::Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTytul = "Niepowodzenie wykonania tranzakcji";
	const STyp::Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTresc = "Nie uda³o siê zachowaæ tanzakcyjnoœci wykonywanych operacji. Operacja powoduj¹ca wyj¹tek: ";

}

/*
const Identyfikator	idBrakElementu											( 0x06 );
const Tekst		tytulBrakElementu										= "Brak Elementu.";
const Tekst		trescBrakElementu										= "Nie ma elementu o podanym kluczu: ";
*/
/* ------------------------------------------- */
