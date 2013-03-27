#include "ZmianaFabryka.h"


ZmianaFabryka::ZmianaFabryka()
{
}




ZmianaFabryka::~ZmianaFabryka()
{
}


ZmianaFabryka& ZmianaFabryka::pobierzInstancje(){
	static ZmianaFabryka a;
	return a;
}


shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz( const ticpp::Element* e ){
	return nullptr;
}