#pragma once
#include "FuncTransf\ZmianaInterfejs.h"
#include "parser\ticpp.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include "OgolnyWyjatek.h"
#include <functional>
/**
* \brief Szablon do tworzenia klasy koszt�w lub wymog�w.
* 
* Zarz�dza kosztem lub wymogiem.
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
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	* \param[in] nazwa - Nazwa w�z�a obiektu.
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
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml, z metod� tworz�c� zdefiniowan� przez u�ytkownika.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	* \param[in] nazwa - Nazwa w�z�a obiektu.
	* \param[in] funkcjaTworzaca - Metoda kt�ra tworzy obiekt z w�z�a xml.
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
	* \brief Metoda wykonuj�ca akcje na obiekcie.
	*
	* Metoda wykonuje dowoln� akcj� na obiekcie.
	* \param[in,out] funkcja - Funktor wykonuj�cy akcje na obiekcie.
	* \return Warto�� zwracana przez funktor.
	*/
	bool wykonaj( function<bool(TypObiektu,Zmiana)> funkcja ){
		return funkcja(obiekt_,zmiana_);
	}

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* \return Wska�nik na przechowywany obiekt.
	*/
	TypObiektu pobierzObiekt() const{
		return obiekt_;
	}

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* \return Wska�nik na przechowywan� zmian�.
	*/
	Zmiana pobierzZmiane()const{
		return zmiana_;
	}

private:
	Zmiana zmiana_; /// Wska�nika na zmian� parametru obiektu.
	TypObiektu obiekt_; /// Wska�nik na obiekt.
};
