#pragma once
#include <TGUI\TGUI.hpp>
#include "PomocniczeTypyTGUI.h"
#include "Model\ObiektInfo.h"

namespace tgui{

	void convertFromBorderToRect(const Borders&, sf::Rect<float>&);
	void normalizujRect(sf::Rect<float>&, float leftWidth, float topHeight);


	/**
	* \brief Klasa kontrolki obiektu.
	*
	* Klasa reprezentuje kontrolk� obiektu. Wy�wietla aktualne dane o obiekcie znajduj�cym sie na planecie. Pozwala na rozbudowe.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuni�cie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 30-09-2014
	*/
	class KontrolkaObiektu :
		public Panel
	{
	public:

		/**
		* \brief Metoda tworzy kontrolk�.
		*
		* Metoda tworzy obiekt klasy KontrolkaObiektu.
		* \param[in] kontener - Wska�nik do kontenera, w kt�rym ma znajdowa� si� stworzony obiekt.
		* \param[in] nazwa - Nazwa nowo stworzonego obiektu.
		* \return Wska�nik na nowo stworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		static Widget* createWidget(Container* kontener, const std::string& nazwa);

		typedef SharedWidgetPtr<KontrolkaObiektu> Ptr; /// Inteligentny wska�nik na obiekt kontrolki.
		
		/**
		* \brief Konstruktor obiektu.
		* 
		* Konstruktor bezparametrowy.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		KontrolkaObiektu();
		
		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] zrodlowy - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		KontrolkaObiektu(const KontrolkaObiektu& zrodlowy);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~KontrolkaObiektu() = default;

		/**
		* \brief Metoda ustawiaj�ca dane obiektu.
		*
		* Metoda ustawia dane wy�wietlane w obiekcie.
		* \param[in] obiekt - Obiekt opisuj�cy.
		* \param[in] planeta - Planeta kontekstu obiektu.
		* \return Zwracana jest warto�c true je�eli uda�o si� wczyta� dane. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool ustawDane(const SpEx::ObiektInfo& obiekt, const SpEx::Planeta& planeta);

		/**
		* \brief Metoda pobieraj�ca identyfikator obiektu.
		*
		* Metoda zwraca identyfikator obiektu, kt�ry aktualnie jest wy�wietlany.
		* \return Identyfikator obiektu aktualnie wy�wietlanego.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		const STyp::Identyfikator& pobierzIdObiektu() const;

		/**
		* \brief Metoda ustawiaj�ca shader dla kontrolki.
		*
		* Metoda ustawia shader dla kontrolki
		* \param[in] shader - wska�nik na shader jaki ma zosta� przypisany do kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void ustawShader(sf::Shader* shader = nullptr);

		/**
		* \brief Metoda ustawiaj�ca prze�roczysto�� kontrolki.
		*
		* Metoda ustawia prze�roczysto�� kontrolki
		* \param[in] przezroczystosc - stopie� prze�roczysto�ci kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void setTransparency(unsigned char przezroczystosc) override;

		/**
		* \brief Metoda ustawiaj�ca rozmiar kontrolki.
		*
		* Metoda ustawia rozmiar kontrolki
		* \param[in] szerokosc - szeroko�� kontrolki.
		* \param[in] wysokosc - wysoko�� kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void setSize(float szerokosc, float wysokosc) override;

		/**
		* \brief Metoda wczytuj�ca parametry kontrolki.
		*
		* Metoda wczytuje parametry kontrolki
		* \param[in] adresPlikuKonfiguracyjnego - adres pliku konfiguracyjnego.
		* \return Zwracana jest warto�� true, je�eli uda si� poprawnie wczyta� parametry kontrolki. Zwracana jest warto�� false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool load(const std::string& adresPlikuKonfiguracyjnego);

		/**
		* \brief Metoda tworz�ca kopi� obiektu.
		*
		* Metoda tworzy kopi� obiektu.
		* \return Wska�nik na skopiowany obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		KontrolkaObiektu* clone() override;

		/**
		* \brief Metoda zwracaj�ca adres pliku konfiguracynego.
		*
		* Metoda zwraca adres pliku konfiguracyjnego, z kt�rego zosta�y zaczytane parametry kontrolki.
		* \return Adres pliku konfiguracyjnego.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		const std::string& getLoadedConfigFile() const;

		/**
		* \brief Metoda ustawiaj�ca warto�� w�a�ciwo�ci.
		*
		* Metoda ustawia warto�� w�a�ciwo�ci zgodnie z danymi przekazanymi w parametrach.
		* \param[in] wlasciwosc - Nazwa w�a�ciwo�ci kontrolki.
		* \param[in] wartosc - Warto�� w�a�ciwo�ci kontrolki.
		* \return Zwracana jest warto�� true je�eli uda si� ustawi� warto��. W przeciwnym wypadku jest zwracana warto�� false.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool setProperty(std::string wlasciwosc, const std::string& wartosc) override;

		/**
		* \brief Metoda pobieraj�ca warto�� w�a�ciwo�ci.
		*
		* Metoda pobiera warto�� w�a�ciwo�ci.
		* \param[in] wlasciwosc - Nazwa w�a�ciwo�ci kontrolki.
		* \param[out] wartosc - Warto�� w�a�ciwo�ci kontrolki.
		* \return Zwracana jest warto�� true je�eli uda si� pobra� warto��. W przeciwnym wypadku jest zwracana warto�� false.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool getProperty(std::string wlasciwosc, std::string& wartosc) const override;

		/**
		* \brief Metoda zwracaj�ca list� w�a�ciwo�ci.
		*
		* Metoda zwraca list� w�a�ciwo�ci jakie mo�na ustawi� w kontrolce.
		* \return Lista w�a�ciwo�ci.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		std::list< std::pair<std::string, std::string> > getPropertyList() const override;
	protected:

		/**
		* \brief Metoda rysuj�ca kontrolk�.
		*
		* Metoda rysuje kontrolk�.
		* \param[in] target - kontekst na kt�rym ma by� rysowana kontrolka.
		* \param[in] states - dodatkowy stan kontekstu rysowania kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		sf::Rect<float> pozycjonujLabel(Label::Ptr, const sf::Rect<float>&, float width, float height, WYROWNANIE_HORYZONTALNE horyzontalne, WYROWNANIE_WERTYKALNE wertykalne);
		
		/**
		* \brief Metoda inicjalizuj�ca obiekt.
		*
		* Metoda inicjalizuje obiekt kontrolki podstawowymi parametrami.
		* \param[in] kontener - Wska�nik na kontener, w kt�rym ma znajdowa� si� obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void initialize(Container *const kontener) override;

		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.

		Texture tlo_; /// Tekstura t�a obrazu
		STyp::Identyfikator idObiektu_ = -1; /// Identyfikator obiektu gry wy�iwetlanego w kontrolce.
		Picture::Ptr obraz_; /// Obraz obiektu gry.
		Label::Ptr nazwa_; /// Nazwa obiektu gry.
		Label::Ptr tresc_; /// Opis obiektu gry.
		Button::Ptr rozbuduj_; /// Przycisk rozbudowy obiektu gry.
		Button::Ptr zniszcz_; /// Przycisk burzenia obiektu gry.
		Label::Ptr czasRozbudowy_; /// Czas rozbudowy obiektu gry.
		Label::Ptr czasZburzenia_; /// Czas burzenia obiektu gry.
		sf::Shader* shader_ = nullptr; /// Wska�nik na u�yte shader'y.
		
		sf::Vector2f rozmiarKontrolki_; /// Rozmiar kontrolki.
		sf::Rect<float> obrazRect_; /// Rozmiar pola obrazka obiektu gry.
		sf::Rect<float> nazwaRect_; /// Rozmiar pola nazwy obiektu gry.
		sf::Rect<float> trescRect_; /// Rozmiar pola tre�ci obiektu gry.
		sf::Rect<float> rozbudujRect_; /// Rozmiar przycisku budowy obiektu gry.
		sf::Rect<float> zniszczRect_; /// Rozmiar przycisku burzenia obiektu gry.
		sf::Rect<float> czasRozbudowyRect_; /// Rozmiar pola czasu budowy obiektu gry.
		sf::Rect<float> czasZburzeniaRect_; /// Rozmiar pola czasu burzenia obiektu gry.

		WYROWNANIE_WERTYKALNE czasRozbudowyWyrownanieWertykalne_ = MIDDLE; /// Wyr�wnanie w pionie pola czasu budowy obiektu gry.
		WYROWNANIE_HORYZONTALNE czasRozbudowyWyrownanieHoryzontalne_ = LEFT; /// Wyr�wnanie w poziomie pola czasu budowy obiektu gry.

		WYROWNANIE_WERTYKALNE czasZburzeniaWyrownanieWertykalne_ = MIDDLE; /// Wyr�wnanie w pionie czasu burzenia obiektu gry.
		WYROWNANIE_HORYZONTALNE czasZburzeniaWyrownanieHoryzontalne_ = LEFT; /// Wyr�wnanie w poziomie czasu burzenia obiektu gry.

		WYROWNANIE_WERTYKALNE nazwaWyrownanieWertykalne_ = MIDDLE;  /// Wyr�wnanie w pionie napisu nazwy obiektu gry.
		WYROWNANIE_HORYZONTALNE nazwaWyrownanieHoryzontalne_ = LEFT; /// Wyr�wnanie w poziomie napisu nazwy obiektu gry.

		WYROWNANIE_WERTYKALNE trescWyrownanieWertykalne_ = MIDDLE; /// Wyr�wnanie w pionie napisu opisuj�cego obiekt gry.
		WYROWNANIE_HORYZONTALNE trescWyrownanieHoryzontalne_ = LEFT; /// Wyr�wnanie w poziomie napisu opisuj�cego obiekt gry.

		bool czyStalyRozmiar_ = false; /// Flaga informuj�ca czy kontrolka ma sta�y rozmiar.
		bool czyProporcjonalny_ = true; /// Flaga informuj�ca czy kontrolka zachowuje proporcje przy zmianie rozmiaru. 

		int idZdarzeniaBudowy_ = 0; /// Numer zdarzenia klikni�cia na przycisk budowy obiektu gry.
		int idZdarzeniaBurzenia_ = 0; /// Numer zdarzenia klikni�cia na przycisk burzenia obiektu gry.
		int idZdarzeniaKlikniecia_ = 0; /// Numer zdarzenia klikni�cia na obrazek obiektu gry.

	};
};
