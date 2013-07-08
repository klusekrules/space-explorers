#include "Test.h"

Statek* tworzStatek( Test& t, const Klucz& id,const Ilosc& i) throw (OgolnyWyjatek,NieznalezionoObiektu);
Surowce* tworzSurowce( Test& t, const Klucz& id,const Ilosc& i) throw (OgolnyWyjatek,NieznalezionoObiektu);

bool ladowanie_danych( Test & t );
bool test_KlasaNiepoprawneParametryFunkcji( Test & t );
bool test_KlasaLadownia( Test & t );
bool test_tworzenieObiektow( Test & t );
bool test_KlasaObiektList( Test & t );
bool test_wymagan( Test & t );
bool test_KlasaJednostkaAtakujaca( Test & t );
bool test_Issue42( Test & t );
bool test_Issue52( Test & t );
bool test_Issue39( Test & t );
bool test_Issue41i57( Test & t );
bool test_TworzeniePlanetyIObiektow( Test & t );
bool test_Technologie( Test & t );
bool test_Budynki( Test & t );
bool test_Logowanie( Test & t );
bool test_ZapisStanuGry( Test & t );