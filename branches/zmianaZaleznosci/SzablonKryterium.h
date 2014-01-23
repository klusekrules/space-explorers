#pragma once
#include "Zmiana\ZmianaInterfejs.h"
#include "Parser\XmlBO.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include <functional>

namespace SpEx{

	/**
	* \brief Szablon do tworzenia klasy koszt�w lub wymog�w.
	*
	* Zarz�dza kosztem lub wymogiem.
	* \author Daniel Wojdak
	* \version 1
	* \date 23-07-2013
	*/
	template< class T >
	class SzablonKryterium
	{
	public:
		typedef std::shared_ptr<T> TypObiektu;
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \param[in] nazwa - Nazwa w�z�a obiektu.
		*/
		SzablonKryterium(XmlBO::ElementWezla wezel)
			: obiekt_(nullptr), zmiana_(nullptr)
		{
			obiekt_ = std::make_shared<T>(wezel);
			zmiana_ = Utils::TworzZmiane(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_ZMIANA));
		}

		/**
		* \brief Metoda wykonuj�ca akcje na obiekcie.
		*
		* Metoda wykonuje dowoln� akcj� na obiekcie.
		* \param[in,out] funkcja - Funktor wykonuj�cy akcje na obiekcie.
		* \return Warto�� zwracana przez funktor.
		*/
		bool wykonaj(std::function<bool(TypObiektu, Zmiana)> funkcja){
			return funkcja(obiekt_, zmiana_);
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
}
