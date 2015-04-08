#pragma once
#include "Szkielet\EkranSzablon.h"

namespace SpEx{

	/**
	* \brief Klasa ekranu startowego.
	*
	* Klasa zarz¹dza ekranem startowym aplikajci.
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
		* Metoda tworzy ekran startowy na bazie danych zawartych w weŸle. Pod³¹cza ekran do okna.
		* \param[in] okno - Okno do którego zostanie pod³¹czony ekran.
		* \param[in] wezel - Weze³ do danych na podstawie których zostanie skonfigurowane okno.
		* \throw WyjatekParser
		*/
		EkranStartowy(sf::RenderWindow& okno, XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~EkranStartowy(void) = default;

		/**
		* \brief Metoda przeliczaj¹ca parametry ekranu wzglêdem aktualnego stanu.
		*
		* Metoda przelicza prametry ekranu w zale¿noœci od stanu jaki zosta³ przekazany jako parametr.
		* \param[inout] stan - Aktualnie przetwarzany stan aplikacji. 
		*/
		void uaktualnij(Stan& stan) override;

	protected:

		sf::WindowHandle okno_; /// Uchwyt do okna rodzica ekranu startowego.

		const Stan::KrokCzasu czasWlaczania_; /// Czas w milisekundach przez, który okna ma siê pojawiaæ na ekranie.
		const Stan::KrokCzasu czasTrwalosci_; /// Czas w milisekundach przez, który okna ma byæ widoczne, po pe³nym pojawieniu siê zamin wyœle komunikat.
		Stan::KrokCzasu czasChwilowy_; /// Zmienna pomocnicza przechowuj¹ca czas który up³yn¹³.

		STyp::Identyfikator idStanuWejscia_; /// Identyfikator stanu, dla którego okna ma reagowaæ.
		STyp::Identyfikator idZdarzeniaWyjscia_; /// Identyfikator zdarzenia jakie ma zostaæ wys³ane po up³ywie czasu trwa³oœci.
	};
};

