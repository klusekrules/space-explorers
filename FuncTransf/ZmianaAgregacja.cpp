#include "ZmianaAgregacja.h"
#include "..\XmlBO.h"
#include "ZmianaFabryka.h"
#include "..\Logger\Logger.h"

ZmianaAgregacja::ZmianaAgregacja( const ticpp::Element* e )
	: ZmianaDekorator( XmlBO::IterateChildrenElementIf<NOTHROW>(e,"Zmiana","for","next") )
{
	if( e && zFabryka ){
		for( auto n = e->IterateChildren("Zmiana", XmlBO::IterateChildrenElement<NOTHROW>(e,"Zmiana") ); n ; n = e->IterateChildren("Zmiana",n) ){
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
	: ZmianaDekorator(e)
{
	for(auto a : e.list){
		if(a.get())
			list.push_back(shared_ptr<ZmianaInterfejs>(a->Kopia()));
	}
}

ZmianaAgregacja& ZmianaAgregacja::operator=( const ZmianaAgregacja& e){
	ZmianaDekorator::operator=(e);
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
	long double v = ZmianaDekorator::value(d,p,planeta);
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
	str.addClass(ZmianaDekorator::toString());
	for( auto a : list){
		if(a.get())
			str.addField("Brat",*a);
	}
	return str.toString();
}