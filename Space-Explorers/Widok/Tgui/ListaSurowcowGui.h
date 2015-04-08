#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "Model\ObiektInfo.h"

namespace tgui{

	/**
	* \brief Klasa listy kontrolek surowc�w.
	*
	* Klasa reprezentuje list� kontrolek surowc�w. Wy�wietla list� surowc�w dost�nych na planecie.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuni�cie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 01-10-2014
	*/
	class ListaSurowcowGui :
		public Panel
	{
	public:
		/**
		* \brief Metoda tworzy kontrolk�.
		*
		* Metoda tworzy obiekt klasy ListaSurowcowGui.
		* \param[in] kontener - Wska�nik do kontenera, w kt�rym ma znajdowa� si� stworzony obiekt.
		* \param[in] nazwa - Nazwa nowo stworzonego obiektu.
		* \return Wska�nik na nowo stworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		static Widget* createWidget(Container* kontener, const std::string& nazwa);

		typedef SharedWidgetPtr<ListaSurowcowGui> Ptr; /// Inteligentny wska�nik na obiekt kontrolki.
		
		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		ListaSurowcowGui() = default;

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopiuj�cy.
		* \param[in] zrodlowy - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		ListaSurowcowGui(const ListaSurowcowGui& zrodlowy);
		
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ListaSurowcowGui() = default;

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
		* \brief Metoda ustawiaj�ca prze�roczysto�� kontrolki.
		*
		* Metoda ustawia prze�roczysto�� kontrolki
		* \param[in] przezroczystosc - stopie� prze�roczysto�ci kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
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
		* \date 01-10-2014
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
		* \date 01-10-2014
		*/
		bool load(const std::string& configFileFilename);

		/**
		* \brief Metoda tworz�ca kopi� obiektu.
		*
		* Metoda tworzy kopi� obiektu.
		* \return Wska�nik na skopiowany obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		ListaSurowcowGui* clone() override;

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

		/**
		* \brief Metoda ustawiaj�ca warto�� w�a�ciwo�ci.
		*
		* Metoda ustawia warto�� w�a�ciwo�ci zgodnie z danymi przekazanymi w parametrach.
		* \param[in] wlasciwosc - Nazwa w�a�ciwo�ci kontrolki.
		* \param[in] wartosc - Warto�� w�a�ciwo�ci kontrolki.
		* \return Zwracana jest warto�� true je�eli uda si� ustawi� warto��. W przeciwnym wypadku jest zwracana warto�� false.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
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
		* \date 01-10-2014
		*/
		bool getProperty(std::string wlasciwosc, std::string& wartosc) const override;

		/**
		* \brief Metoda zwracaj�ca list� w�a�ciwo�ci.
		*
		* Metoda zwraca list� w�a�ciwo�ci jakie mo�na ustawi� w kontrolce.
		* \return Lista w�a�ciwo�ci.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
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
		* \date 01-10-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
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
			public Panel
		{
		public:
			typedef SharedWidgetPtr<SurowiecGui> Ptr; /// Inteligentny wska�nik na obiekt kontrolki.
			
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
			* \brief Metoda ustawiaj�ca prze�roczysto�� kontrolki.
			*
			* Metoda ustawia prze�roczysto�� kontrolki
			* \param[in] przezroczystosc - stopie� prze�roczysto�ci kontrolki.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			void setTransparency(unsigned char przezroczystosc) override;

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
			* \brief Metoda tworz�ca kopi� obiektu.
			*
			* Metoda tworzy kopi� obiektu.
			* \return Wska�nik na skopiowany obiekt.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			SurowiecGui* clone() override;

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

			/**
			* \brief Metoda ustawiaj�ca warto�� w�a�ciwo�ci.
			*
			* Metoda ustawia warto�� w�a�ciwo�ci zgodnie z danymi przekazanymi w parametrach.
			* \param[in] wlasciwosc - Nazwa w�a�ciwo�ci kontrolki.
			* \param[in] wartosc - Warto�� w�a�ciwo�ci kontrolki.
			* \return Zwracana jest warto�� true je�eli uda si� ustawi� warto��. W przeciwnym wypadku jest zwracana warto�� false.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
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
			* \date 01-10-2014
			*/
			bool getProperty(std::string wlasciwosc, std::string& wartosc) const override;

			/**
			* \brief Metoda zwracaj�ca list� w�a�ciwo�ci.
			*
			* Metoda zwraca list� w�a�ciwo�ci jakie mo�na ustawi� w kontrolce.
			* \return Lista w�a�ciwo�ci.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			std::list< std::pair<std::string, std::string> > getPropertyList() const override;
		private:

			/**
			* \brief Metoda inicjalizuj�ca obiekt.
			*
			* Metoda inicjalizuje obiekt kontrolki podstawowymi parametrami.
			* \param[in] kontener - Wska�nik na kontener, w kt�rym ma znajdowa� si� obiekt.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			void initialize(Container *const kontener) override;

			std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.
			Label::Ptr tekst_; /// Prezentowany tekst.
			STyp::Identyfikator idObiektu_; /// Identyfikator reprezentowanego obiektu.
		};

		/**
		* \brief Metoda inicjalizuj�ca obiekt.
		*
		* Metoda inicjalizuje obiekt kontrolki podstawowymi parametrami.
		* \param[in] kontener - Wska�nik na kontener, w kt�rym ma znajdowa� si� obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void initialize(Container *const kontener) override;
		
		/**
		* \brief Metoda od�wie�aj�ca pozycj� kontrolek.
		*
		* Metoda od�wie�a pozycj� kontrolek.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void odswiezPozycje();

		mutable std::mutex zmianaDanych_; /// Muteks dost�pu do modyfikacji danych kontrolek.
		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.
		SurowiecGui::Ptr szablonKontrolki_; /// Wska�nik na szablon kontrolki obiektu.
		std::vector<SurowiecGui::Ptr> kontrolki_; /// Kontener z kontrolkami obiekt�w.

	};
};
