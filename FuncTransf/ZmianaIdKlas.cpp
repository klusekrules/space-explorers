#include "ZmianaAgregacja.h"
#include "ZmianaLiniowa.h"
#include "ZmianaPotegowa.h"
#include "ZmianaPotegowaAlt.h"
ZmianaFabryka* ZmianaAgregacja::zFabryka(nullptr);
ZmianaFabryka* ZmianaPotegowaAlt::zFabryka(nullptr);

const int ZmianaAgregacja::idKlasy(2);
const int ZmianaLiniowa::idKlasy(3);
const int ZmianaPotegowa::idKlasy(4);
const int ZmianaPotegowaAlt::idKlasy(7);