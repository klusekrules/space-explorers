#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "Model\ObiektInfo.h"
#include "SurowiecGui.h"

namespace tgui{
	class ListaSurowcowGuiRenderer;
	/**
	* \brief Klasa listy kontrolek surowców.
	*
	* Klasa reprezentuje listê kontrolek surowców. Wyœwietla listê surowców dostênych na planecie.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 01-10-2014
	*/
	class ListaSurowcowGui :
		public BazowyWidzet
	{
	public:
		typedef std::shared_ptr<ListaSurowcowGui> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const ListaSurowcowGui> ConstPtr; ///< Shared constant widget pointer

		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		ListaSurowcowGui();

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] zrodlowy - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		ListaSurowcowGui(const ListaSurowcowGui& zrodlowy);

		ListaSurowcowGui& operator= (const ListaSurowcowGui& right);

		static ListaSurowcowGui::Ptr copy(ListaSurowcowGui::ConstPtr widget);

		std::shared_ptr<ListaSurowcowGuiRenderer> getRenderer() const {
			return std::static_pointer_cast<ListaSurowcowGuiRenderer>(m_renderer);
		}

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ListaSurowcowGui() = default;

		/**
		* \brief Metoda odœwiezaj¹ca dane kontrolek.
		*
		* Metoda uaktualnia dane reprezentowane przez kontrolkê.
		* \param[in] planeta - Planeta z której s¹ pobierane dane.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void aktualizacjaDanych(const SpEx::Planeta& planeta);
				
	protected:

		/**
		* \brief Metoda rysuj¹ca kontrolkê.
		*
		* Metoda rysuje kontrolkê.
		* \param[in] target - kontekst na którym ma byæ rysowana kontrolka.
		* \param[in] states - dodatkowy stan kontekstu rysowania kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		
		/**
		* \brief Metoda odœwie¿aj¹ca pozycjê kontrolek.
		*
		* Metoda odœwie¿a pozycjê kontrolek.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void odswiezPozycje();

		void stworzDomyslnySzablonKontrolki();

		void wyczyscDane();

		mutable std::mutex zmianaDanych_; /// Muteks dostêpu do modyfikacji danych kontrolek.
		SurowiecGui::Ptr szablonKontrolki_; /// WskaŸnik na szablon kontrolki obiektu.
		std::vector<SurowiecGui::Ptr> kontrolki_; /// Kontener z kontrolkami obiektów.

		friend class ListaSurowcowGuiRenderer;
		friend std::shared_ptr<DataIO::Node> saveListaSurowcowGui(ListaSurowcowGui::Ptr);
		friend Widget::Ptr loadListaSurowcowGui(std::shared_ptr<DataIO::Node>, Widget::Ptr);
	};

	class ListaSurowcowGuiRenderer : public BazowyRenderer
	{
	public:
		using BazowyRenderer::BazowyRenderer;
	private:
		std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;
	protected:
		friend class ListaSurowcowGui;
	};
	
};
