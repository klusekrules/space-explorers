#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "Model\ObiektInfo.h"
#include "BazowyRenderer.h"

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
		public BazowyWidzet
	{
	public:
		typedef std::shared_ptr<SurowiecGui> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const SurowiecGui> ConstPtr; ///< Shared constant widget pointer

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		SurowiecGui();

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

		std::shared_ptr<SurowiecGuiRenderer> getRenderer() const {
			return std::static_pointer_cast<SurowiecGuiRenderer>(m_renderer);
		}

		Widget::Ptr clone() const override {
			return std::make_shared<SurowiecGui>(*this);
		}

	protected:

		void reload(const std::string& primary = "", const std::string& secondary = "", bool force = false) override;

	private:

		Label::Ptr tekst_; /// Prezentowany tekst.
		STyp::Identyfikator idObiektu_; /// Identyfikator reprezentowanego obiektu.

		friend class SurowiecGuiRenderer;
	};

	class SurowiecGuiRenderer : public BazowyRenderer
	{
	public:
		using BazowyRenderer::BazowyRenderer;

	private:
		std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;
		SurowiecGuiRenderer(const SurowiecGuiRenderer&) = default;
		SurowiecGuiRenderer& operator=(const SurowiecGuiRenderer&) = delete;

	protected:
		
		friend class SurowiecGui;
	};
};