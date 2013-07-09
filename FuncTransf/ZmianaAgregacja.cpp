#include "ZmianaAgregacja.h"
#include "..\XmlBO.h"
#include "ZmianaFabryka.h"
#include "..\Logger\Logger.h"

ZmianaAgregacja::ZmianaAgregacja( TiXmlElement* e )
{
	if( e && zFabryka ){
		next = zFabryka->Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,"Zmiana","for","next"));
		for( TiXmlElement* n = XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,"Zmiana","for","next")->NextSiblingElement("Zmiana"); n ; n = n->NextSiblingElement("Zmiana") ){
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

long double ZmianaAgregacja::value( const long double& d, const int& p, const int& planeta )const{
	if(!next)
		return d;
	long double v = next->value(d,p,planeta);
	long double suma = 0;
	for(auto e : list){
		if(e.get())
			suma+=e->value(v,p,planeta);
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