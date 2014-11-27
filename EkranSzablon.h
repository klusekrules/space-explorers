#pragma once
#include "Stan.h"
#include "TGUI\Gui.hpp"
#include "LogListGui.h"

namespace SpEx{
	/**
	* \brief Klasa szablonowa dla nowych ekranow.
	*
	* Klasa bazowa dla klas ekranow. Najprostrza wersja klasy ekranu pozwalaj¹ca na wczytywnie danych z pliku. 
	* Dostarcza uniwersalny interfejs u¿ywany w aplikacji.
	* \author Daniel Wojdak
	* \version 3
	* \date 27-11-2014
	*/
	class EkranSzablon :
		public sf::Drawable,
		public sf::Transformable,
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Konstruktor.
		* 
		* Konstruktor buduj¹cy obiekt na podstawie wez³a z konfiguracj¹.
		* \param[in] wezel - Weze³ konfiguracyjny.
		* \throw WyjatekParser
		*/
		EkranSzablon(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~EkranSzablon() = default;

		/**
		* \brief Metoda przeliczaj¹ca parametry ekranu wzglêdem aktualnego stanu.
		*
		* Metoda przelicza prametry ekranu w zale¿noœci od stanu jaki zosta³ przekazany jako parametr.
		* \param[inout] stan - Aktualnie przetwarzany stan aplikacji.
		*/
		virtual void uaktualnij(Stan& stan);

		/**
		* \brief Metoda odbieraj¹ca zdarzenie.
		*
		* Metoda odbiera zdarzenie i przypisuje je do odpowiedniego okna nale¿¹cego do ekranu.
		* \param[inout] stan - Aktualnie przetwarzany stan aplikacji.
		* \param[in] zdarzenie - Wykryte zdarzenie.
		*/
		virtual void odbierz(Stan& stan, const sf::Event& zdarzenie);

		/**
		* \brief Metoda pod³¹czaj¹ca do okna.
		*
		* Metoda pod³¹cza ekran do okna przekazanego jako parametr.
		* \param[in] okno - Okno do którego zostaje pod³¹czony ekran.
		*/
		virtual void podlacz(sf::RenderWindow& okno);

		/**
		* \brief Metoda od³¹czaj¹ca do okna.
		*
		* Metoda od³¹cza ekran od okna przekazanego jako parametr.
		* \param[in] okno - Okno do którego zostaje pod³¹czony ekran.
		*/
		virtual void odlacz(sf::RenderWindow& okno);

		/**
		* \brief Metoda pobieraj¹ca identyfikator ekranu.
		*
		* Metoda zwraca aktualny identyfikator ekranu.
		* \return Aktualny identyfikator ekranu.
		*/
		const STyp::Identyfikator& pobierzId() const;

		/**
		* \brief Metoda pobieraj¹ca uchwyt do interfejsu GUI.
		* 
		* Metoda zwraca interfejs GUI na którym budowane s¹ okna danego ekranu.
		* \return Referencja do interfejsu GUI.
		*/
		tgui::Gui& pobierzGUI();


		/**
		* \brief Metoda czyszcz¹ca ekran.
		*
		* Metoda usuwa wszystkie okna znajduj¹ce siê na danym ekranie.
		*/
		virtual void clear();

		tgui::LogListGui::Ptr oknoKomunikatow_ = nullptr; /// WskaŸnik na okno komunikatów.

		/**
		* \brief Metoda tworz¹ca tekstowy opis obiektu.
		*
		* Metoda generuje czytelny tekstowy opis obiektu.
		* \return Opis obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 27-11-2014
		*/
		std::string napis() const override;

	protected:

		/**
		* \brief Metoda konfiguruj¹ca kontrolkê.
		*
		* Metoda Konfiguruje wczytan¹ przez ekran kontrolkê na podstawie wez³a konfiguracyjnego.
		* \param[in] wezel - Weze³ konfiguracyjny.
		* \param[in] kontrolka - WskaŸnik do kontrolki, która ma zostaæ skonfigurowana.
		* \throw WyjatekParser, BladKonfiguracjiEkranu
		*/
		bool wczytajDaneKontrolki(XmlBO::ElementWezla wezel, tgui::Widget::Ptr kontrolka);

		/**
		* \brief Metoda rysuj¹ca kontrolki.
		*
		* Metoda rysuj¹ca kontrolki na ekranie.
		* \param[in] target - unused.
		* \param[in] states - unused.
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		STyp::Identyfikator id_; /// Identyfikator ekranu.
		mutable tgui::Gui interfejs_; /// Interfejs GUI na którym tworzone s¹ kontrolki.
		
	};
};

