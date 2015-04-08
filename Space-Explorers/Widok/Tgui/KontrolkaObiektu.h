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
	* Klasa reprezentuje kontrolkê obiektu. Wyœwietla aktualne dane o obiekcie znajduj¹cym sie na planecie. Pozwala na rozbudowe.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 30-09-2014
	*/
	class KontrolkaObiektu :
		public Panel
	{
	public:

		/**
		* \brief Metoda tworzy kontrolkê.
		*
		* Metoda tworzy obiekt klasy KontrolkaObiektu.
		* \param[in] kontener - WskaŸnik do kontenera, w którym ma znajdowaæ siê stworzony obiekt.
		* \param[in] nazwa - Nazwa nowo stworzonego obiektu.
		* \return WskaŸnik na nowo stworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		static Widget* createWidget(Container* kontener, const std::string& nazwa);

		typedef SharedWidgetPtr<KontrolkaObiektu> Ptr; /// Inteligentny wskaŸnik na obiekt kontrolki.
		
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
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] zrodlowy - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		KontrolkaObiektu(const KontrolkaObiektu& zrodlowy);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~KontrolkaObiektu() = default;

		/**
		* \brief Metoda ustawiaj¹ca dane obiektu.
		*
		* Metoda ustawia dane wyœwietlane w obiekcie.
		* \param[in] obiekt - Obiekt opisuj¹cy.
		* \param[in] planeta - Planeta kontekstu obiektu.
		* \return Zwracana jest wartoœc true je¿eli uda³o siê wczytaæ dane. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool ustawDane(const SpEx::ObiektInfo& obiekt, const SpEx::Planeta& planeta);

		/**
		* \brief Metoda pobieraj¹ca identyfikator obiektu.
		*
		* Metoda zwraca identyfikator obiektu, który aktualnie jest wyœwietlany.
		* \return Identyfikator obiektu aktualnie wyœwietlanego.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		const STyp::Identyfikator& pobierzIdObiektu() const;

		/**
		* \brief Metoda ustawiaj¹ca shader dla kontrolki.
		*
		* Metoda ustawia shader dla kontrolki
		* \param[in] shader - wskaŸnik na shader jaki ma zostaæ przypisany do kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void ustawShader(sf::Shader* shader = nullptr);

		/**
		* \brief Metoda ustawiaj¹ca przeŸroczystoœæ kontrolki.
		*
		* Metoda ustawia przeŸroczystoœæ kontrolki
		* \param[in] przezroczystosc - stopieñ przeŸroczystoœci kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void setTransparency(unsigned char przezroczystosc) override;

		/**
		* \brief Metoda ustawiaj¹ca rozmiar kontrolki.
		*
		* Metoda ustawia rozmiar kontrolki
		* \param[in] szerokosc - szerokoœæ kontrolki.
		* \param[in] wysokosc - wysokoœæ kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void setSize(float szerokosc, float wysokosc) override;

		/**
		* \brief Metoda wczytuj¹ca parametry kontrolki.
		*
		* Metoda wczytuje parametry kontrolki
		* \param[in] adresPlikuKonfiguracyjnego - adres pliku konfiguracyjnego.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ parametry kontrolki. Zwracana jest wartoœæ false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool load(const std::string& adresPlikuKonfiguracyjnego);

		/**
		* \brief Metoda tworz¹ca kopiê obiektu.
		*
		* Metoda tworzy kopiê obiektu.
		* \return WskaŸnik na skopiowany obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		KontrolkaObiektu* clone() override;

		/**
		* \brief Metoda zwracaj¹ca adres pliku konfiguracynego.
		*
		* Metoda zwraca adres pliku konfiguracyjnego, z którego zosta³y zaczytane parametry kontrolki.
		* \return Adres pliku konfiguracyjnego.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		const std::string& getLoadedConfigFile() const;

		/**
		* \brief Metoda ustawiaj¹ca wartoœæ w³aœciwoœci.
		*
		* Metoda ustawia wartoœæ w³aœciwoœci zgodnie z danymi przekazanymi w parametrach.
		* \param[in] wlasciwosc - Nazwa w³aœciwoœci kontrolki.
		* \param[in] wartosc - Wartoœæ w³aœciwoœci kontrolki.
		* \return Zwracana jest wartoœæ true je¿eli uda siê ustawiæ wartoœæ. W przeciwnym wypadku jest zwracana wartoœæ false.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool setProperty(std::string wlasciwosc, const std::string& wartosc) override;

		/**
		* \brief Metoda pobieraj¹ca wartoœæ w³aœciwoœci.
		*
		* Metoda pobiera wartoœæ w³aœciwoœci.
		* \param[in] wlasciwosc - Nazwa w³aœciwoœci kontrolki.
		* \param[out] wartosc - Wartoœæ w³aœciwoœci kontrolki.
		* \return Zwracana jest wartoœæ true je¿eli uda siê pobraæ wartoœæ. W przeciwnym wypadku jest zwracana wartoœæ false.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool getProperty(std::string wlasciwosc, std::string& wartosc) const override;

		/**
		* \brief Metoda zwracaj¹ca listê w³aœciwoœci.
		*
		* Metoda zwraca listê w³aœciwoœci jakie mo¿na ustawiæ w kontrolce.
		* \return Lista w³aœciwoœci.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		std::list< std::pair<std::string, std::string> > getPropertyList() const override;
	protected:

		/**
		* \brief Metoda rysuj¹ca kontrolkê.
		*
		* Metoda rysuje kontrolkê.
		* \param[in] target - kontekst na którym ma byæ rysowana kontrolka.
		* \param[in] states - dodatkowy stan kontekstu rysowania kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		sf::Rect<float> pozycjonujLabel(Label::Ptr, const sf::Rect<float>&, float width, float height, WYROWNANIE_HORYZONTALNE horyzontalne, WYROWNANIE_WERTYKALNE wertykalne);
		
		/**
		* \brief Metoda inicjalizuj¹ca obiekt.
		*
		* Metoda inicjalizuje obiekt kontrolki podstawowymi parametrami.
		* \param[in] kontener - WskaŸnik na kontener, w którym ma znajdowaæ siê obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void initialize(Container *const kontener) override;

		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.

		Texture tlo_; /// Tekstura t³a obrazu
		STyp::Identyfikator idObiektu_ = -1; /// Identyfikator obiektu gry wyœiwetlanego w kontrolce.
		Picture::Ptr obraz_; /// Obraz obiektu gry.
		Label::Ptr nazwa_; /// Nazwa obiektu gry.
		Label::Ptr tresc_; /// Opis obiektu gry.
		Button::Ptr rozbuduj_; /// Przycisk rozbudowy obiektu gry.
		Button::Ptr zniszcz_; /// Przycisk burzenia obiektu gry.
		Label::Ptr czasRozbudowy_; /// Czas rozbudowy obiektu gry.
		Label::Ptr czasZburzenia_; /// Czas burzenia obiektu gry.
		sf::Shader* shader_ = nullptr; /// WskaŸnik na u¿yte shader'y.
		
		sf::Vector2f rozmiarKontrolki_; /// Rozmiar kontrolki.
		sf::Rect<float> obrazRect_; /// Rozmiar pola obrazka obiektu gry.
		sf::Rect<float> nazwaRect_; /// Rozmiar pola nazwy obiektu gry.
		sf::Rect<float> trescRect_; /// Rozmiar pola treœci obiektu gry.
		sf::Rect<float> rozbudujRect_; /// Rozmiar przycisku budowy obiektu gry.
		sf::Rect<float> zniszczRect_; /// Rozmiar przycisku burzenia obiektu gry.
		sf::Rect<float> czasRozbudowyRect_; /// Rozmiar pola czasu budowy obiektu gry.
		sf::Rect<float> czasZburzeniaRect_; /// Rozmiar pola czasu burzenia obiektu gry.

		WYROWNANIE_WERTYKALNE czasRozbudowyWyrownanieWertykalne_ = MIDDLE; /// Wyrównanie w pionie pola czasu budowy obiektu gry.
		WYROWNANIE_HORYZONTALNE czasRozbudowyWyrownanieHoryzontalne_ = LEFT; /// Wyrównanie w poziomie pola czasu budowy obiektu gry.

		WYROWNANIE_WERTYKALNE czasZburzeniaWyrownanieWertykalne_ = MIDDLE; /// Wyrównanie w pionie czasu burzenia obiektu gry.
		WYROWNANIE_HORYZONTALNE czasZburzeniaWyrownanieHoryzontalne_ = LEFT; /// Wyrównanie w poziomie czasu burzenia obiektu gry.

		WYROWNANIE_WERTYKALNE nazwaWyrownanieWertykalne_ = MIDDLE;  /// Wyrównanie w pionie napisu nazwy obiektu gry.
		WYROWNANIE_HORYZONTALNE nazwaWyrownanieHoryzontalne_ = LEFT; /// Wyrównanie w poziomie napisu nazwy obiektu gry.

		WYROWNANIE_WERTYKALNE trescWyrownanieWertykalne_ = MIDDLE; /// Wyrównanie w pionie napisu opisuj¹cego obiekt gry.
		WYROWNANIE_HORYZONTALNE trescWyrownanieHoryzontalne_ = LEFT; /// Wyrównanie w poziomie napisu opisuj¹cego obiekt gry.

		bool czyStalyRozmiar_ = false; /// Flaga informuj¹ca czy kontrolka ma sta³y rozmiar.
		bool czyProporcjonalny_ = true; /// Flaga informuj¹ca czy kontrolka zachowuje proporcje przy zmianie rozmiaru. 

		int idZdarzeniaBudowy_ = 0; /// Numer zdarzenia klikniêcia na przycisk budowy obiektu gry.
		int idZdarzeniaBurzenia_ = 0; /// Numer zdarzenia klikniêcia na przycisk burzenia obiektu gry.
		int idZdarzeniaKlikniecia_ = 0; /// Numer zdarzenia klikniêcia na obrazek obiektu gry.

	};
};
