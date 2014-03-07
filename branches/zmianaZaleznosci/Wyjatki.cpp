#include "NiezgodnyTypSurowca.h"
#include "NieznalezionoObiektu.h"
#include "NiepoprawneParametryFunkcji.h"
#include "NiepowodzenieTranzakcji.h"

namespace SpEx{

	const STyp::Identyfikator	NiezgodnyTypSurowca::idNiezgodnyTypSurowca(0x01);
	const STyp::Tekst		NiezgodnyTypSurowca::tytulNiezgodnyTypSurowcaDomyslny = "Niezgodny Typ Surowca";
	const STyp::Tekst		NiezgodnyTypSurowca::trescNiezgodnyTypSurowcaDomyslny = "Brak zgodnosci typow uzytych surowcow.";

	const STyp::Identyfikator	NieznalezionoObiektu::idNieznalezionoObiektu(0x09);
	const STyp::Tekst		NieznalezionoObiektu::tytulNieznalezionoObiektu = "Nie znaleziono obiektu.";
	const STyp::Tekst		NieznalezionoObiektu::trescNieznalezionoObiektu = "Obiekt o podanych kluczu nie zosta³ znaleziony.";

	const STyp::Identyfikator	NiepoprawneParametryFunkcji::idNiepoprawneParametryFunkcji(0x0A);
	const STyp::Tekst		NiepoprawneParametryFunkcji::tytulNiepoprawneParametryFunkcji = "Niepoprawne parametry funkcji.";
	const STyp::Tekst		NiepoprawneParametryFunkcji::trescNiepoprawneParametryFunkcji = "Do funkcji zosta³y przekazane niepoprawne parametry.";

	const STyp::Identyfikator	NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiID(0x0C);
	const STyp::Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTytul = "Niepowodzenie wykonania tranzakcji";
	const STyp::Tekst		NiepowodzenieTranzakcji::domyslnyNiepowodzenieTranzakcjiTresc = "Nie uda³o siê zachowaæ tanzakcyjnoœci wykonywanych operacji. Operacja powoduj¹ca wyj¹tek: ";

}

/* ------------------------------------------- */
