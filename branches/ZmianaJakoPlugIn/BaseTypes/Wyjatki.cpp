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
/* Sta�e pola klas wyj�tk�w  */

const IdType	OgolnyWyjatek::domyslnyOgolnyWyjatekID					( 0x0 );
const Tekst		OgolnyWyjatek::domyslnyOgolnyWyjatekTytul				= "Ogolny wyjatek!";
const Tekst		OgolnyWyjatek::domyslnyOgolnyWyjatekTresc				= "Wystapil ogolny wyjatek";
	
const IdType	NiezgodnyTypSurowca::idNiezgodnyTypSurowca				( 0x01 );
const Tekst		NiezgodnyTypSurowca::tytulNiezgodnyTypSurowcaDomyslny	= "Niezgodny Typ Surowca";
const Tekst		NiezgodnyTypSurowca::trescNiezgodnyTypSurowcaDomyslny	= "Brak zgodnosci typow uzytych surowcow.";

const IdType	WyjatekParseraXML::idWyjatekParseraXML					( 0x02 );
const Tekst		WyjatekParseraXML::tytulWyjatekParseraXML				= "Wyjatek przechwycony z biblioteki ticpp.";
const Tekst		WyjatekParseraXML::trescWyjatekParseraXML				= "Wykryto wyjatek wyrzucony z biblioteki ticpp o nastepujacej tresci:";
const Tekst		WyjatekParseraXML::trescBladStrukturyXml				= "Blad struktury pliku xml: ";

const IdType	WyjatekSTL::idWyjatekSTL								( 0x03 );
const Tekst		WyjatekSTL::tytulWyjatekSTL								= "Przechwycono wyjatek STL.";
const Tekst		WyjatekSTL::trescWyjatekSTL								= "Przechwycony komunikat o wyjatku z biblioteki STL:";

const IdType	BrakAtrybutuXML::idBrakAtrybutuXML						( 0x04 );
const Tekst		BrakAtrybutuXML::tytulBrakAtrybutuXML					= "Brak atrybutu.";
const Tekst		BrakAtrybutuXML::trescBrakAtrybutuXML					= "Brak szukanego atrybutu w danym elemencie. Nazwa szukanego atrybutu: ";

const IdType	BrakMaski::idBrakMaski									( 0x05 );
const Tekst		BrakMaski::tytulBrakMaski								= "Brak Maski.";
const Tekst		BrakMaski::trescBrakMaski								= "Nie znaleziono maski: ";

const IdType	NiezainicjalizowanaKlasa::idNiezainicjalizowanaKlasa	( 0x06 );
const Tekst		NiezainicjalizowanaKlasa::tytulNiezainicjalizowanaKlasa	= "Nie zainicjalizowana klasa.";
const Tekst		NiezainicjalizowanaKlasa::trescNiezainicjalizowanaKlasa	= "Klasa nie zosta�a zainicjalizowana.";

const IdType	NiepoprawnaIloscObiektow::idNiepoprawnaIloscObiektow	( 0x07 );
const Tekst		NiepoprawnaIloscObiektow::tytulNiepoprawnaIloscObiektow = "Niepoprawna ilo�� obiekt�w.";
const Tekst		NiepoprawnaIloscObiektow::trescNiepoprawnaIloscObiektow = "U�yta ilo�� obiekt�w jest zbyt du�a lub niepoprawna.";

const IdType	BladLaczeniaObiektow::idBladLaczeniaObiektow			( 0x08 );
const Tekst		BladLaczeniaObiektow::tytulBladLaczeniaObiektow			= "B��d ��czenia obiekt�w.";
const Tekst		BladLaczeniaObiektow::trescBladLaczeniaObiektow			= "Nie uda�o si� po��czy� obiekt�w.";

const IdType	NieznalezionoObiektu::idNieznalezionoObiektu			( 0x09 );
const Tekst		NieznalezionoObiektu::tytulNieznalezionoObiektu			= "Nie znaleziono obiektu.";
const Tekst		NieznalezionoObiektu::trescNieznalezionoObiektu			= "Obiekt o podanych kluczu nie zosta� znaleziony.";

const IdType	NiepoprawneParametryFunkcji::idNiepoprawneParametryFunkcji ( 0x0A );
const Tekst		NiepoprawneParametryFunkcji::tytulNiepoprawneParametryFunkcji = "Niepoprawne parametry funkcji.";
const Tekst		NiepoprawneParametryFunkcji::trescNiepoprawneParametryFunkcji = "Do funkcji zosta�y przekazane niepoprawne parametry.";

const IdType	BladDzieleniaLadowni::idBladDzieleniaLadowni			( 0x0B );
const Tekst		BladDzieleniaLadowni::tytulBladDzieleniaLadowni			= "B��d podczas dzielenia �adowni.";
const Tekst		BladDzieleniaLadowni::trescBladDzieleniaLadowni			= "Podczas podzia�u �adowni wyst�pi� nieoczekiwany b��d.";
/*
const IdType	idBrakElementu											( 0x06 );
const Tekst		tytulBrakElementu										= "Brak Elementu.";
const Tekst		trescBrakElementu										= "Nie ma elementu o podanym kluczu: ";
*/
/* ------------------------------------------- */

