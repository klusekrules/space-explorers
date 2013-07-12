#include "ZmianaAgregacja.h"
#include "..\XmlBO.h"
#include "ZmianaFabryka.h"
#include "..\Logger\Logger.h"
#include "..\definicjeWezlowXML.h"

ZmianaAgregacja::ZmianaAgregacja( TiXmlElement* wezel )
{
	if( wezel && fabryka_ ){
		nastepna_ = fabryka_->Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WARTOSC_ATRYBUTU_XML_NASTEPNY ));
		TiXmlElement* dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WARTOSC_ATRYBUTU_XML_BRAT );
		for( ; dziecko ; dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WARTOSC_ATRYBUTU_XML_BRAT, dziecko ) ){
			auto element = fabryka_->Tworz(dziecko->ToElement());
			if(element)
				listaZmian_.push_back(element);
		}
	}
}

ZmianaInterfejs* ZmianaAgregacja::TworzZmianaAgregacja( TiXmlElement* wezel ){
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
		nastepna_ = shared_ptr<ZmianaInterfejs>(obiekt.nastepna_->Kopia());
	else
		nastepna_ = nullptr;
	for(auto element : obiekt.listaZmian_){
		if(element)
			listaZmian_.push_back(shared_ptr<ZmianaInterfejs>(element->Kopia()));
	}
	return *this;
}

ZmianaAgregacja::~ZmianaAgregacja(){
}

long double ZmianaAgregacja::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety)const{
	if(!nastepna_)
		return wartosc;
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

string ZmianaAgregacja::toString() const{
	Logger str(NAZWAKLASY(ZmianaAgregacja));
	if(nastepna_)
		str.dodajPole( "Nastêpna", *nastepna_ );
	for( auto element : listaZmian_){
		if(element)
			str.dodajPole( "Brat", *element );
	}
	return str.toString();
}
