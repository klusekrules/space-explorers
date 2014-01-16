#include "ZmianaAgregacja.h"
#include "..\XmlBO.h"
#include "ZmianaFabryka.h"
#include "..\Logger\Logger.h"
#include "..\definicjeWezlowXML.h"
#include "UtilsZmiana.h"

ZmianaAgregacja::ZmianaAgregacja( tinyxml2::XMLElement* wezel )
{
	if( wezel && fabryka_ ){
		tinyxml2::XMLElement* wezelNastepny = XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WARTOSC_ATRYBUTU_XML_NASTEPNY );
		if(!wezelNastepny)
			UtilsZmiana::generujWyjatekBleduStruktury(wezel);
		nastepna_ = fabryka_->Tworz(wezelNastepny);
		if(!nastepna_)
			UtilsZmiana::generujWyjatekBleduStruktury(wezelNastepny);

		tinyxml2::XMLElement* dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WARTOSC_ATRYBUTU_XML_BRAT );
		if(!dziecko)
			UtilsZmiana::generujWyjatekBleduStruktury(wezel);
		for( ; dziecko ; dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WARTOSC_ATRYBUTU_XML_BRAT, dziecko ) ){
			auto element = fabryka_->Tworz(dziecko);
			if(element)
				listaZmian_.push_back(element);
			else
				UtilsZmiana::generujWyjatekBleduStruktury(dziecko);
		}
	}
}

ZmianaInterfejs* ZmianaAgregacja::TworzZmianaAgregacja( tinyxml2::XMLElement* wezel ){
	return new ZmianaAgregacja(wezel);
}

ZmianaAgregacja* ZmianaAgregacja::Kopia()const{
	return new ZmianaAgregacja(*this);
}

ZmianaAgregacja::ZmianaAgregacja( const ZmianaAgregacja& obiekt )
	: nastepna_(nullptr)
{
	this->operator=(obiekt);
}

ZmianaAgregacja& ZmianaAgregacja::operator=( const ZmianaAgregacja& obiekt ){
	if(obiekt.nastepna_)
		nastepna_ = std::shared_ptr<ZmianaInterfejs>(obiekt.nastepna_->Kopia());
	else
		nastepna_ = nullptr;
	for(auto element : obiekt.listaZmian_){
		if(element)
			listaZmian_.push_back(std::shared_ptr<ZmianaInterfejs>(element->Kopia()));
	}
	return *this;
}

long double ZmianaAgregacja::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety)const{
	long double rezultat = nastepna_->policzWartosc( wartosc, poziom, identyfikatorPlanety );
	long double suma = 0;
	for(auto element : listaZmian_){
		if(element)
			suma+=element->policzWartosc( rezultat, poziom, identyfikatorPlanety );
	}
	return suma;
}

bool ZmianaAgregacja::RejestrujZmianaAgregacja( ZmianaFabryka &fabryka ){
	fabryka_ = &fabryka;
	return fabryka.rejestracjaZmiany( identyfikator_, ZmianaAgregacja::TworzZmianaAgregacja );
}

std::string&& ZmianaAgregacja::napis() const{
	Logger str(NAZWAKLASY(ZmianaAgregacja));
	if(nastepna_)
		str.dodajPole( "Nastêpna", *nastepna_ );
	for( auto element : listaZmian_){
		if(element)
			str.dodajPole( "Brat", *element );
	}
	return str.napis();
}
