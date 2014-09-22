local ffi = require "interfejs"
local przeprowadzonoTesty = false
-- Komentarz lua
--[[ 
	Komentarz wieloliniowy.
]]

-- Lokalne
function wstawZdarzenieDlaAktualnegoStanu ( id, addNumber )
	local stan = ffi.new('struct Stan_t')
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ffi.C.pobierzAktualnyStan(stan)
	zdarzenie.idStanu_ = stan.idStanu_
	zdarzenie.numer_ = addNumber
	zdarzenie.idZdarzenia_ = id
	ffi.C.wstawZdarzenie(zdarzenie)
end

function wstawZdarzenieDlaAktualnegoStanu ( id )
	local stan = ffi.new('struct Stan_t')
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ffi.C.pobierzAktualnyStan(stan)
	zdarzenie.idStanu_ = stan.idStanu_
	zdarzenie.numer_ = stan.numer_
	zdarzenie.idZdarzenia_ = id
	ffi.C.wstawZdarzenie(zdarzenie)
end

-- Ustawianie Okna
function stanPoczatkowy ()
	wejscieDoStanu()
	ffi.C.wyczyscListeEkranow();
	ffi.C.zaladujGre("danetestowe.xml")
	ffi.C.loguj("Ustawianie okna o id 0")
	if ffi.C.wstawEkranNaStos(0) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

function ustawOknoMenu ()
	wejscieDoStanu()
	ffi.C.wyczyscListeEkranow();
	ffi.C.loguj("Ustawianie okna o id 1")
	if ffi.C.wstawEkranNaStos(1) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
	ffi.C.loguj("przeprowadzonoTesty: " .. tostring(przeprowadzonoTesty) )
	if przeprowadzonoTesty == true then
		ffi.C.ustawWlasciwosc(1,"listaobiektow","enabled","false")
	else
		ffi.C.ustawWlasciwosc(1,"listaobiektow","enabled","true")
	end
end

function ustawOknoLogowania ()
	wejscieDoStanu()
	ffi.C.wyczyscListeEkranow();
	ffi.C.loguj("Ustawianie okna o id 4")
	if ffi.C.wstawEkranNaStos(4) == true then
		ffi.C.ustawWlasciwosc(4,"login","focused","true")
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

function ustawOknoPonownegoLogowania ()
	wejscieDoStanu()
	ffi.C.wyczyscListeEkranow();
	ffi.C.loguj("Ustawianie okna o id 4")
	if ffi.C.wstawEkranNaStos(4) == true then
		ffi.C.loguj("Ustawianiono")
		ffi.C.ustawWlasciwosc(4,"pass","focused","true")
		ffi.C.ustawWlasciwosc(4,"login","text", ffi.C.pobierzNazweAktualnegoGracza())
		ffi.C.ustawWlasciwosc(4,"login","enabled","false")
		ffi.C.ustawWlasciwosc(4,"nowygracz","enabled","false")
		if ffi.C.zaladujGre("danetestowe.xml") == true then
			ffi.C.loguj("Za³adowano dane.")
		else
			ffi.C.loguj("Nie uda³o siê za³adowaæ danych.")
		end
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

function wyjdzOknoPonownegoLogowania ()
	ffi.C.ustawWlasciwosc(4,"login","enabled","true")
	ffi.C.ustawWlasciwosc(4,"nowygracz","enabled","true")
	wyjscieZeStanu()
end

function ustawOknoListy()
	ffi.C.aktualizujDaneListyObiektow(3,"MojaKontrolka")
	ffi.C.aktualizujDaneListySurowcow(3,"ListaSurowcow")
	wejscieDoStanu()
	ffi.C.wyczyscListeEkranow();
	ffi.C.loguj("Ustawianie okna o id 3")
	if ffi.C.wstawEkranNaStos(3) == true then	
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
end

-- przejscia miedzy stanami
function wyjscieZeStanu()
	local stan = ffi.new('struct Stan_t');
	ffi.C.zdejmijEkranZeStosu()
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

-- zadania menu g³ównego
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

function wlaczTestowanie ()
	wejscieDoStanu()
	ffi.C.wyczyscListeEkranow();
	ffi.C.loguj("Ustawianie okna o id 2")
	if ffi.C.wstawEkranNaStos(2) == true then
		ffi.C.loguj("Ustawianiono")
	else
		ffi.C.loguj("Nieustawianiono")
	end
	
	-- ffi.C.zlecZadanie("lua\\test.lua","testy");
end

function testy ()
	ffi.C.loguj("Testowanie")
	ffi.C.testyJednostkowe()
	przeprowadzonoTesty = true
	ffi.C.loguj("przeprowadzonoTesty: " .. tostring(przeprowadzonoTesty) )
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	zdarzenie.idZdarzenia_ = 1
	zdarzenie.idStanu_ = 3
	zdarzenie.numer_ = 0
	ffi.C.kolejkujZdarzenie(zdarzenie);
end
-- Zadania listy okien

function rozbuduj ()
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ffi.C.pobierzZdarzenie(zdarzenie)
	ffi.C.wyswietlWiadomoscWGUI(1,"Rozbuduj " .. tostring(zdarzenie.numer_) )
	ffi.C.ustawWlasciwosc(3,"MojaKontrolka","enabled","false")
	ffi.C.wybudujObiekt(zdarzenie.numer_,1)
	ffi.C.aktualizujDaneListyObiektow(3,"MojaKontrolka")
	ffi.C.ustawWlasciwosc(3,"MojaKontrolka","enabled","true")
end

function zniszcz ()
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ffi.C.pobierzZdarzenie(zdarzenie)
	ffi.C.wyswietlWiadomoscWGUI(1,"Zburz " .. tostring(zdarzenie.numer_))
end

function info ()
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ffi.C.pobierzZdarzenie(zdarzenie)
	ffi.C.wyswietlWiadomoscWGUI(1,"Info " .. tostring(zdarzenie.numer_))
end

function przeladujOknoListeObiektow ()	
	ffi.C.przeladujEkran(3)
end

function powrotDoOkna()
	local stan = ffi.new('struct Stan_t')
	ffi.C.pobierzAktualnyStan(stan)
	ffi.C.ustawNowyStanNastepny(stan.numer_);
end

-- Zadania okna logowania
function tworzGracza()
	if ffi.C.nowyGracz("login","pass") == true then
		wstawZdarzenieDlaAktualnegoStanu ( 4 )
	end
	ffi.C.ustawWlasciwosc(4,"login","text","")
	ffi.C.ustawWlasciwosc(4,"pass","text","")
end

function zaloguj()
	if ffi.C.zaloguj("login","pass") == true then
		wstawZdarzenieDlaAktualnegoStanu ( 4 )
	end
	ffi.C.ustawWlasciwosc(4,"login","text","")
	ffi.C.ustawWlasciwosc(4,"pass","text","")
end

function ponownieZaloguj()
	if ffi.C.zaloguj("login","pass") == true then
		wstawZdarzenieDlaAktualnegoStanu ( 4 )
		przeprowadzonoTesty = false
		ffi.C.loguj("przeprowadzonoTesty: " .. tostring(przeprowadzonoTesty) )
	end
	ffi.C.ustawWlasciwosc(4,"pass","text","")
end
