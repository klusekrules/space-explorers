local mymodule = {}
local ffi = require("ffi")
ffi.cdef[[
//Logowanie w stylu aplikacji
void logujPoleceniaKonsoli();
void loguj(const char *komunikat );
void wyswietlWiadomoscWGUI(unsigned int typ, const char * komunikat);

//Struktury
struct Zdarzenie_t{
	int idStanu_;
	int numer_;
	int idZdarzenia_;
};

struct Stan_t{
	int idStanu_;
	int numer_;
};

enum TrybAplikacji {
	Serwer = 1 , 
	Klient = 2 , 
	Invalid = 3 
};

enum TrybAplikacji trybAplikacji();

//Pobieranie informacji
bool pobierzZdarzenie( struct Zdarzenie_t& z );
bool pobierzPoprzedniStan( struct Stan_t& s );
bool pobierzAktualnyStan( struct Stan_t& s );
bool pobierzNastepnyStan( struct Stan_t& s );
void ustawNowyStanNastepny( int id );
void ustawNowyNumerNastepny( int numer );

//Sterowanie stanami
bool wstawEkranNaStos(int id);
bool ustawWlasciwosc(int ekran, const char *kontrolka, const char *nazwaWlasciwosci, const char *nowaWartosc);
void przeladujEkran(int id);
bool zdejmijEkranZeStosu();
void wyczyscListeEkranow();
void kolejkujZdarzenie( struct Zdarzenie_t& s );
void wstawZdarzenie( struct Zdarzenie_t& s );

//Akcje
void testyJednostkowe();
void zamknijAplikacje();
void zlecZadanie( const char *plik , const char *funkcja );
void zlecZadanieGraficzne(const char *plik, const char *funkcja);
void aktualizujDaneListyObiektow(int idEkranu,const char *nazwaKontrolki);
void aktualizujDaneListySurowcow(int idEkranu, const char *nazwaKontrolki);
bool zaladujGre(const char *plik);
bool wybudujObiekt(int id, int ilosc);

//Gracz
bool zaloguj(const char *kontrolkaNazwy, const char *kontrolkaHasla);
bool nowyGracz(const char *kontrolkaNazwy, const char *kontrolkaHasla);
bool usunGracza(const char *kontrolkaNazwy, const char *kontrolkaHasla);
const char * pobierzNazweAktualnegoGracza();

]]
mymodule = ffi
return mymodule