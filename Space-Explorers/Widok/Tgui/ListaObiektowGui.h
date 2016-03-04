#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include "KontrolkaObiektu.h"
#include <mutex>
#include <unordered_map>

namespace tgui{

	/**
	* \brief Klasa listy kontrolek obiekt�w.
	*
	* Klasa reprezentuje list� kontrolek obiekt�w. Wy�wietla list� obiekt�w wybudowanych na planecie.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuni�cie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 01-10-2014
	*/
	class ListaObiektowGui :
		public BazowyWidzet
	{
	public:
		friend class ListaObiektowGuiRenderer;

		typedef std::shared_ptr<ListaObiektowGui> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const ListaObiektowGui> ConstPtr; ///< Shared constant widget pointer

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		ListaObiektowGui();

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] zrodlowy - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		ListaObiektowGui(const ListaObiektowGui& zrodlowy);

		ListaObiektowGui& operator= (const ListaObiektowGui& right);

		static ListaObiektowGui::Ptr copy(ListaObiektowGui::ConstPtr widget);

		std::shared_ptr<ListaObiektowGuiRenderer> getRenderer() const {
			return std::static_pointer_cast<ListaObiektowGuiRenderer>(m_renderer);
		}

		void setPosition(const Layout2d& position) override;
		using Transformable::setPosition;

		void setSize(const Layout2d& size) override;
		using Transformable::setSize;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ListaObiektowGui() = default;
		
		/**
		* \brief Metoda od�wiezaj�ca pozycje kontrolek.
		*
		* Metoda przelicza pozycje kontrolek oraz suwaka.
		* \param[in] czyResetSuwaka - flaga informuj�ca o wyzerowaniu aktualnej pozycji suwaka.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void odswiez(bool czyResetSuwaka = true);

		/**
		* \brief Metoda od�wiezaj�ca dane kontrolek.
		*
		* Metoda uaktualnia dane reprezentowane przez kontrolk�.
		* \param[in] planeta - Planeta z kt�rej s� pobierane dane.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void aktualizacjaDanych(const SpEx::Planeta& planeta);

		/**
		* \brief Metoda pobiera typ wy�wietlanych obiekt�w.
		*
		* Metoda pobiera typ obiekt�w jakie s� wy�wietlane w kontrolce.
		* \return Typ wy�iwetlanych obiekt�w w kontrolce.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		int pobierzTypObiektu() const;

		void ustawTypObiektu(int typ);
		
	protected:

		/**
		* \brief Metoda rysuj�ca kontrolk�.
		*
		* Metoda rysuje kontrolk�.
		* \param[in] target - kontekst na kt�rym ma by� rysowana kontrolka.
		* \param[in] states - dodatkowy stan kontekstu rysowania kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:

		/**
		* \brief Metoda obs�uguj�ca zdarzenie zmiany pozycji rolki myszki.
		*
		* Metoda wywo�ywana w momencie zmiany pozycji rolki myszki.
		* \param[in] delta - Warto�� zmiany pozycji rolki.
		* \param[in] x - Pozycja x myszki.
		* \param[in] y - Pozycja y myszki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void mouseWheelMoved(int delta, int x, int y) override;
		
		/**
		* \brief Metoda przeliczaj�ca pozycj� kontrolek.
		*
		* Metoda przelicza pozycje kontrolek. Przesuwa je zgodnie z warto�ci� delty przekazan� w parametrze.
		* \param[in] delta - Warto�� na podstawie kt�rej jest wyliczane przesuni�cie kontrolek.
		* \param[in] czyUaktualnicRozmiar - Flaga informuj�ca o uaktualnieniu rozmiaru kontrolek.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void przeliczPozycjeKontrolek(int delta, bool czyUaktualnicRozmiar = false);
		
		/**
		* \brief Metoda przeliczaj�ca pozycj� suwaka.
		*
		* Metoda przelicza pozycje suwaka.
		* \param[in] wysokosc - Wysoko�� okna w kt�rym znajduje si� suwak.
		* \param[in] czyResetSuwaka - Flaga informuj�ca o zresetowaniu warto�ci suwaka.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void uaktualnijSuwak(float wysokosc, bool czyResetSuwaka);

		void stworzDomyslnySzablonKontrolki();

		void uaktualnijShader() const;

		int wartosc_suwaka_ = 0;
		int wartosc_suwaka_min = 0;
		int wartosc_suwaka_max = 0;
		KontrolkaObiektu::Ptr szablonKontrolki_; /// Wska�nik na szablon kontrolki obiektu.
		std::vector<KontrolkaObiektu::Ptr> kontrolki_; /// Kontener z kontrolkami obiekt�w.
		mutable std::mutex zmianaDanych_; /// Muteks dost�pu do modyfikacji ilo�ci kontrolek.
		float odstepMiedzyKontrolkami_ = 0.0f; /// Odst�p pomi�dzy poszczeg�lnymi kontrolkami.
		int mnoznikRolki_ = 15; /// Mno�nik rolki przy wyliczaniu przesuni�cia kontrolek.
		int typObiektu_ = 0; /// Typ wy�iwetlanych obiekt�w.
		bool czyAutoRozmiar_ = true; /// Automatyczne wyliczanie rozmiar�w.

		friend std::shared_ptr<DataIO::Node> saveListaObiektowGui(ListaObiektowGui::Ptr widget);
		friend Widget::Ptr loadListaObiektowGui(std::shared_ptr<DataIO::Node>, Widget::Ptr);
	};

	class ListaObiektowGuiRenderer : public BazowyRenderer
	{
	public:
		using BazowyRenderer::BazowyRenderer;
		void setProperty(std::string property, const std::string& value) override;
		void setProperty(std::string property, ObjectConverter&& value) override;
	private:
		std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;

	protected:
		friend class ListaObiektowGui;
	};
};
