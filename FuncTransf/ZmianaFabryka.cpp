#include "ZmianaFabryka.h"
#include "..\XmlBO.h"
#include "..\definicjeWezlowXML.h"

ZmianaFabryka::ZmianaFabryka()
{
}

ZmianaFabryka::ZmianaFabryka( const ZmianaFabryka& obiekt )
	: callbacks_ ( obiekt.callbacks_ )
{
}

ZmianaFabryka& ZmianaFabryka::operator=( const ZmianaFabryka& obiekt ){
	callbacks_ = obiekt.callbacks_;
	return *this;
}

bool ZmianaFabryka::rejestracjaZmiany( int id, KreatorZmiany funkcja ){
	if( funkcja==nullptr || id==0 || callbacks_.find(id)!=callbacks_.end() )
		return false;
	callbacks_[id] = funkcja;
	return true;
}

ZmianaFabryka& ZmianaFabryka::pobierzInstancje(){
	static ZmianaFabryka instancja;
	return instancja;
}

shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz( TiXmlElement* wezel ) const {
	if(wezel){
		int id = XmlBO::WczytajAtrybut<int>( wezel, ATRYBUT_XML_IDENTYFIKATOR , 0 );
		if(id==0)
			return nullptr;
		auto iterator = callbacks_.find(id);
		if(iterator == callbacks_.end())
			return nullptr;
		return shared_ptr<ZmianaInterfejs>( iterator->second(wezel) );
	}
	return nullptr;
}
