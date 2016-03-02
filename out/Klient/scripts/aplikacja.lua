local ffi = require "interfejs"

require "class"

Aplikacja = class()

function Aplikacja:test()	
	ffi.C.loguj("Test tworzenia klasy w lua.")
end

function Aplikacja:loguj(l)	
	ffi.C.loguj(l)
end

function Aplikacja:wstawZdarzenie ( id, addNumber )
	local stan = ffi.new('struct Stan_t')
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ffi.C.pobierzAktualnyStan(stan)
	zdarzenie.idStanu_ = stan.idStanu_
	zdarzenie.numer_ = addNumber
	zdarzenie.idZdarzenia_ = id
	ffi.C.wstawZdarzenie(zdarzenie)
end

function Aplikacja:wstawZdarzenie( id )
	local stan = ffi.new('struct Stan_t')
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ffi.C.pobierzAktualnyStan(stan)
	zdarzenie.idStanu_ = stan.idStanu_
	zdarzenie.numer_ = stan.numer_
	zdarzenie.idZdarzenia_ = id
	ffi.C.wstawZdarzenie(zdarzenie)
end

function Aplikacja:zamknij()
	ffi.C.zamknijAplikacje()
end

function Aplikacja:listaPolecen()
	ffi.C.logujPoleceniaKonsoli()
end

function Aplikacja:tryb()
	return ffi.C.trybAplikacji()
end

function Aplikacja:zaloguj(login, pass)	
	return ffi.C.zaloguj(login.kontrolka_,pass.kontrolka_)
end

function Aplikacja:tworzGracza(login, pass)	
	return ffi.C.nowyGracz(login.kontrolka_,pass.kontrolka_)
end

function Aplikacja:zaladujGre( file )	
	return ffi.C.zaladujGre(file)
end

function Aplikacja:nazwaGracza()	
	return ffi.C.pobierzNazweAktualnegoGracza()
end

function Aplikacja:wlaczTesty()	
	ffi.C.testyJednostkowe()
end

function Aplikacja:wybudujObiekt( id , parametr )	
	ffi.C.wybudujObiekt( id, parametr )
end

Zdarzenie = class(function(o)
	o.idStanu_ = nil
	o.numer_ = nil
	o.idZdarzenia_ = nil
	end)

function Zdarzenie:pobierz() 	
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	ret = ffi.C.pobierzZdarzenie(zdarzenie)
	if ret == true then
		self.idStanu_ = zdarzenie.idStanu_
		self.numer_ = zdarzenie.numer_
		self.idZdarzenia_ = zdarzenie.idZdarzenia_
	end
	return ret
end

function Zdarzenie:wstaw()
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	zdarzenie.idStanu_ = self.idStanu_
	zdarzenie.numer_ = self.numer_
	zdarzenie.idZdarzenia_ = self.idZdarzenia_
	ffi.C.wstawZdarzenie(zdarzenie)
end

function Zdarzenie:kolejkuj()
	local zdarzenie = ffi.new('struct Zdarzenie_t')
	zdarzenie.idStanu_ = self.idStanu_
	zdarzenie.numer_ = self.numer_
	zdarzenie.idZdarzenia_ = self.idZdarzenia_
	ffi.C.kolejkujZdarzenie(zdarzenie)
end
	
function Zdarzenie:podlaczDoAktualnegoStanu()
	local stan = ffi.new('struct Stan_t')
	ret = ffi.C.pobierzAktualnyStan(stan)
	if ret == true then
		self.idStanu_ = stan.idStanu_
	end
	return ret
end

Stan = class(function(o)
	o.idStanu_ = nil
	o.numer_ = nil
	end)

function Stan:poprzedni()
	local stan = ffi.new('struct Stan_t')
	ret = ffi.C.pobierzPoprzedniStan(stan)
	if ret == true then
		self.idStanu_ = stan.idStanu_
		self.numer_ = stan.numer_
	end
	return ret
end

function Stan:aktualny()
	local stan = ffi.new('struct Stan_t')
	ret = ffi.C.pobierzAktualnyStan(stan)
	if ret == true then
		self.idStanu_ = stan.idStanu_
		self.numer_ = stan.numer_
	end
	return ret
end

function Stan:nastepny()
	local stan = ffi.new('struct Stan_t')
	ret = ffi.C.pobierzNastepnyStan(stan)
	if ret == true then
		self.idStanu_ = stan.idStanu_
		self.numer_ = stan.numer_
	end
	return ret
end

function Stan:ustawNastepny( id )
	ffi.C.ustawNowyStanNastepny( id )
end
function Stan:ustawNastepny()
	ffi.C.ustawNowyStanNastepny( self.idStanu_ )
end

function Stan:ustawNastepnyNumer( numer )
	ffi.C.ustawNowyNumerNastepny( numer )
end

function Stan:ustawNastepnyNumer( )
	ffi.C.ustawNowyNumerNastepny( self.numer_ )
end