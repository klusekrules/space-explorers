#pragma once
#include "Stan.h"
#include "TGUI\Gui.hpp"
#include "LogListGui.h"

namespace SpEx{
	/**
	* \brief Klasa szablonowa dla nowych ekranow.
	*
	* Klasa bazowa dla klas ekranow. Najprostrza wersja klasy ekranu pozwalaj�ca na wczytywnie danych z pliku. 
	* Dostarcza uniwersalny interfejs u�ywany w aplikacji.
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
		* Konstruktor buduj�cy obiekt na podstawie wez�a z konfiguracj�.
		* \param[in] wezel - Weze� konfiguracyjny.
		* \throw WyjatekParser
		*/
		EkranSzablon(XmlBO::ElementWezla wezel);

		/**
		* \brief Destruktor.
		*/
		virtual ~EkranSzablon() = default;

		/**
		* \brief Metoda przeliczaj�ca parametry ekranu wzgl�dem aktualnego stanu.
		*
		* Metoda przelicza prametry ekranu w zale�no�ci od stanu jaki zosta� przekazany jako parametr.
		* \param[inout] stan - Aktualnie przetwarzany stan aplikacji.
		*/
		virtual void uaktualnij(Stan& stan);

		/**
		* \brief Metoda odbieraj�ca zdarzenie.
		*
		* Metoda odbiera zdarzenie i przypisuje je do odpowiedniego okna nale��cego do ekranu.
		* \param[inout] stan - Aktualnie przetwarzany stan aplikacji.
		* \param[in] zdarzenie - Wykryte zdarzenie.
		*/
		virtual void odbierz(Stan& stan, const sf::Event& zdarzenie);

		/**
		* \brief Metoda pod��czaj�ca do okna.
		*
		* Metoda pod��cza ekran do okna przekazanego jako parametr.
		* \param[in] okno - Okno do kt�rego zostaje pod��czony ekran.
		*/
		virtual void podlacz(sf::RenderWindow& okno);

		/**
		* \brief Metoda od��czaj�ca do okna.
		*
		* Metoda od��cza ekran od okna przekazanego jako parametr.
		* \param[in] okno - Okno do kt�rego zostaje pod��czony ekran.
		*/
		virtual void odlacz(sf::RenderWindow& okno);

		/**
		* \brief Metoda pobieraj�ca identyfikator ekranu.
		*
		* Metoda zwraca aktualny identyfikator ekranu.
		* \return Aktualny identyfikator ekranu.
		*/
		const STyp::Identyfikator& pobierzId() const;

		/**
		* \brief Metoda pobieraj�ca uchwyt do interfejsu GUI.
		* 
		* Metoda zwraca interfejs GUI na kt�rym budowane s� okna danego ekranu.
		* \return Referencja do interfejsu GUI.
		*/
		tgui::Gui& pobierzGUI();


		/**
		* \brief Metoda czyszcz�ca ekran.
		*
		* Metoda usuwa wszystkie okna znajduj�ce si� na danym ekranie.
		*/
		virtual void clear();

		tgui::LogListGui::Ptr oknoKomunikatow_ = nullptr; /// Wska�nik na okno komunikat�w.

		/**
		* \brief Metoda tworz�ca tekstowy opis obiektu.
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
		* \brief Metoda konfiguruj�ca kontrolk�.
		*
		* Metoda Konfiguruje wczytan� przez ekran kontrolk� na podstawie wez�a konfiguracyjnego.
		* \param[in] wezel - Weze� konfiguracyjny.
		* \param[in] kontrolka - Wska�nik do kontrolki, kt�ra ma zosta� skonfigurowana.
		* \throw WyjatekParser, BladKonfiguracjiEkranu
		*/
		bool wczytajDaneKontrolki(XmlBO::ElementWezla wezel, tgui::Widget::Ptr kontrolka);

		/**
		* \brief Metoda rysuj�ca kontrolki.
		*
		* Metoda rysuj�ca kontrolki na ekranie.
		* \param[in] target - unused.
		* \param[in] states - unused.
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		STyp::Identyfikator id_; /// Identyfikator ekranu.
		mutable tgui::Gui interfejs_; /// Interfejs GUI na kt�rym tworzone s� kontrolki.
		
	};
};

