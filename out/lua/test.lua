require "aplikacja"
require "gui"
local przeprowadzonoTesty = false
-- Komentarz lua
--[[ 
	Komentarz wieloliniowy.
]]
app = Aplikacja()
gui = Gui()
login = Kontrolka(4,"login")
pass = Kontrolka(4,"pass")
listaSurowcow = Kontrolka(3,"ListaSurowcow")
listaObiektow = Kontrolka(3,"MojaKontrolka")
-- Ustawianie Okna
function stanPoczatkowy ()
	wejscieDoStanu()
	gui:wyczyscEkrany()
	app:zaladujGre("danetestowe.xml")
	app:loguj("Ustawianie okna o id 0")
	if Ekran(0):wstaw() == true then
		app:loguj("Ustawianiono")
	else
		app:loguj("Nieustawianiono")
	end
	if app:tryb() == "Serwer" then
		app:listaPolecen()
	end
end

function ustawOknoMenu ()
	wejscieDoStanu()
	gui:wyczyscEkrany()
	app:loguj("Ustawianie okna o id 1")	
	wlasciwosc = Wlasciwosc(1,"listaobiektow","enabled")
	if Ekran(1):wstaw() == true then
		app:loguj("Ustawianiono")
	else
		app:loguj("Nieustawianiono")
	end
	app:loguj("przeprowadzonoTesty: " .. tostring(przeprowadzonoTesty) )
	if przeprowadzonoTesty == true then
		wlasciwosc:ustaw("false")
	else
		wlasciwosc:ustaw("true")
	end
end

function ustawOknoLogowania ()
	wejscieDoStanu()
	gui:wyczyscEkrany()
	app:loguj("Ustawianie okna o id 4")
	if Ekran(4):wstaw() == true then
		login:wlasciwosc("focused"):ustaw("true")
		app:loguj("Ustawianiono")
	else
		app:loguj("Nieustawianiono")
	end
end

function ustawOknoPonownegoLogowania ()
	wejscieDoStanu()
	gui:wyczyscEkrany()
	ekran = Ekran(4)
	app:loguj("Ustawianie okna o id 4")
	if ekran:wstaw() == true then
		app:loguj("Ustawianiono")
		pass:wlasciwosc("focused"):ustaw("true")
		login:wlasciwosc("text"):ustaw(app:nazwaGracza())
		login:wlasciwosc("enabled"):ustaw("false")
		ekran:kontrolka("nowygracz"):wlasciwosc("enabled"):ustaw("false")
		if app:zaladujGre("danetestowe.xml") == true then
			app:loguj("Za³adowano dane.")
		else
			app:loguj("Nie uda³o siê za³adowaæ danych.")
		end
	else
		app:loguj("Nieustawianiono")
	end
end

function wyjdzOknoPonownegoLogowania ()
	login:wlasciwosc("enabled"):ustaw("true")
	Wlasciwosc(4,"nowygracz","enabled"):ustaw("true")
	wyjscieZeStanu()
end

function ustawOknoListy()
	listaObiektow:aktualizujDaneObiektow()
	listaSurowcow:aktualizujDaneSurowcow()
	wejscieDoStanu()
	gui:wyczyscEkrany()
	app:loguj("Ustawianie okna o id 3")
	if Ekran(3):wstaw() == true then	
		app:loguj("Ustawianiono")
	else
		app:loguj("Nieustawianiono")
	end
end

-- przejscia miedzy stanami
function wyjscieZeStanu()
	local stan = Stan()
	gui:zdejmijOstatniEkran()
	if stan:aktualny() == true then
		app:loguj("Wyjscie ze stanu " .. tostring(stan.idStanu_))
	else
		app:loguj("Wyjscie z nieznanego stanu")
	end
end

function wejscieDoStanu()
	local stan = Stan()
	if stan:aktualny() == true then
		app:loguj("Wejscie do stanu " .. tostring(stan.idStanu_))
	else
		app:loguj("Wejscie do nieznanego stanu")
	end
end

-- zadania menu g³ównego
function zamknijAplikacje ()
	app:zamknij()
end

function przejdzDoZamykania ()
	local zdarzenie = Zdarzenie()
	if zdarzenie:pobierz() == true then
		zdarzenie.idZdarzenia_ = 3
		zdarzenie:kolejkuj()
	else
		app:loguj("Wymuszenie zamykania aplikacji")
		app:zamknij()
	end
end

function wlaczTestowanie ()
	wejscieDoStanu()
	gui:wyczyscEkrany()
	app:loguj("Ustawianie okna o id 2")
	if Ekran(2):wstaw() == true then
		app:loguj("Ustawianiono")
	else
		app:loguj("Nieustawianiono")
	end
	
	-- ffi.C.zlecZadanie("lua\\test.lua","testy");
end

function testy ()
	app:loguj("Testowanie")
	app:wlaczTesty()
	przeprowadzonoTesty = true
	app:loguj("przeprowadzonoTesty: " .. tostring(przeprowadzonoTesty) )
	local zdarzenie = Zdarzenie()
	zdarzenie.idZdarzenia_ = 1
	zdarzenie.idStanu_ = 3
	zdarzenie.numer_ = 0
	zdarzenie:kolejkuj()
end
-- Zadania listy okien

function rozbuduj ()
	local zdarzenie = Zdarzenie()
	zdarzenie:pobierz()
	gui:loguj(1,"Rozbuduj " .. tostring(zdarzenie.numer_) )
	listaObiektow:wlasciwosc("enabled"):ustaw("false")
	app:wybudujObiekt(zdarzenie.numer_,1)
	listaObiektow:aktualizujDaneObiektow()	
	listaObiektow:wlasciwosc("enabled"):ustaw("true")
end

function zniszcz ()
	local zdarzenie = Zdarzenie()
	zdarzenie:pobierz()
	gui:loguj(1,"Zburz " .. tostring(zdarzenie.numer_))
end

function info ()
	local zdarzenie = Zdarzenie()
	zdarzenie:pobierz()
	gui:loguj(1,"Info " .. tostring(zdarzenie.numer_))
end

function przeladujOknoListeObiektow ()	
	Ekran(3):przeladuj()
end

function powrotDoOkna()
	local stan = Stan()
	stan:aktualny()
	stan.idStanu_= stan.numer_
	stan:ustawNastepny()
end

-- Zadania okna logowania
function tworzGracza()
	if app:tworzGracza(login,pass) == true then
		app:wstawZdarzenie( 4 )
	end
	login:wlasciwosc("text"):ustaw("")
	pass:wlasciwosc("text"):ustaw("")
end

function zaloguj()
	if app:zaloguj(login,pass) == true then
		app:wstawZdarzenie( 4 )
	end
	login:wlasciwosc("text"):ustaw("")
	pass:wlasciwosc("text"):ustaw("")
end

function ponownieZaloguj()
	if app:zaloguj(login,pass) == true then
		app:wstawZdarzenie( 4 )
		przeprowadzonoTesty = false
		app:loguj("przeprowadzonoTesty: " .. tostring(przeprowadzonoTesty) )
	end
	pass:wlasciwosc("text"):ustaw("")
end
