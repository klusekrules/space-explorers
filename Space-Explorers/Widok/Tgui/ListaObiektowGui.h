#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include "KontrolkaObiektu.h"
#include <mutex>
#include <unordered_map>

namespace tgui{

	/**
	* \brief Klasa listy kontrolek obiektów.
	*
	* Klasa reprezentuje listê kontrolek obiektów. Wyœwietla listê obiektów wybudowanych na planecie.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
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
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		ListaObiektowGui() = default;

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopiuj¹cy.
		* \param[in] zrodlowy - Obiekt Ÿród³owy.
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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ListaObiektowGui() = default;
		
		/**
		* \brief Metoda odœwiezaj¹ca pozycje kontrolek.
		*
		* Metoda przelicza pozycje kontrolek oraz suwaka.
		* \param[in] czyResetSuwaka - flaga informuj¹ca o wyzerowaniu aktualnej pozycji suwaka.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void odswiez(bool czyResetSuwaka = true);

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

		/**
		* \brief Metoda wczytuj¹ca parametry kontrolki.
		*
		* Metoda wczytuje parametry kontrolki
		* \param[in] adresPlikuKonfiguracyjnego - adres pliku konfiguracyjnego.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê poprawnie wczytaæ parametry kontrolki. Zwracana jest wartoœæ false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		bool load(const std::string& configFileFilename);
		
		/**
		* \brief Metoda pobiera typ wyœwietlanych obiektów.
		*
		* Metoda pobiera typ obiektów jakie s¹ wyœwietlane w kontrolce.
		* \return Typ wyœiwetlanych obiektów w kontrolce.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		int pobierzTypObiektu() const;

		/**
		* \brief Metoda zwracaj¹ca adres pliku konfiguracynego.
		*
		* Metoda zwraca adres pliku konfiguracyjnego, z którego zosta³y zaczytane parametry kontrolki.
		* \return Adres pliku konfiguracyjnego.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		const std::string& getLoadedConfigFile() const;

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
		* \brief Metoda obs³uguj¹ca zdarzenie zmiany pozycji rolki myszki.
		*
		* Metoda wywo³ywana w momencie zmiany pozycji rolki myszki.
		* \param[in] delta - Wartoœæ zmiany pozycji rolki.
		* \param[in] x - Pozycja x myszki.
		* \param[in] y - Pozycja y myszki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void mouseWheelMoved(int delta, int x, int y) override;

		/**
		* \brief Metoda obs³uguj¹ca zdarzenie zmiany pozycji suwaka.
		*
		* Metoda wywo³ywana po zmianie pozycji suwaka.
		* \param[in] callback - Kontekst zdarzenia.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void scrollbarValueChanged(const tgui::Callback& callback);

		/**
		* \brief Metoda przeliczaj¹ca pozycjê kontrolek.
		*
		* Metoda przelicza pozycje kontrolek. Przesuwa je zgodnie z wartoœci¹ delty przekazan¹ w parametrze.
		* \param[in] delta - Wartoœæ na podstawie której jest wyliczane przesuniêcie kontrolek.
		* \param[in] czyUaktualnicRozmiar - Flaga informuj¹ca o uaktualnieniu rozmiaru kontrolek.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void przeliczPozycjeKontrolek(int delta, bool czyUaktualnicRozmiar = false);
		
		/**
		* \brief Metoda przeliczaj¹ca pozycjê suwaka.
		*
		* Metoda przelicza pozycje suwaka.
		* \param[in] wysokosc - Wysokoœæ okna w którym znajduje siê suwak.
		* \param[in] czyResetSuwaka - Flaga informuj¹ca o zresetowaniu wartoœci suwaka.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void uaktualnijSuwak(float wysokosc, bool czyResetSuwaka);

		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.

		Scrollbar::Ptr suwak_; /// WskaŸnik na kontrolkê suwaka.
		KontrolkaObiektu::Ptr szablonKontrolki_; /// WskaŸnik na szablon kontrolki obiektu.
		std::vector<KontrolkaObiektu::Ptr> kontrolki_; /// Kontener z kontrolkami obiektów.
		std::shared_ptr<sf::Shader> shader_ = nullptr; /// WskaŸnika na obiekt shader'ów.
		mutable std::mutex zmianaDanych_; /// Muteks dostêpu do modyfikacji iloœci kontrolek.
		Borders margines_; /// Wewnêtrzne marginesy kontrolki.
		float szerokoscSuwaka_ = 20.f; /// Szerokoœæ suwaka
		float odstepMiedzyKontrolkami_ = 0.0f; /// Odstêp pomiêdzy poszczególnymi kontrolkami.
		int mnoznikRolki_ = 15; /// Mno¿nik rolki przy wyliczaniu przesuniêcia kontrolek.
		int typObiektu_ = 0; /// Typ wyœiwetlanych obiektów.
		bool pokazSuwak_ = false; /// Flaga informuj¹ca czy suwak ma byæ widoczny
		bool czyAutoRozmiar_ = true; /// Automatyczne wyliczanie rozmiarów.
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
