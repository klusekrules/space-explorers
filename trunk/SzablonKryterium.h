#pragma once
#include "Zmiana\ZmianaInterfejs.h"
#include "Parser\XmlBO.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"
#include <functional>

namespace SpEx{

	/**
	* \brief Szablon do tworzenia klasy kosztów lub wymogów.
	*
	* Zarz¹dza kosztem lub wymogiem.
	* \author Daniel Wojdak
	* \version 1
	* \date 23-07-2013
	*/
	template< class T >
	class SzablonKryterium
	{
	public:
		//--- Definicje typów lokalnych ---

		typedef std::shared_ptr<T> TypObiektu;
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana;

		//--- Metody domyœlne ---

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

		//--- Metody usuniête ---

		SzablonKryterium() = delete;

		//--- Metody statyczne ---

		//--- Konstruktory ---

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		*/
		SzablonKryterium(XmlBO::ElementWezla wezel){
			obiekt_ = std::make_shared<T>(wezel);
			zmiana_ = Utils::TworzZmiane(XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_ZMIANA));
		}

		//--- Destruktor ---

		//--- Operatory ---

		//--- Metody wirtualne ---

		//--- Metody przeci¹¿one ---
		
		//--- Metody typu Get/Set ---

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

		//--- Pozosta³e metody ---
		
		/**
		* \brief Metoda wykonuj¹ca akcje na obiekcie.
		*
		* Metoda wykonuje dowoln¹ akcjê na obiekcie.
		* \param[in,out] funkcja - Funktor wykonuj¹cy akcje na obiekcie.
		* \return Wartoœæ zwracana przez funktor.
		*/
		bool wykonaj(std::function<bool(TypObiektu, Zmiana)> funkcja){
			return funkcja(obiekt_, zmiana_);
		}

	private:

		//--- Atrybuty ---

		Zmiana zmiana_ = nullptr; /// WskaŸnika na zmianê parametru obiektu.
		TypObiektu obiekt_ = nullptr; /// WskaŸnik na obiekt.
	};
}
