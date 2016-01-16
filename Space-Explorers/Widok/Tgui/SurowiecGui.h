#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "Model\ObiektInfo.h"

namespace tgui {

	class SurowiecGuiRenderer;

	/**
	* \brief Klasa kontrolki surowca.
	*
	* Klasa reprezentuje kontrolk� surowca. Wy�wietla ilo�� surowca na planecie.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuni�cie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 01-10-2014
	*/
	class SurowiecGui :
		public Widget
	{
	public:
		typedef std::shared_ptr<SurowiecGui> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const SurowiecGui> ConstPtr; ///< Shared constant widget pointer

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		SurowiecGui() = default;

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] zrodlowy - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		SurowiecGui(const SurowiecGui& zrodlowy);
		
		SurowiecGui& operator= (const SurowiecGui& right);

		std::shared_ptr<SurowiecGuiRenderer> getRenderer() const{
			return std::static_pointer_cast<SurowiecGuiRenderer>(m_renderer);
		}

		virtual void setPosition(const Layout2d& position) override;
		using Transformable::setPosition;

		void setSize(const Layout2d& size) override;
		using Transformable::setSize;

		virtual sf::Vector2f getFullSize() const override;

		void setFont(const Font& font);

		std::shared_ptr<sf::Font> getTextFont(){
			return m_panel->getFont();
		}
		
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~SurowiecGui() = default;

		/**
		* \brief Metoda pobieraj�ca identyfikator obiektu.
		*
		* Metoda pobiera identyfikator reprezentowanego obiektu.
		* \return Identyfikator reprezentowanego obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		const STyp::Identyfikator& pobierzIdObiektu() const;

		/**
		* \brief Metoda ustawiaj�ca dane w kontrolce.
		*
		* Metoda ustawia dane reprezentowanego obiektu w kontrolce.
		* \param[in] obiekt - Reprezentowany obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void ustawDane(const SpEx::Obiekt& obiekt);

		/**
		* \brief Metoda ustawiaj�ca rozmiar tekstu.
		*
		* Metoda ustawia rozmiar tekstu wy�wietlanego w kontrolce.
		* \param[in] rozmiar - Rozmiar tekstu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void setTextSize(unsigned int rozmiar);
		/**
		* \brief Metoda ustawiaj�ca kolor tekstu.
		*
		* Metoda ustawia kolor tekstu wy�wietlanego w kontrolce.
		* \param[in] kolor - Kolor tekstu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void setTextColor(sf::Color kolor);

		bool mouseOnWidget(float x, float y) override;
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
			return std::make_shared<SurowiecGui>(*this);
		}

		virtual void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;

	private:

		void updateRendering();

		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.
		Label::Ptr tekst_; /// Prezentowany tekst.
		STyp::Identyfikator idObiektu_; /// Identyfikator reprezentowanego obiektu.

		Panel::Ptr m_panel = std::make_shared<Panel>();

		friend class SurowiecGuiRenderer;
	};

	class SurowiecGuiRenderer : public WidgetRenderer, public WidgetBorders, public WidgetPadding
	{
	public:
		SurowiecGuiRenderer(SurowiecGui* kontrolka) : m_surowceGui(kontrolka) {}

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

		SurowiecGuiRenderer(const SurowiecGuiRenderer&) = default;
		SurowiecGuiRenderer& operator=(const SurowiecGuiRenderer&) = delete;

	protected:

		SurowiecGui* m_surowceGui;

		sf::Color m_borderColor;
		sf::Color m_backgroundColor;

		Texture m_backgroundTexture;

		friend class SurowiecGui;
	};
};