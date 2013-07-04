#include "ZmianaDekorator.h"
#include "ZmianaAgregacja.h"
#include "ZmianaLiniowa.h"
#include "ZmianaPotegowa.h"
#include "ZmianaPotegowaAlt.h"
ZmianaFabryka* ZmianaDekorator::zFabryka(nullptr);
ZmianaFabryka* ZmianaAgregacja::zFabryka(nullptr);
ZmianaFabryka* ZmianaPotegowaAlt::zFabryka(nullptr);

const int ZmianaDekorator::idKlasy(1);
const int ZmianaAgregacja::idKlasy(2);
const int ZmianaLiniowa::idKlasy(3);
const int ZmianaPotegowa::idKlasy(4);
const int ZmianaPotegowaAlt::idKlasy(7);