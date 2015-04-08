#pragma once
#include "Szkielet\EkranSzablon.h"

namespace SpEx{

	/**
	* \brief Klasa ekranu startowego.
	*
	* Klasa zarz�dza ekranem startowym aplikajci.
	* \author Daniel Wojdak
	* \version 1
	* \date 05-06-2014
	*/
	class EkranStartowy :
		public EkranSzablon
	{
	public:
		/**
		* \brief Konstruktor.
		*
		* Metoda tworzy ekran startowy na bazie danych zawartych w we�le. Pod��cza ekran do okna.
		* \param[in] okno - Okno do kt�rego zostanie pod��czony ekran.
		* \param[in] wezel - Weze� do danych na podstawie kt�rych zostanie skonfigurowane okno.
		* \throw WyjatekParser
		*/
		EkranStartowy(sf::RenderWindow& okno, XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~EkranStartowy(void) = default;

		/**
		* \brief Metoda przeliczaj�ca parametry ekranu wzgl�dem aktualnego stanu.
		*
		* Metoda przelicza prametry ekranu w zale�no�ci od stanu jaki zosta� przekazany jako parametr.
		* \param[inout] stan - Aktualnie przetwarzany stan aplikacji. 
		*/
		void uaktualnij(Stan& stan) override;

	protected:

		sf::WindowHandle okno_; /// Uchwyt do okna rodzica ekranu startowego.

		const Stan::KrokCzasu czasWlaczania_; /// Czas w milisekundach przez, kt�ry okna ma si� pojawia� na ekranie.
		const Stan::KrokCzasu czasTrwalosci_; /// Czas w milisekundach przez, kt�ry okna ma by� widoczne, po pe�nym pojawieniu si� zamin wy�le komunikat.
		Stan::KrokCzasu czasChwilowy_; /// Zmienna pomocnicza przechowuj�ca czas kt�ry up�yn��.

		STyp::Identyfikator idStanuWejscia_; /// Identyfikator stanu, dla kt�rego okna ma reagowa�.
		STyp::Identyfikator idZdarzeniaWyjscia_; /// Identyfikator zdarzenia jakie ma zosta� wys�ane po up�ywie czasu trwa�o�ci.
	};
};

