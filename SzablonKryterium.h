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
		//--- Definicje typ�w lokalnych ---

		typedef std::shared_ptr<T> TypObiektu;
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana;

		//--- Metody domy�lne ---

		virtual ~SzablonKryterium() = default;

		SzablonKryterium(const SzablonKryterium&) = default;

		SzablonKryterium(SzablonKryterium&& obiekt) = default; /*{
			*this = std::move(obiekt);
		}*/

		SzablonKryterium& operator=(const SzablonKryterium&) = default;

		SzablonKryterium& operator=(SzablonKryterium&& obiekt) = default;/*{
			if (*this != &obiekt){
				zmiana_ = std::move(obiekt.zmiana_);
				obiekt_ = std::move(obiekt.obiekt_);
			}
			return *this;
		};*/

		//--- Metody usuni�te ---

		SzablonKryterium() = delete;

		//--- Metody statyczne ---

		//--- Konstruktory ---

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		SzablonKryterium(XmlBO::ElementWezla wezel){
			obiekt_ = std::make_shared<T>(wezel);
			zmiana_ = Utils::TworzZmiane(XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_ZMIANA));
		}

		//--- Destruktor ---

		//--- Operatory ---

		//--- Metody wirtualne ---

		//--- Metody przeci��one ---
		
		//--- Metody typu Get/Set ---

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

		//--- Pozosta�e metody ---
		
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

	private:

		//--- Atrybuty ---

		Zmiana zmiana_ = nullptr; /// Wska�nika na zmian� parametru obiektu.
		TypObiektu obiekt_ = nullptr; /// Wska�nik na obiekt.
	};
}
