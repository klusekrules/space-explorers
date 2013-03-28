#include "ZmianaAgregacja.h"
#include "XmlBO.h"
#include "ZmianaFabryka.h"

ZmianaAgregacja::ZmianaAgregacja( const ticpp::Element* e )
	: ZmianaDekorator( XmlBO::IterateChildrenElement(e,"ZmianaNext") )
{
	if(e){
		for( auto n = e->IterateChildren("Zmiana",nullptr); n ; n = e->IterateChildren("Zmiana",n) ){
			list.push_back(ZmianaFabryka::pobierzInstancje().Tworz(n->ToElement()));
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

long double ZmianaAgregacja::value( const long double& d )const{
	long double v = ZmianaDekorator::value(d);
	long double suma = 0;
	for(auto e : list){
		if(e.get())
			suma+=e->value(v);
	}
	return suma;
}

bool ZmianaAgregacja::RejestrujZmianaAgregacja(){
	return ZmianaFabryka::pobierzInstancje().RejestracjaZmiany(idKlasy,ZmianaAgregacja::TworzZmianaAgregacja);
}

string ZmianaAgregacja::toString() const{
	Logger str(LogZmianaAgregacja::className());
	str.addClass(ZmianaDekorator::toString());
	for( auto a : list){
		if(a.get())
			str.addField("Brat",*a);
	}
	return str.toString();
}