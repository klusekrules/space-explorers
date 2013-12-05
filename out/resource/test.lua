local ffi = require("ffi")
ffi.cdef[[
int printf(const char *fmt, ...);
int barfunc(int foo);
bool ustawOkno(int id);
void testyJednostkowe();
void wyczyscListeOkien();
void zamknijAplikacje();
void loguj(const char *komunikat );

struct Zdarzenie_t{
	int idStanu_;
	int numer_;
	int idZdarzenia_;
};

struct Zdarzenie_t pobierzZdarzenie( );
]]

function f ()
	local bar = ffi.C.barfunc(1)
	ffi.C.printf("Hello %s!\n%d\n", "world", ffi.new("int", bar) )
	ffi.C.loguj("Komunikacja z Loggerem dziala!")
end

function s ()
	ffi.C.loguj("Komunikat stanu")
	ffi.C.wyczyscListeOkien();
	ffi.C.loguj("Ustawianie okna o id 1")
	if ffi.C.ustawOkno(1) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

function z ()
	ffi.C.loguj("Komunikat zdarzenia")
	ffi.C.zamknijAplikacje()
end

function a ()
	ffi.C.loguj("Komunikat stanu a")
end

function b ()
	ffi.C.loguj("Komunikat zdarzenia b")
end

function stanPoczatkowy ()
	ffi.C.loguj("Ustawianie okna o id 0")
	if ffi.C.ustawOkno(0) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

function t ()
	ffi.C.loguj("Testowanie")
	ffi.C.testyJednostkowe()
end

local W = ffi.C.pobierzZdarzenie()
ffi.C.printf("idStanu %s\n idZdarzenia %s\n numer %s\n %s\n", tostring(W.idStanu_), tostring(W.idZdarzenia_), tostring(W.numer_), tostring( W.idZdarzenia_ + W.numer_ )  )
ffi.C.loguj("Poza funkcj�")
