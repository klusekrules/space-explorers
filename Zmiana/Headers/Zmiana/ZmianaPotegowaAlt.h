#pragma once
#include "ZmianaParametr.h"
#include "ZmianaFabryka.h"

namespace SZmi{
	/**
	* \brief Klasa reprezentuj�ca zmian� pot�gow� alternatywna.
	*
	* Spos�b dzia�ania metody wyliczajacej:
	*	- Warto�� atrybutu mno�ona jest przez wsp�czynik pobrany z parametru i to mno�one jest przez poziom podniesiony do pot�gi oblicznej przez zmian� wczytan� do atrybutu wykladnik_. ( wartosc * wspolczynnik_ * poziom^wykladnik_ )
	* \author Daniel Wojdak
	* \version 1
	* \date 11-07-2013
	*/
	class ZMIANA_API ZmianaPotegowaAlt :
		public ZmianaInterfejs,
		virtual public SLog::LoggerInterface
	{
	private:
		static ZmianaFabryka* fabryka_; ///  Wska�nik na fabryk� zmian.
		static const int identyfikator_; /// Identyfikator klasy przekazywany do fabryki.

		/**
		* Metoda tworz�ca obiekt a podstawie w�z�a.
		* \param[in] wezel - W�ze� na podstawie kt�rego tworzony jest obiekt.
		* \return Wska�nika na obiekt utworzonej zmiany.
		*/
		static ZmianaInterfejs* TworzZmianaPotegowaAlt(XmlBO::ElementWezla wezel);

		ZmianaParametr wspolczynnik_; /// Wsp�czynnik liniowy.
		std::shared_ptr<ZmianaInterfejs> wykladnik_; /// Wyk�adnik pot�gi.

	public:

		/**
		* Metoda rejestruj�ca klas� w fabryce.
		* \param[in] fabryka - Referencja do globalnej fabryki.
		* \return Metoda zwraca warto�� true, je�eli uda si� zarejestrowa� klas�. Je�eli wyst�pi� b��d zwr�cona jest warto�� false.
		* \sa ZmianaFabryka
		*/
		static bool RejestrujZmianaPotegowaAlt(ZmianaFabryka &fabryka);

		/**
		* Metoda wyliczaj�ca warto��.
		* Spos�b dzia�ania metod policzWartosc klasy zmiana agregacja:
		*	- Warto�� atrybutu mno�ona jest przez wsp�czynik pobrany z parametru i to mno�one jest przez poziom podniesiony do pot�gi oblicznej przez zmian� wczytan� do atrybutu wykladnik_. ( wartosc * wspolczynnik_ * poziom^wykladnik_ )
		* \param[in] wartosc - podstawowa warto�� parametru, dla k�trego b�dzie wyliczana modyfikacja warto�ci.
		* \param[in] poziom - poziom obiektu, dla kt�rego b�dzie wyliczana modyfikacja warto�ci.
		* \param[in] identyfikatorPlanety - identyfikator planety, na kt�rej znajduje si� obiekt.
		* \return Przeliczona warto�� atryutu.
		*/
		long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const override;

		/**
		* Metoda tworzy kopi� obiektu.
		* \return Wska�nik do kopii obiektu.
		* \warning Zwr�cony wska�nik musi zostac zwolniony operatorem delete.
		*/
		ZmianaPotegowaAlt* Kopia()const override;

		/**
		* Konstruktor obiektu na podstawie w�z�a XML.
		* \param[in] wezel - Wezel drzewa xml.
		* \pre W�ze� musi zawiera� nast�puj�c� struktur�
		* \code {.xml}
		*	<Zmiana id="n">
		*		<Param wspolczynnik="3.0"/>
		*		<Zmiana id="x">
		*		</Zmiana>
		*	</Zmiana>
		* \endcode
		* Parametr \<Param id="1" wspolczynnik="3.0"/\> to wspolczynnik_, a zmiana \<Zmiana id="x"\> to wykladnik_.
		*/
		explicit ZmianaPotegowaAlt(XmlBO::ElementWezla wezel);

		/**
		* Destruktor
		*/
		virtual ~ZmianaPotegowaAlt() = default;

		/**
		* Metoda tworz�ca napis zawieraj�cy opis obiektu.
		* \return Opis obiektu.
		*/
		std::string napis() const override;

	};
}
