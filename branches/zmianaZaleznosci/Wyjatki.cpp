#include "OgolnyWyjatek.h"
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
/* Sta³e pola klas wyj¹tków  */

const Identyfikator	OgolnyWyjatek::domyslnyOgolnyWyjatekID					( 0x0 );
const Tekst		OgolnyWyjatek::domyslnyOgolnyWyjatekTytul				= "Ogolny wyjatek!";
const Tekst		OgolnyWyjatek::domyslnyOgolnyWyjatekTresc				= "Wystapil ogolny wyjatek";
	
const Identyfikator	NiezgodnyTypSurowca::idNiezgodnyTypSurowca				( 0x01 );
const Tekst		NiezgodnyTypSurowca::tytulNiezgodnyTypSurowcaDomyslny	= "Niezgodny Typ Surowca";
const Tekst		NiezgodnyTypSurowca::trescNiezgodnyTypSurowcaDomyslny	= "Brak zgodnosci typow uzytych surowcow.";

const Identyfikator	WyjatekParseraXML::idWyjatekParseraXML					( 0x02 );
const Tekst		WyjatekParseraXML::tytulWyjatekParseraXML				= "Wyjatek przechwycony z biblioteki ticpp.";
const Tekst		WyjatekParseraXML::trescWyjatekParseraXML				= "Wykryto wyjatek wyrzucony z biblioteki ticpp o nastepujacej tresci:";
const Tekst		WyjatekParseraXML::trescBladStrukturyXml				= "Blad struktury pliku xml: ";

const Identyfikator	WyjatekSTL::idWyjatekSTL								( 0x03 );
const Tekst		WyjatekSTL::tytulWyjatekSTL								= "Przechwycono wyjatek STL.";
const Tekst		WyjatekSTL::trescWyjatekSTL								= "Przechwycony komunikat o wyjatku z biblioteki STL:";

const Identyfikator	BrakAtrybutuXML::idBrakAtrybutuXML						( 0x04 );
const Tekst		BrakAtrybutuXML::tytulBrakAtrybutuXML					= "Brak atrybutu.";
const Tekst		BrakAtrybutuXML::trescBrakAtrybutuXML					= "Brak szukanego atrybutu w danym elemencie. Nazwa szukanego atrybutu: ";

const Identyfikator	BrakMaski::idBrakMaski									( 0x05 );
const Tekst		BrakMaski::tytulBrakMaski								= "Brak Maski.";
const Tekst		BrakMaski::trescBrakMaski								= "Nie znaleziono maski: ";

const Identyfikator	NiezainicjalizowanaKlasa::idNiezainicjalizowanaKlasa	( 0x06 );
const Tekst		NiezainicjalizowanaKlasa::tytulNiezainicjalizowanaKlasa	= "Nie zainicjalizowana klasa.";
const Tekst		NiezainicjalizowanaKlasa::trescNiezainicjalizowanaKlasa	= "Klasa nie zosta³a zainicjalizowana.";

const Identyfikator	NiepoprawnaIloscObiektow::idNiepoprawnaIloscObiektow	( 0x07 );
const Tekst		NiepoprawnaIloscObiektow::tytulNiepoprawnaIloscObiektow = "Niepoprawna iloœæ obiektów.";
const Tekst		NiepoprawnaIloscObiektow::trescNiepoprawnaIloscObiektow = "U¿yta iloœæ obiektów jest zbyt du¿a lub niepoprawna.";

const Identyfikator	BladLaczeniaObiektow::idBladLaczeniaObiektow			( 0x08 );
const Tekst		BladLaczeniaObiektow::tytulBladLaczeniaObiektow			= "B³¹d ³¹czenia obiektów.";
const Tekst		BladLaczeniaObiektow::trescBladLaczeniaObiektow			= "Nie uda³o siê po³¹czyæ obiektów.";

const Identyfikator	NieznalezionoObiektu::idNieznalezionoObiektu			( 0x09 );
const Tekst		NieznalezionoObiektu::tytulNieznalezionoObiektu			= "Nie znaleziono obiektu.";
const Tekst		NieznalezionoObiektu::trescNieznalezionoObiektu			= "Obiekt o podanych kluczu nie zosta³ znaleziony.";

const Identyfikator	NiepoprawneParametryFunkcji::idNiepoprawneParametryFunkcji ( 0x0A );
const Tekst		NiepoprawneParametryFunkcji::tytulNiepoprawneParametryFunkcji = "Niepoprawne parametry funkcji.";
const Tekst		NiepoprawneParametryFunkcji::trescNiepoprawneParametryFunkcji = "Do funkcji zosta³y przekazane niepoprawne parametry.";

const Identyfikator	BladDzieleniaLadowni::idBladDzieleniaLadowni			( 0x0B );
const Tekst		BladDzieleniaLadowni::tytulBladDzieleniaLadowni			= "B³¹d podczas dzielenia ³adowni.";
const Tekst		BladDzieleniaLadowni::trescBladDzieleniaLadowni			= "Podczas podzia³u ³adowni wyst¹pi³ nieoczekiwany b³¹d.";

const Identyfikator	NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiID			( 0x0C );
const Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTytul			= "Niepowodzenie wykonania tranzakcji";
const Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTresc			= "Nie uda³o siê zachowaæ tanzakcyjnoœci wykonywanych operacji. Operacja powoduj¹ca wyj¹tek: ";
/*
const Identyfikator	idBrakElementu											( 0x06 );
const Tekst		tytulBrakElementu										= "Brak Elementu.";
const Tekst		trescBrakElementu										= "Nie ma elementu o podanym kluczu: ";
*/
/* ------------------------------------------- */


