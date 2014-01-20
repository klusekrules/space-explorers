#include "ZmianaAgregacja.h"
#include "ZmianaLiniowa.h"
#include "ZmianaPotegowa.h"
#include "ZmianaPotegowaAlt.h"
namespace SZmi {
	ZmianaFabryka* ZmianaAgregacja::fabryka_(nullptr);
	ZmianaFabryka* ZmianaPotegowaAlt::fabryka_(nullptr);

	const int ZmianaAgregacja::identyfikator_(2);
	const int ZmianaLiniowa::identyfikator_(3);
	const int ZmianaPotegowa::identyfikator_(4);
	const int ZmianaPotegowaAlt::identyfikator_(7);
}
