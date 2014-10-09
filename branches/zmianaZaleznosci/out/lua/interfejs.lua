local mymodule = {}
local ffi = require("ffi")
ffi.cdef[[
//Logowanie w stylu aplikacji
void loguj(const char *komunikat );

//Struktury
struct Zdarzenie_t{
	int idStanu_;
	int numer_;
	int idZdarzenia_;
};

struct Stan_t{
	int idStanu_;
	int numer_;
	long double dt_; //Milisekundy
};

//Pobieranie informacji
bool pobierzZdarzenie( struct Zdarzenie_t& z );
bool pobierzPoprzedniStan( struct Stan_t& s );
bool pobierzAktualnyStan( struct Stan_t& s );
bool pobierzNastepnyStan( struct Stan_t& s );

//Sterowanie stanami
bool ustawOkno(int id);
void wyczyscListeOkien();
void kolejkujZdarzenie( struct Zdarzenie_t& s );
void wstawZdarzenie( struct Zdarzenie_t& s );

//Akcje
void testyJednostkowe();
void zamknijAplikacje();
void zlecZadanie( const char *plik , const char *funkcja );
]]
mymodule = ffi
return mymodule