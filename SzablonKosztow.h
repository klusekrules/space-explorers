#pragma once
#include "FuncTransf\ZmianaInterfejs.h"
#include "parser\ticpp.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include "OgolnyWyjatek.h"
#include <functional>
/**
* \brief Szablon do tworzenia klasy kosztów lub wymogów.
* 
* Zarz¹dza kosztem lub wymogiem.
* \author Daniel Wojdak
* \version 1
* \date 23-07-2013
*/
template< class T >
class SzablonKosztow
{
public:
	typedef shared_ptr<T> TypObiektu;
	typedef shared_ptr<ZmianaInterfejs> Zmiana;

	/**
	* \brief Konstruktor.
	*
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	* \param[in] nazwa - Nazwa wêz³a obiektu.
	*/
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
	
	/**
	* \brief Konstruktor.
	*
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml, z metod¹ tworz¹c¹ zdefiniowan¹ przez u¿ytkownika.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	* \param[in] nazwa - Nazwa wêz³a obiektu.
	* \param[in] funkcjaTworzaca - Metoda która tworzy obiekt z wêz³a xml.
	*/
	SzablonKosztow( TiXmlElement* wezel , string nazwa, function< TypObiektu(TiXmlElement*) > funkcjaTworzaca ) 
		: obiekt_(nullptr), zmiana_(nullptr)
	{
		if(wezel){
			TiXmlElement* element = XmlBO::ZnajdzWezel<NOTHROW>(wezel,nazwa);
			if(element){
				obiekt_ = funkcjaTworzaca(element);
				if(!obiekt_)
					Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,element);
				zmiana_ = Utils::TworzZmiane(XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_ZMIANA));
			}
		}
	}

	/**
	* \brief Metoda wykonuj¹ca akcje na obiekcie.
	*
	* Metoda wykonuje dowoln¹ akcjê na obiekcie.
	* \param[in,out] funkcja - Funktor wykonuj¹cy akcje na obiekcie.
	* \return Wartoœæ zwracana przez funktor.
	*/
	bool wykonaj( function<bool(TypObiektu,Zmiana)> funkcja ){
		return funkcja(obiekt_,zmiana_);
	}

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* \return WskaŸnik na przechowywany obiekt.
	*/
	TypObiektu pobierzObiekt() const{
		return obiekt_;
	}

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* \return WskaŸnik na przechowywan¹ zmianê.
	*/
	Zmiana pobierzZmiane()const{
		return zmiana_;
	}

private:
	Zmiana zmiana_; /// WskaŸnika na zmianê parametru obiektu.
	TypObiektu obiekt_; /// WskaŸnik na obiekt.
};
