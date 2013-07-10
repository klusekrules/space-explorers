#include "ZmianaAgregacja.h"
#include "..\XmlBO.h"
#include "ZmianaFabryka.h"
#include "..\Logger\Logger.h"
#include "..\definicjeWezlowXML.h"

ZmianaAgregacja::ZmianaAgregacja( TiXmlElement* e )
{
	if( e && zFabryka ){
		next = zFabryka->Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WARTOSC_ATRYBUTU_XML_NASTEPNY));
		for( TiXmlElement* n = XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WARTOSC_ATRYBUTU_XML_NASTEPNY)->NextSiblingElement(WEZEL_XML_ZMIANA); n ; n = n->NextSiblingElement(WEZEL_XML_ZMIANA) ){
			auto e = zFabryka->Tworz(n->ToElement());
			if(e)
				list.push_back(e);
		}
	}
}

ZmianaAgregacja* ZmianaAgregacja::Kopia()const{
	return new ZmianaAgregacja(*this);
}

ZmianaAgregacja::ZmianaAgregacja( const ZmianaAgregacja& e)
	: next(nullptr)
{
	if(e.next)
		next = shared_ptr<ZmianaInterfejs>(e.next->Kopia());
	for(auto a : e.list){
		if(a.get())
			list.push_back(shared_ptr<ZmianaInterfejs>(a->Kopia()));
	}
}

ZmianaAgregacja& ZmianaAgregacja::operator=( const ZmianaAgregacja& e){
	if(e.next)
		next = shared_ptr<ZmianaInterfejs>(e.next->Kopia());
	else
		next = nullptr;
	for(auto a : e.list){
		if(a.get())
			list.push_back(shared_ptr<ZmianaInterfejs>(a->Kopia()));
	}
	return *this;
}

ZmianaAgregacja::~ZmianaAgregacja()
{
}

long double ZmianaAgregacja::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety)const{
	if(!next)
		return wartosc;
	long double v = next->policzWartosc(wartosc,poziom,identyfikatorPlanety);
	long double suma = 0;
	for(auto e : list){
		if(e.get())
			suma+=e->policzWartosc(v,poziom,identyfikatorPlanety);
	}
	return suma;
}

bool ZmianaAgregacja::RejestrujZmianaAgregacja( ZmianaFabryka &ref ){
	zFabryka = &ref;
	return ref.RejestracjaZmiany(idKlasy,ZmianaAgregacja::TworzZmianaAgregacja);
}

string ZmianaAgregacja::toString() const{
	Logger str(CLASSNAME(ZmianaAgregacja));
	if(next)
		str.addField("Next",*(next));
	for( auto a : list){
		if(a.get())
			str.addField("Brat",*a);
	}
	return str.toString();
}