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

	class KontrolkaObiektuRenderer;

	class KontrolkaObiektu :
		public Widget
	{
	public:
		typedef std::shared_ptr<KontrolkaObiektu> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const KontrolkaObiektu> ConstPtr; ///< Shared constant widget pointer

		/**
		* \brief Konstruktor obiektu.
		*
		* Konstruktor bezparametrowy.
		* \author Daniel Wojdak
		* \version 3
		* \date 27-11-2015
		*/
		KontrolkaObiektu();

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] copy - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 3
		* \date 27-11-2015
		*/
		KontrolkaObiektu(const KontrolkaObiektu& copy);
		
		KontrolkaObiektu& operator= (const KontrolkaObiektu& right);

		std::shared_ptr<KontrolkaObiektuRenderer> getRenderer() const
		{
			return std::static_pointer_cast<KontrolkaObiektuRenderer>(m_renderer);
		}

		virtual void setPosition(const Layout2d& position) override;
		using Transformable::setPosition;
		
		void setSize(const Layout2d& size) override;
		using Transformable::setSize;
		
		virtual sf::Vector2f getFullSize() const override;

		void setFont(const Font& font);

		std::shared_ptr<sf::Font> getTextFont()
		{
			return m_panel->getFont();
		}

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

		virtual bool mouseOnWidget(float x, float y) override;
			
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

		virtual Widget::Ptr clone() const override
		{
			return std::make_shared<KontrolkaObiektu>(*this);
		}

		virtual void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;

	private:

		void updateRendering();

		sf::Rect<float> pozycjonujLabel(Label::Ptr, const sf::Rect<float>&, float width, float height, WYROWNANIE_HORYZONTALNE horyzontalne, WYROWNANIE_WERTYKALNE wertykalne);
		
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


		//unsigned int m_lineSpacing = 0;
		//unsigned int m_textSize = 18;
		//sf::Color m_textColor = sf::Color::Black;

		//std::size_t m_maxLines = 0;

		//float m_fullTextHeight = 0;

		//bool m_linesStartFromTop = false;

		// The panel containing the labels
		Panel::Ptr m_panel = std::make_shared<Panel>();

		// The scrollbar
		//Scrollbar::Ptr m_scroll = std::make_shared<Scrollbar>();

		friend class KontrolkaObiektuRenderer;

	};

	
	class KontrolkaObiektuRenderer : public WidgetRenderer, public WidgetBorders, public WidgetPadding
	{
	public:
		KontrolkaObiektuRenderer(KontrolkaObiektu* kontrolka) : m_kontrolkaObiektu(kontrolka) {}

		virtual void setProperty(std::string property, const std::string& value) override;
		virtual void setProperty(std::string property, ObjectConverter&& value) override;

		virtual ObjectConverter getProperty(std::string property) const override;

		virtual std::map<std::string, ObjectConverter> getPropertyValuePairs() const override;
		void setBorderColor(const sf::Color& borderColor);
		void setBackgroundColor(const sf::Color& backgroundColor);


		void setBackgroundTexture(const Texture& texture);
		void setPadding(const Padding& padding) override;
		using WidgetPadding::setPadding;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:

		virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;

		KontrolkaObiektuRenderer(const KontrolkaObiektuRenderer&) = default;
		KontrolkaObiektuRenderer& operator=(const KontrolkaObiektuRenderer&) = delete;

	protected:

		KontrolkaObiektu* m_kontrolkaObiektu;

		sf::Color m_borderColor;
		sf::Color m_backgroundColor;

		Texture m_backgroundTexture;

		friend class KontrolkaObiektu;
	};
};
