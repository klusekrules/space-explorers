#pragma once
#include <TGUI\TGUI.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "Model\ObiektInfo.h"

namespace tgui{

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
		public Panel
	{
	public:
		/**
		* \brief Metoda tworzy kontrolkê.
		*
		* Metoda tworzy obiekt klasy ListaSurowcowGui.
		* \param[in] kontener - WskaŸnik do kontenera, w którym ma znajdowaæ siê stworzony obiekt.
		* \param[in] nazwa - Nazwa nowo stworzonego obiektu.
		* \return WskaŸnik na nowo stworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		static Widget* createWidget(Container* kontener, const std::string& nazwa);

		typedef SharedWidgetPtr<ListaSurowcowGui> Ptr; /// Inteligentny wskaŸnik na obiekt kontrolki.
		
		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		ListaSurowcowGui() = default;

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

		/**
		* \brief Metoda ustawiaj¹ca przeŸroczystoœæ kontrolki.
		*
		* Metoda ustawia przeŸroczystoœæ kontrolki
		* \param[in] przezroczystosc - stopieñ przeŸroczystoœci kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
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
		* \date 01-10-2014
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
		* \date 01-10-2014
		*/
		bool load(const std::string& configFileFilename);

		/**
		* \brief Metoda tworz¹ca kopiê obiektu.
		*
		* Metoda tworzy kopiê obiektu.
		* \return WskaŸnik na skopiowany obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		ListaSurowcowGui* clone() override;

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

		/**
		* \brief Metoda ustawiaj¹ca wartoœæ w³aœciwoœci.
		*
		* Metoda ustawia wartoœæ w³aœciwoœci zgodnie z danymi przekazanymi w parametrach.
		* \param[in] wlasciwosc - Nazwa w³aœciwoœci kontrolki.
		* \param[in] wartosc - Wartoœæ w³aœciwoœci kontrolki.
		* \return Zwracana jest wartoœæ true je¿eli uda siê ustawiæ wartoœæ. W przeciwnym wypadku jest zwracana wartoœæ false.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
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
		* \date 01-10-2014
		*/
		bool getProperty(std::string wlasciwosc, std::string& wartosc) const override;

		/**
		* \brief Metoda zwracaj¹ca listê w³aœciwoœci.
		*
		* Metoda zwraca listê w³aœciwoœci jakie mo¿na ustawiæ w kontrolce.
		* \return Lista w³aœciwoœci.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
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
		* \date 01-10-2014
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		/**
		* \brief Klasa kontrolki surowca.
		*
		* Klasa reprezentuje kontrolkê surowca. Wyœwietla iloœæ surowca na planecie.
		* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		class SurowiecGui :
			public Panel
		{
		public:
			typedef SharedWidgetPtr<SurowiecGui> Ptr; /// Inteligentny wskaŸnik na obiekt kontrolki.
			
			/**
			* \brief Domyœlny konstruktor.
			*
			* Domyœlny konstruktor.
			*/
			SurowiecGui() = default;

			/**
			* \brief Konstruktor kopiuj¹cy.
			*
			* Konstruktor kopiuj¹cy.
			* \param[in] zrodlowy - Obiekt Ÿród³owy.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			SurowiecGui(const SurowiecGui& zrodlowy);

			/**
			* \brief Domyœlny destruktor.
			*
			* Domyœlny destruktor.
			*/
			virtual ~SurowiecGui() = default;

			/**
			* \brief Metoda pobieraj¹ca identyfikator obiektu.
			*
			* Metoda pobiera identyfikator reprezentowanego obiektu.
			* \return Identyfikator reprezentowanego obiektu.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			const STyp::Identyfikator& pobierzIdObiektu() const;

			/**
			* \brief Metoda ustawiaj¹ca dane w kontrolce.
			*
			* Metoda ustawia dane reprezentowanego obiektu w kontrolce.
			* \param[in] obiekt - Reprezentowany obiekt.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			void ustawDane(const SpEx::Obiekt& obiekt);

			/**
			* \brief Metoda ustawiaj¹ca przeŸroczystoœæ kontrolki.
			*
			* Metoda ustawia przeŸroczystoœæ kontrolki
			* \param[in] przezroczystosc - stopieñ przeŸroczystoœci kontrolki.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			void setTransparency(unsigned char przezroczystosc) override;

			/**
			* \brief Metoda ustawiaj¹ca rozmiar tekstu.
			*
			* Metoda ustawia rozmiar tekstu wyœwietlanego w kontrolce.
			* \param[in] rozmiar - Rozmiar tekstu.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			void setTextSize(unsigned int rozmiar);
			/**
			* \brief Metoda ustawiaj¹ca kolor tekstu.
			*
			* Metoda ustawia kolor tekstu wyœwietlanego w kontrolce.
			* \param[in] kolor - Kolor tekstu.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			void setTextColor(sf::Color kolor);

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
			* \brief Metoda tworz¹ca kopiê obiektu.
			*
			* Metoda tworzy kopiê obiektu.
			* \return WskaŸnik na skopiowany obiekt.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			SurowiecGui* clone() override;

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

			/**
			* \brief Metoda ustawiaj¹ca wartoœæ w³aœciwoœci.
			*
			* Metoda ustawia wartoœæ w³aœciwoœci zgodnie z danymi przekazanymi w parametrach.
			* \param[in] wlasciwosc - Nazwa w³aœciwoœci kontrolki.
			* \param[in] wartosc - Wartoœæ w³aœciwoœci kontrolki.
			* \return Zwracana jest wartoœæ true je¿eli uda siê ustawiæ wartoœæ. W przeciwnym wypadku jest zwracana wartoœæ false.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
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
			* \date 01-10-2014
			*/
			bool getProperty(std::string wlasciwosc, std::string& wartosc) const override;

			/**
			* \brief Metoda zwracaj¹ca listê w³aœciwoœci.
			*
			* Metoda zwraca listê w³aœciwoœci jakie mo¿na ustawiæ w kontrolce.
			* \return Lista w³aœciwoœci.
			* \author Daniel Wojdak
			* \version 2
			* \date 01-10-2014
			*/
			std::list< std::pair<std::string, std::string> > getPropertyList() const override;
		private:

			/**
			* \brief Metoda inicjalizuj¹ca obiekt.
			*
			* Metoda inicjalizuje obiekt kontrolki podstawowymi parametrami.
			* \param[in] kontener - WskaŸnik na kontener, w którym ma znajdowaæ siê obiekt.
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
		* \brief Metoda inicjalizuj¹ca obiekt.
		*
		* Metoda inicjalizuje obiekt kontrolki podstawowymi parametrami.
		* \param[in] kontener - WskaŸnik na kontener, w którym ma znajdowaæ siê obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void initialize(Container *const kontener) override;
		
		/**
		* \brief Metoda odœwie¿aj¹ca pozycjê kontrolek.
		*
		* Metoda odœwie¿a pozycjê kontrolek.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-10-2014
		*/
		void odswiezPozycje();

		mutable std::mutex zmianaDanych_; /// Muteks dostêpu do modyfikacji danych kontrolek.
		std::string plikKonfiguracyjny_ = ""; /// Adres pliku konfiguracyjnego.
		SurowiecGui::Ptr szablonKontrolki_; /// WskaŸnik na szablon kontrolki obiektu.
		std::vector<SurowiecGui::Ptr> kontrolki_; /// Kontener z kontrolkami obiektów.

	};
};
