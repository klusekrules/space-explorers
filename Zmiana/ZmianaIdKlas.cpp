#include "ZmianaAgregacja.h"
#include "ZmianaLiniowa.h"
#include "ZmianaPotegowa.h"
#include "ZmianaPotegowaAlt.h"
namespace SZmi {
	ZmianaFabryka* ZmianaAgregacja::fabryka_(nullptr);
	ZmianaFabryka* ZmianaPotegowaAlt::fabryka_(nullptr);

	const STyp::Identyfikator ZmianaAgregacja::identyfikator_(2);
	const STyp::Identyfikator ZmianaLiniowa::identyfikator_(3);
	const STyp::Identyfikator ZmianaPotegowa::identyfikator_(4);
	const STyp::Identyfikator ZmianaPotegowaAlt::identyfikator_(7);
}
