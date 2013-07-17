#pragma once
#include "Logger\LoggerInterface.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "parser\ticpp.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include <functional>

template< class T >
class SzablonKosztow :
	virtual public LoggerInterface
{
public:
	typedef shared_ptr<T> TypObiektu;
	typedef shared_ptr<ZmianaInterfejs> Zmiana;
	SzablonKosztow( TiXmlElement* wezel , string nazwa ) 
		: obiekt_(nullptr), zmiana_(nullptr)
	{
		if(wezel){
			TiXmlElement* element = XmlBO::ZnajdzWezel<NOTHROW>(wezel,nazwa);
			if(element){
				obiekt_ = TypObiektu(new T(element));
				zmiana_ = Utils::TworzZmiane(XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_ZMIANA));
			}
		}
	}

	virtual ~SzablonKosztow(void)
	{
	}

	bool wykonaj( function<bool(TypObiektu,Zmiana)> funkcja ){
		return funkcja(obiekt_,zmiana_);
	}

	string napis()const{
		return string();
	}
private:
	Zmiana zmiana_;
	TypObiektu obiekt_;
};

