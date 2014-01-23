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
		typedef std::shared_ptr<T> TypObiektu;
		typedef std::shared_ptr<SZmi::ZmianaInterfejs> Zmiana;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \param[in] nazwa - Nazwa wêz³a obiektu.
		*/
		SzablonKryterium(XmlBO::ElementWezla wezel)
			: obiekt_(nullptr), zmiana_(nullptr)
		{
			obiekt_ = std::make_shared<T>(wezel);
			zmiana_ = Utils::TworzZmiane(XmlBO::ZnajdzWezel<THROW>(wezel, WEZEL_XML_ZMIANA));
		}

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
}
