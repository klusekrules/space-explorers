#pragma once
#include "Zmiana\ZmianaInterfejs.h"
#include "Parser\XmlBO.h"
#include <functional>

namespace SpEx{

	//Klasa stworzona w celu pozbycia siê k³opotliwych zale¿noœci plików nag³ówkowych.
	class SzablonKryteriumPriv{
	public:
		static std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla);
	};

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
		typedef std::shared_ptr<T> TypObiektu; /// Typ obiektu przechowywanego w szablonie.
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana; /// Typ zmiany przechowywanej w szablonie.
		
		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~SzablonKryterium() = default;

		/**
		* \brief Domyœlny konstruktor kopiuj¹cy.
		*
		* Domyœlny konstruktor kopiuj¹cy.
		* \param[in] obiekt - Obiekt Ÿród³owy.
		*/
		SzablonKryterium(const SzablonKryterium& obiekt) = default;

		/**
		* \brief Domyœlny konstruktor przenosz¹cy.
		*
		* Domyœlny konstruktor przenosz¹cy.
		* \param[inout] obiekt - Obiekt Ÿród³owy.
		*/
		SzablonKryterium(SzablonKryterium&& obiekt) = default;

		/**
		* \brief Domyœlny operator kopiuj¹cy.
		*
		* Domyœlny operator kopiuj¹cy.
		* \param[inout] obiekt - Obiekt Ÿród³owy.
		* \return Referencja do obiektu.
		*/
		SzablonKryterium& operator=(const SzablonKryterium& obiekt) = default;

		/**
		* \brief Domyœlny operator przenosz¹cy.
		*
		* Domyœlny operator przenosz¹cy.
		* \param[inout] obiekt - Obiekt Ÿród³owy.
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
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		SzablonKryterium(XmlBO::ElementWezla wezel)
			: obiekt_ (std::make_shared<T>(wezel)),
			zmiana_(SzablonKryteriumPriv::TworzZmiane(wezel)){
		}

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* \return WskaŸnik na przechowywany obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		TypObiektu pobierzObiekt() const{
			return obiekt_;
		}

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* \return WskaŸnik na przechowywan¹ zmianê.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		Zmiana pobierzZmiane()const{
			return zmiana_;
		}

		/**
		* \brief Metoda wykonuj¹ca akcje na obiekcie.
		*
		* Metoda wykonuje dowoln¹ akcjê na obiekcie.
		* \param[in,out] funkcja - Funktor wykonuj¹cy akcje na obiekcie.
		* \return Wartoœæ zwracana przez funktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 23-07-2013
		*/
		bool wykonaj(std::function<bool(TypObiektu, Zmiana)> funkcja){
			return funkcja(obiekt_, zmiana_);
		}

	private:
		Zmiana zmiana_ = nullptr; /// WskaŸnika na zmianê parametru obiektu.
		TypObiektu obiekt_ = nullptr; /// WskaŸnik na obiekt.
	};
}
