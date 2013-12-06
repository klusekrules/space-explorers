local ffi = require "interfejs"

function ustawOknoMenu ()
	wejscieDoStanu()
	ffi.C.wyczyscListeOkien();
	ffi.C.loguj("Ustawianie okna o id 1")
	if ffi.C.ustawOkno(1) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

function wyjscieZeStanu()
	local stan = ffi.new('struct Stan_t');
	if ffi.C.pobierzAktualnyStan(stan) == true then
		ffi.C.loguj("Wyjscie ze stanu " .. tostring(stan.idStanu_))
	else
		ffi.C.loguj("Wyjscie z nieznanego stanu")
	end
end

function wejscieDoStanu()
	local stan = ffi.new('struct Stan_t');
	if ffi.C.pobierzAktualnyStan(stan) == true then
		ffi.C.loguj("Wejscie do stanu " .. tostring(stan.idStanu_))
	else
		ffi.C.loguj("Wejscie do nieznanego stanu")
	end
end

function zamknijAplikacje ()
	ffi.C.zamknijAplikacje()
end

function przejdzDoZamykania ()
	local zdarzenie = ffi.new('struct Zdarzenie_t');
	if ffi.C.pobierzZdarzenie(zdarzenie) == true then
		zdarzenie.idZdarzenia_ = 3
		ffi.C.kolejkujZdarzenie(zdarzenie);
	else
		ffi.C.loguj("Wymuszenie zamykania aplikacji")
		ffi.C.zamknijAplikacje()
	end
end

function stanPoczatkowy ()
	wejscieDoStanu()
	ffi.C.wyczyscListeOkien();
	ffi.C.loguj("Ustawianie okna o id 0")
	if ffi.C.ustawOkno(0) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

function wlaczTestowanie ()
	ffi.C.loguj("Testowanie")
	ffi.C.testyJednostkowe()
end