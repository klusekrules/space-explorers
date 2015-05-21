#include "NiezgodnyTypSurowca.h"
#include "NieznalezionoObiektu.h"
#include "NiepoprawneParametryFunkcji.h"
#include "BladKonfiguracjiEkranu.h"
#include "BladKonfiguracjiAplikacji.h"
#include "PowtorzenieIdObiektu.h"
#include "NieznalezionoPliku.h"
#include "BladStukturyStanu.h"
#include "NiezaimplementowanaMetoda.h"

namespace SpEx{
	const STyp::Identyfikator NiezaimplementowanaMetoda::idNiezaimplementowanaMetoda(0x6);
	const STyp::Tekst NiezaimplementowanaMetoda::tytulNiezaimplementowanaMetoda("Metoda jest niezaimplementowana!");
	const STyp::Tekst NiezaimplementowanaMetoda::trescNiezaimplementowanaMetoda("Wywo³ano niezaimplementowan¹ metodê: ");

	const STyp::Identyfikator BladStukturyStanu::idBladStukturyStanu(0x5);
	const STyp::Identyfikator NieznalezionoPliku::idNieznalezionoPliku(0x4);
	const STyp::Identyfikator PowtorzenieIdObiektu::idPowtorzeniaIdObiektu(0x3);
	const STyp::Identyfikator BladKonfiguracjiEkranu::idBladKonfiguracjiEkranu(0x2);
	const STyp::Identyfikator BladKonfiguracjiAplikacji::idBladKonfiguracjiAplikacji(0x1);

	const STyp::Identyfikator	NiezgodnyTypSurowca::idNiezgodnyTypSurowca(0x10);
	const STyp::Tekst		NiezgodnyTypSurowca::tytulNiezgodnyTypSurowcaDomyslny = "Niezgodny Typ Surowca";
	const STyp::Tekst		NiezgodnyTypSurowca::trescNiezgodnyTypSurowcaDomyslny = "Brak zgodnosci typow uzytych surowcow.";

	const STyp::Identyfikator	NieznalezionoObiektu::idNieznalezionoObiektu(0x19);
	const STyp::Tekst		NieznalezionoObiektu::tytulNieznalezionoObiektu = "Nie znaleziono obiektu.";
	const STyp::Tekst		NieznalezionoObiektu::trescNieznalezionoObiektu = "Obiekt o podanych kluczu nie zosta³ znaleziony.";

	const STyp::Identyfikator	NiepoprawneParametryFunkcji::idNiepoprawneParametryFunkcji(0x1A);
	const STyp::Tekst		NiepoprawneParametryFunkcji::tytulNiepoprawneParametryFunkcji = "Niepoprawne parametry funkcji.";
	const STyp::Tekst		NiepoprawneParametryFunkcji::trescNiepoprawneParametryFunkcji = "Do funkcji zosta³y przekazane niepoprawne parametry.";


}

/* ------------------------------------------- */
