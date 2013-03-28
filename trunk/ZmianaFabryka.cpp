#include "ZmianaFabryka.h"

ZmianaFabryka::ZmianaFabryka()
{
}

ZmianaFabryka::ZmianaFabryka( const ZmianaFabryka& a)
{
}

ZmianaFabryka& ZmianaFabryka::operator=(const ZmianaFabryka& a){
	return *this;
}

ZmianaFabryka::~ZmianaFabryka()
{
}

bool ZmianaFabryka::RejestracjaZmiany(IdType id, KreatorZmiany funkcja){
	if(callbacks_.find(id)!=callbacks_.end())
		return false;
	callbacks_[id] = funkcja;
	return true;
}

ZmianaFabryka& ZmianaFabryka::pobierzInstancje(){
	static ZmianaFabryka a;
	return a;
}


shared_ptr<ZmianaInterfejs> ZmianaFabryka::Tworz( const ticpp::Element* e ){
	if(e){
		string str = e->GetAttribute("id");
		Log::debug(str);
		if(str.empty())
			throw BrakAtrybutuXML(EXCEPTION_PLACE,Tekst("id"));
		IdType id( stoi( str, nullptr, 0 ));
		auto i = callbacks_.find(id);
		if(i == callbacks_.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE,str);
		return shared_ptr<ZmianaInterfejs>(callbacks_[id](e));
	}
	//throw OgolnyWyjatek(EXCEPTION_PLACE,IdType(-1),Tekst("Unexpected"),Tekst("Nieoczekiwane wystapienie bledu."));
	return nullptr;
}