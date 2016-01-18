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
		ListaObiektowGui() = default;

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

		std::shared_ptr<ListaObiektowGuiRenderer> getRenderer() const {
			return std::static_pointer_cast<ListaObiektowGuiRenderer>(m_renderer);
		}
		void setPosition(const Layout2d& position) override;

		void setSize(const Layout2d& size) override;

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
		* \brief Metoda wczytuj�ca parametry kontrolki.
		*
		* Metoda wczytuje parametry kontrolki
		* \param[in] adresPlikuKonfiguracyjnego - adres pliku konfiguracyjnego.
		* \return Zwracana jest warto�� true, je�eli uda si� poprawnie wczyta� parametry kontrolki. Zwracana jest warto�� false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		bool load(const std::string& configFileFilename);
		
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

		/**
		* \brief Metoda zwracaj�ca adres pliku konfiguracynego.
		*
		* Metoda zwraca adres pliku konfiguracyjnego, z kt�rego zosta�y zaczytane parametry kontrolki.
		* \return Adres pliku konfiguracyjnego.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		const std::string& getLoadedConfigFile() const;

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
		* \brief Metoda obs�uguj�ca zdarzenie zmiany pozycji suwaka.
		*
		* Metoda wywo�ywana po zmianie pozycji suwaka.
		* \param[in] callback - Kontekst zdarzenia.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void scrollbarValueChanged(const tgui::Callback& callback);

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

		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.

		Scrollbar::Ptr suwak_; /// Wska�nik na kontrolk� suwaka.
		KontrolkaObiektu::Ptr szablonKontrolki_; /// Wska�nik na szablon kontrolki obiektu.
		std::vector<KontrolkaObiektu::Ptr> kontrolki_; /// Kontener z kontrolkami obiekt�w.
		std::shared_ptr<sf::Shader> shader_ = nullptr; /// Wska�nika na obiekt shader'�w.
		mutable std::mutex zmianaDanych_; /// Muteks dost�pu do modyfikacji ilo�ci kontrolek.
		Borders margines_; /// Wewn�trzne marginesy kontrolki.
		float szerokoscSuwaka_ = 20.f; /// Szeroko�� suwaka
		float odstepMiedzyKontrolkami_ = 0.0f; /// Odst�p pomi�dzy poszczeg�lnymi kontrolkami.
		int mnoznikRolki_ = 15; /// Mno�nik rolki przy wyliczaniu przesuni�cia kontrolek.
		int typObiektu_ = 0; /// Typ wy�iwetlanych obiekt�w.
		bool pokazSuwak_ = false; /// Flaga informuj�ca czy suwak ma by� widoczny
		bool czyAutoRozmiar_ = true; /// Automatyczne wyliczanie rozmiar�w.
	};

	class ListaObiektowGuiRenderer : public BazowyRenderer
	{
	public:
		using BazowyRenderer::BazowyRenderer;

	private:
		std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;
		ListaObiektowGuiRenderer(const ListaObiektowGuiRenderer&) = default;
		ListaObiektowGuiRenderer& operator=(const ListaObiektowGuiRenderer&) = delete;

	protected:

		friend class ListaObiektowGui;
	};
};
