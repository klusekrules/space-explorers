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
	ffi.C.zdejmijOkno()
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
	wejscieDoStanu()
	ffi.C.wyczyscListeOkien();
	ffi.C.loguj("Ustawianie okna o id 2")
	if ffi.C.ustawOkno(2) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
	
	ffi.C.zlecZadanie("lua\\test.lua","testy");
end


function testy ()
	ffi.C.loguj("Testowanie")
	ffi.C.testyJednostkowe()
	
	local zdarzenie = ffi.new('struct Zdarzenie_t');
	zdarzenie.idZdarzenia_ = 1
	zdarzenie.idStanu_ = 3
	zdarzenie.numer_ = 0
	ffi.C.kolejkujZdarzenie(zdarzenie);
end

function ustawOknoListy()
	wejscieDoStanu()
	ffi.C.wyczyscListeOkien();
	ffi.C.loguj("Ustawianie okna o id 3")
	if ffi.C.ustawOkno(3) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
	ffi.C.wypelnijKontrolkeObiektu(3,1,"MojaKontrolka")
end

function wczytajDane ()	
	if ffi.C.wczytajDane("danetestowe.xml") == true then
		ffi.C.loguj("Za³adowano dane.")
	else
		ffi.C.loguj("Nie uda³o siê za³adowaæ danych.")
	end
end

function przeladujOknoListeObiektow ()	
	ffi.C.przeladujOkno(3)
end

function wczytajPonownieListeObiektow ()
    ffi.C.przeladujOkno(3)
	ffi.C.zlecZadanieGraficzne("lua\\test.lua","wczytajPonownieListeObiektowImpl");
end

function wczytajPonownieListeObiektowImpl ()
	wczytajDane()
	ustawOknoListy()
end