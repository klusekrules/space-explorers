#include "Ladownia.h"
#include "LadowniaInfo.h"
#include "Statek.h"
#include "Surowce.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

Ladownia::Ladownia( const Poziom& p, const IdType& idP, const LadowniaInfo& l )
	: PodstawoweParametry(p, idP), obiekty(), zajete(), ladowniaInfo(l)
{
}

Ladownia::Ladownia( const PodstawoweParametry& p, const LadowniaInfo& l )
	: PodstawoweParametry(p), obiekty(), zajete(), ladowniaInfo(l)
{
}

Fluktuacja Ladownia::WolneMiejsce() const{
	return Fluktuacja( 1.0 ) - ( zajete / getPojemnoscMax() );
}

Ilosc Ladownia::SprawdzIloscObiektow( const Klucz& itID ) const{
	try{
		return obiekty.get(itID).getIlosc();
	} catch( OgolnyWyjatek& ){
		return Ilosc();
	}
}

bool Ladownia::Polacz( Ladownia& l ){
	obiekty.moveAll(l.obiekty);
	return true;
}

bool Ladownia::czMoznaDodacDoLadownii( const Statek& c ) const {
	return true;
}

bool Ladownia::czMoznaDodacDoLadownii( const Surowce& c ) const {
	return c.czyTypPrzyrostowy();
}

bool Ladownia::DodajObiektDoLadowni( Item& obiekt ){
	if(!obiekt.czMoznaDodacDoLadownii(*this)){
		return false;
	}
	if( obiekt.getObjetosc() > getPojemnoscMax() ){
		return false;
	}
	if( (obiekt.getObjetosc() + zajete) > getPojemnoscMax()){
		return false;
	}
	try{
		obiekty.add(obiekt);
		przeliczZajeteMiejsce();
	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().warn(e.generujKomunikat());
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

/* Zwr�cony zbiornik ma obj�to�� z przedzia�u  < min , max >  */
Ladownia::Zbiornik* Ladownia::PodzielLadownie( const Objetosc& oMax , const Objetosc& oMin ) throw( BladDzieleniaLadowni, NiepoprawneParametryFunkcji ){
	Zbiornik *zb = new Zbiornik();
	try{
		Zbiornik kopia(obiekty);
		Objetosc tObj ( 0.0 );
		Objetosc tMin ( oMin );

		//Je�eli objeto�� czekiwana jest r�wna 0 to zwracamy pusty zbior obiekt�w
		if( oMax == tObj )
			return zb;

		// Je�eli obj�to�� minimalna jest ujemna to j� zerujemy
		if( tMin < tObj )
			tMin = tObj;

		//Je�eli obj�to�� oczekiwana mniejsza od 0 lub obj�to�� minimalna wi�ksza od pojemno�ci 
		//lub obj�to�� minimalna wi�ksza od obj�to�ci docelowej. Wyj�tek
		if( oMax < tObj || oMin > zajete || oMin > oMax )
			throw NiepoprawneParametryFunkcji( EXCEPTION_PLACE , oMax , oMin );
	
		/*
			Przechodzimy po elementach zbiornika i przepisujemy tyle ile si� da. Dopuszczamy dzielenie grup obiekt�w je�li mo�liwe.
		*/
		for( auto o : obiekty){
			Objetosc objElementu(o.second->getObjetosc());
			if( objElementu + tObj <= oMax ){
				if(Zbiornik::move(o.first, kopia , *zb)){
					tObj += objElementu;
				}
			}else{
				Objetosc objPojedyncza( objElementu() / o.second->getIlosc()() );
				if( oMax - tObj >= objPojedyncza ){
					Ilosc liczbaElementow( floorl(( oMax() - tObj() ) / objPojedyncza()) );
					if( liczbaElementow >= Ilosc(1.0) ){
						if(Zbiornik::move(o.first,liczbaElementow, kopia , *zb)){
							tObj += Objetosc( objPojedyncza() * liczbaElementow() );
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

Masa Ladownia::getMasaZawartosciLadowni()const {
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

const Objetosc& Ladownia::getZajeteMiejsce() const{
	return zajete;
}


Objetosc Ladownia::getPojemnoscMax() const{
	return ladowniaInfo.getPojemnoscMaksymalna(*this);
}

bool Ladownia::zapisz( TiXmlElement* e ) const {
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_LADOWNIA);
	e->LinkEndChild( n );
	n->SetAttribute(ATRYBUT_XML_ZAJETE_MIEJSCE,zajete.toString());
	for( auto o : obiekty){
		if(!o.second->zapisz(n))
			return false;
	}
	return true;
}

bool Ladownia::odczytaj (TiXmlElement* e) {
	if(e){
		auto c = e->Attribute(ATRYBUT_XML_ZAJETE_MIEJSCE);
		if(!c)
			return false;
		zajete(stod(c));
		try{
			for(TiXmlElement* n = e->FirstChildElement(); n != nullptr ; n = n->NextSiblingElement()){
				string c = n->Attribute(ATRYBUT_XML_IDENTYFIKATOR);
				if(c.empty())
					return false;
				Utils::trim(c);
				IdType id(stoi(c,nullptr,0));
				Obiekt* p = Aplikacja::getInstance().getGra().getObiekt(id).TworzEgzemplarz(Ilosc(),IdType());			
				if(!p->odczytaj(n) ){
					delete p;
					return false;
				}
				obiekty.add(p);
			}
		}catch(...){
			return false;
		}
		return true;
	}
	return false;
}

string Ladownia::toString() const{
	Logger str(CLASSNAME(Ladownia));
	str.addField("Zajete Miejsce",zajete);
	str.addField(CLASSNAME(Zbiornik),obiekty);
	str.addField(CLASSNAME(LadowniaInfo)+"ID",ladowniaInfo.getId());
	return str.toString();
}