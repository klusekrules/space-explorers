#include "ZmianaDekorator.h"
#include "../Logger/Logger.h"
#include "ZmianaFabryka.h"

ZmianaDekorator::ZmianaDekorator( const ticpp::Element* e ){
	if(e){
		next = ZmianaFabryka::pobierzInstancje().Tworz(e);
	}
}
ZmianaDekorator::ZmianaDekorator( const ZmianaDekorator& e )
	: next( e.next->Kopia() )
{
}

ZmianaDekorator::~ZmianaDekorator(){
}

long double ZmianaDekorator::value( const long double& d, const Poziom& p )const{
	if(next.get())
		return next->value(d,p);
	return d;
}

ZmianaDekorator& ZmianaDekorator::operator=(const ZmianaDekorator& a){
	next = shared_ptr<ZmianaInterfejs>(a.next->Kopia());
	return *this;
}

ZmianaDekorator* ZmianaDekorator::Kopia()const{
	return new ZmianaDekorator(*this);
}

string ZmianaDekorator::toString () const{
	Logger str(CLASSNAME(ZmianaDekorator));
	if(next.get())
		str.addField("Dziecko",*next);
	return str.toString();
}

bool ZmianaDekorator::RejestrujZmianaDekotor(){
	return ZmianaFabryka::pobierzInstancje().RejestracjaZmiany(idKlasy,ZmianaDekorator::TworzZmianaDekorator);
}