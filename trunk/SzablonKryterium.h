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
		typedef std::shared_ptr<T> TypObiektu; /// Typ obiektu przechowywanego w szablonie.
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana; /// Typ zmiany przechowywanej w szablonie.
		
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~SzablonKryterium() = default;

		/**
		* \brief Domy�lny konstruktor kopiuj�cy.
		*
		* Domy�lny konstruktor kopiuj�cy.
		* \param[in] obiekt - Obiekt �r�d�owy.
		*/
		SzablonKryterium(const SzablonKryterium& obiekt) = default;

		/**
		* \brief Domy�lny konstruktor przenosz�cy.
		*
		* Domy�lny konstruktor przenosz�cy.
		* \param[inout] obiekt - Obiekt �r�d�owy.
		*/
		SzablonKryterium(SzablonKryterium&& obiekt) = default;

		/**
		* \brief Domy�lny operator kopiuj�cy.
		*
		* Domy�lny operator kopiuj�cy.
		* \param[inout] obiekt - Obiekt �r�d�owy.
		* \return Referencja do obiektu.
		*/
		SzablonKryterium& operator=(const SzablonKryterium& obiekt) = default;

		/**
		* \brief Domy�lny operator przenosz�cy.
		*
		* Domy�lny operator przenosz�cy.
		* \param[inout] obiekt - Obiekt �r�d�owy.
		* \return Referencja do obiektu.
		*/
		SzablonKryterium& operator=(SzablonKryterium&& obiekt) = default;

		/**
		* \brief Konstruktor.
		*/
		SzablonKryterium() = delete;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		SzablonKryterium(XmlBO::ElementWezla wezel){
			obiekt_ = std::make_shared<T>(wezel);
			zmiana_ = Utils::TworzZmiane(XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_ZMIANA));
		}

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* \return Wska�nik na przechowywany obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		TypObiektu pobierzObiekt() const{
			return obiekt_;
		}

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* \return Wska�nik na przechowywan� zmian�.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		Zmiana pobierzZmiane()const{
			return zmiana_;
		}

		/**
		* \brief Metoda wykonuj�ca akcje na obiekcie.
		*
		* Metoda wykonuje dowoln� akcj� na obiekcie.
		* \param[in,out] funkcja - Funktor wykonuj�cy akcje na obiekcie.
		* \return Warto�� zwracana przez funktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		bool wykonaj(std::function<bool(TypObiektu, Zmiana)> funkcja){
			return funkcja(obiekt_, zmiana_);
		}

	private:
		Zmiana zmiana_ = nullptr; /// Wska�nika na zmian� parametru obiektu.
		TypObiektu obiekt_ = nullptr; /// Wska�nik na obiekt.
	};
}
