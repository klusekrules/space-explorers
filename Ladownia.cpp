#include "Ladownia.h"

Ladownia::Ladownia( )
	: zajete( ) 
	, pojemnoscMax( ), obiekty()
	, przyrostPojemnoscMax( )
{
}

Ladownia::Ladownia( const Objetosc& isPojemnoscMax )
	: zajete( ) 
	, pojemnoscMax( isPojemnoscMax ), obiekty()
	, przyrostPojemnoscMax(  )
{
}

Ladownia::Ladownia( const Objetosc& isPojemnoscMax , const Fluktuacja& wzPrzyrost )
	: zajete( Stale::objetoscDomyslny ) 
	, pojemnoscMax( isPojemnoscMax ), obiekty(), przyrostPojemnoscMax( wzPrzyrost )
{
}

Ladownia::Ladownia( const Ladownia& lLadownia )
	: zajete( lLadownia.zajete) , pojemnoscMax( lLadownia.pojemnoscMax ) 
	, obiekty( lLadownia.obiekty ), przyrostPojemnoscMax( lLadownia.przyrostPojemnoscMax )
{
}

Ladownia::~Ladownia( ){
}

Fluktuacja Ladownia::WolneMiejsce() const{
	return Fluktuacja( 1.0 ) - ( zajete / pojemnoscMax );
}

Objetosc Ladownia::MaksymalnaPojemnosc() const{
	return Objetosc( pojemnoscMax * ( Fluktuacja(1.0) + przyrostPojemnoscMax ) );
}

Ilosc Ladownia::SprawdzIloscObiektow( const Klucz& itID ) const{
	try{
		return obiekty.get(itID).getIlosc();
	} catch( OgolnyWyjatek& ){
		return Ilosc();
	}
}
	
bool Ladownia::DodajObiektDoLadowni( const Item& obiekt ){
	if( obiekt.getObjetosc() > MaksymalnaPojemnosc() ){
		return false;
	}
	if( (obiekt.getObjetosc() + zajete) > MaksymalnaPojemnosc()){
		return false;
	}
	try{
		obiekty.add(obiekt);
		przeliczZajeteMiejsce();
	}catch(OgolnyWyjatek){
		return false;
	}
	return true;		
}	

Ladownia::Item& Ladownia::PobierzObiekt( const Klucz& itID, const Ilosc& isIlosc ) throw( NieznalezionoObiektu, NiepoprawnaIloscObiektow ){
	if(obiekty.isEmpty())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,itID.toString());

	try{
		Obiekt& o = obiekty.get(itID);
		if( isIlosc == o.getIlosc() ){
			obiekty.getAndDel(itID);
			przeliczZajeteMiejsce();
			return o;
		}

		if( isIlosc < o.getIlosc() ){
			Obiekt *k = o.Podziel(isIlosc);
			przeliczZajeteMiejsce();
			return *k;
		}

		if( isIlosc == Ilosc() ){
			throw NieznalezionoObiektu(EXCEPTION_PLACE,o.toString());
		}

		if( isIlosc > o.getIlosc() ){
			throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,isIlosc);
		}
	}catch( OgolnyWyjatek& ){
		throw;
	}	
	throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,isIlosc);
}

/* Zwrócony zbiornik ma objêtoœæ z przedzia³u  < min , max >  */
Ladownia::Zbiornik* Ladownia::PodzielLadownie( const Objetosc& max , const Objetosc& min ) throw( BladDzieleniaLadowni, NiepoprawneParametryFunkcji ){
	Zbiornik *zb = new Zbiornik();
	try{
		Zbiornik kopia(obiekty);
		Objetosc tObj ( 0.0 );
		Objetosc tMin ( min );

		//Je¿eli objetoœæ czekiwana jest równa 0 to zwracamy pusty zbior obiektów
		if( max == tObj )
			return zb;

		// Je¿eli objêtoœæ minimalna jest ujemna to j¹ zerujemy
		if( tMin < tObj )
			tMin = tObj;

		//Je¿eli objêtoœæ oczekiwana mniejsza od 0 lub objêtoœæ minimalna wiêksza od pojemnoœci 
		//lub objêtoœæ minimalna wiêksza od objêtoœci docelowej. Wyj¹tek
		if( max < tObj || min > zajete || min > max )
			throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , max , min );
	
		/*
			Przechodzimy po elementach zbiornika i przepisujemy tyle ile siê da. Dopuszczamy dzielenie grup obiektów jeœli mo¿liwe.
		*/
		for( auto o : obiekty){
			Objetosc objElementu(o.second->getObjetosc());
			if( objElementu + tObj <= max ){
				if(Zbiornik::move(o.first, kopia , *zb)){
					tObj += objElementu;
				}
			}else{
				Objetosc objPojedyncza( objElementu.value() / o.second->getIlosc().value() );
				if( max - tObj >= objPojedyncza ){
					Ilosc liczbaElementow( floorl(( max.value() - tObj.value() ) / objPojedyncza.value()) );
					if( liczbaElementow >= Ilosc(1.0) ){
						if(Zbiornik::move(o.first,liczbaElementow, kopia , *zb)){
							tObj += Objetosc( objPojedyncza.value() * liczbaElementow.value() );
						}
					}
				}
			}
			if(tObj >= tMin)
				break;
		}
		if(tObj >= tMin){
			obiekty = kopia;
			przeliczZajeteMiejsce();
		}else{
			throw BladDzieleniaLadowni( EXCEPTION_PLACE, this->toString() );
		}
	}catch(...){
		delete zb;
		throw;
	}
	return zb;
}

void Ladownia::przeliczZajeteMiejsce(){
	zajete=Objetosc(0);
	for( auto o : obiekty){
		zajete += o.second->getObjetosc();
	}
}

Masa Ladownia::getMasaZawartosciLadowni(){
	Masa m (0);
	for( auto o : obiekty){
		m += o.second->getMasa();
	}
	return m;
}

Ladownia::ListaKluczy Ladownia::PobierzListeIdObiektow() const{
	return obiekty.rawKluczList();
}

const Ladownia::Zbiornik& Ladownia::getPrzewozoneObiekty() const{
	return obiekty;
}

void Ladownia::setPrzeworzoneObiekty( const Zbiornik& a ){
	obiekty = a;
}

const Objetosc& Ladownia::getZajeteMiejsce() const{
	return zajete;
}

void Ladownia::setZajeteMiejsce( const Objetosc& isPojemnosc ){
	zajete = isPojemnosc;
}

const Objetosc& Ladownia::getPojemnoscMax() const{
	return pojemnoscMax;
}

void Ladownia::setPojemnoscMax( const Objetosc& isPojemnoscMax ){
	pojemnoscMax=isPojemnoscMax;
}

const Fluktuacja& Ladownia::getPrzyrostPojemnoscMax() const{
	return przyrostPojemnoscMax;
}

void Ladownia::setPrzyrostPojemnoscMax( const Fluktuacja& wzPrzyrost ){
	przyrostPojemnoscMax = wzPrzyrost;
}

string Ladownia::toString() const{
	Logger str("Ladownia");
	str.addField("Zajete Miejsce",zajete);
	str.addField("Pojemnosc Maksymalna",pojemnoscMax);
	str.addField("Przyrost Pojemnosci",przyrostPojemnoscMax);
	str.addField("Zawartosc Ladowni",obiekty);
	return str.toString();
}