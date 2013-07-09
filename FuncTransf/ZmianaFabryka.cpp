#include "ZmianaFabryka.h"

ZmianaFabryka::ZmianaFabryka()
{
}

ZmianaFabryka::ZmianaFabryka( const ZmianaFabryka& a)
{
}

ZmianaFabryka& ZmianaFabryka::operator=(const ZmianaFabryka& a){
	callbacks_ = a.callbacks_;
	return *this;
}

ZmianaFabryka::~ZmianaFabryka()
{
}

bool ZmianaFabryka::RejestracjaZmiany(int id, KreatorZmiany funkcja){
	if(callbacks_.find(id)!=callbacks_.end())
		return false;
	callbacks_[id] = funkcja;
	return true;
}

ZmianaFabryka& ZmianaFabryka::pobierzInstancje(){
	static ZmianaFabryka a;
	return a;
}


shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz( TiXmlElement* e ){
	if(e){
		string str = e->Attribute("id");
		if(str.empty())
			return nullptr;
			//throw BrakAtrybutuXML(EXCEPTION_PLACE,Tekst("id"));
		int id = stoi( str, nullptr, 0 );
		auto i = callbacks_.find(id);
		if(i == callbacks_.end())
			return nullptr;
			//throw NieznalezionoObiektu(EXCEPTION_PLACE,str);
		return shared_ptr<ZmianaInterfejs>(callbacks_[id](e));
	}
	//throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Unexpected"),Tekst("Nieoczekiwane wystapienie bledu."));
	return nullptr;
}