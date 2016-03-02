local ffi = require "interfejs"

require "class"

Gui = class()

function Gui:loguj(t,l)	
	ffi.C.wyswietlWiadomoscWGUI(t,l)
end

function Gui:wyczyscEkrany()	
	ffi.C.wyczyscListeEkranow()
end

function Gui:zdejmijOstatniEkran()	
	ffi.C.zdejmijEkranZeStosu()
end

Ekran = class(function(o,ekran)
	o.ekran_ = ekran
	end)

function Ekran:wstaw()
	return ffi.C.wstawEkranNaStos(self.ekran_)
end

function Ekran:przeladuj()
	return ffi.C.przeladujEkran(self.ekran_)
end

Kontrolka = class(Ekran,function(o,ekran, kontrolka)
	Ekran.init(o,ekran)
	o.kontrolka_ = kontrolka
	end)
	
function Ekran:kontrolka( kontrolka )
	return Kontrolka(self.ekran_,kontrolka)
end

function Kontrolka:ekran()
	return Ekran(self.ekran_)
end

function Kontrolka:aktualizujDaneObiektow()
	ffi.C.aktualizujDaneListyObiektow(self.ekran_,self.kontrolka_)
end

function Kontrolka:aktualizujDaneSurowcow()
	ffi.C.aktualizujDaneListySurowcow(self.ekran_,self.kontrolka_)
end

Wlasciwosc = class(Kontrolka, function(o,ekran,kontrolka,nazwa)
	Kontrolka.init(o,ekran, kontrolka)
	o.nazwa_ = nazwa
	end)

function Kontrolka:wlasciwosc( nazwa )
	return Wlasciwosc(self.ekran_,self.kontrolka_,nazwa)
end

function Wlasciwosc:kontrolka()
	return Kontrolka(self.ekran_,self.kontrolka_)
end

function Wlasciwosc:ustaw( value )
	return ffi.C.ustawWlasciwosc(self.ekran_,self.kontrolka_,self.nazwa_,value)
end