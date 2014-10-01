#pragma once
#include <TGUI\TGUI.hpp>
#include "PomocniczeTypyTGUI.h"

namespace tgui{

	/**
	* \brief Klasa kontrolki wyœwietlaj¹cej logi.
	*
	* Klasa reprezentuje kontrolkê wyœwietlaj¹cej logi.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuniêcie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 30-09-2014
	*/
	class LogListGui :
		public Panel
	{
	private:

		/**
		* \brief Klasa opisuj¹ca typ kounikatu w logach.
		*
		* Klasa reprezentuje typ komunikatu wyœwietlanego w kontrolce logów.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		struct MessageTypeDescription{

			/**
			* \brief Konstruktor obiektu.
			*
			* Konstruktor obiektu.
			* \param[in] pierwszyKolor - Pierwszy kolor komunikatu.
			* \param[in] drugiKolor - Drugi kolor komunikatu.
			* \param[in] pierwszyRozmiarCzcionki - Pierwszy rozmiar czcionki komunikatu.
			* \param[in] drugiRozmiarCzcionki - Drugi rozmiar czcionki komunikatu.
			* \author Daniel Wojdak
			* \version 2
			* \date 30-09-2014
			*/
			MessageTypeDescription(const sf::Color& pierwszyKolor, const sf::Color& drugiKolor, unsigned int pierwszyRozmiarCzcionki, unsigned int drugiRozmiarCzcionki)
				: pierwszyKolor_(pierwszyKolor), drugiKolor_(drugiKolor), pierwszyRozmiarCzcionki_(pierwszyRozmiarCzcionki), drugiRozmiarCzcionki_(drugiRozmiarCzcionki)
			{
			}
			
			sf::Color pierwszyKolor_; /// Pierwszy kolor komunikatu.
			sf::Color drugiKolor_; /// Drugi kolor komunikatu.
			unsigned int pierwszyRozmiarCzcionki_; /// Pierwszy rozmiar czcionki komunikatu.
			unsigned int drugiRozmiarCzcionki_; /// Drugi rozmiar czcionki komunikatu.
		};

	public:
		/**
		* \brief Metoda tworzy kontrolkê.
		*
		* Metoda tworzy obiekt klasy LogListGui.
		* \param[in] kontener - WskaŸnik do kontenera, w którym ma znajdowaæ siê stworzony obiekt.
		* \param[in] nazwa - Nazwa nowo stworzonego obiektu.
		* \return WskaŸnik na nowo stworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		static Widget* createWidget(Container* kontener, const std::string& nazwa);

		typedef std::vector<MessageTypeDescription>::size_type MessageType; /// Typ okreœlaj¹cy numer u¿ytego komunikatu.

		typedef SharedWidgetPtr<LogListGui> Ptr; /// Inteligentny wskaŸnik na obiekt kontrolki.

		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		LogListGui() = default;

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~LogListGui() = default;

		/**
		* \brief Metoda usuwaj¹ca ostatni komunikat.
		*
		* Metoda usuwa najstarszy komunikat z listy wyœwietlanych komunikatów.
		* \return Zwracana jest wartoœæ true, je¿eli uda³o sie usun¹æ komunikat lub false, je¿eli nie ma komunikatów do usuniêcia.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool deleteLastMessage();

		/**
		* \brief Metoda dodaj¹ca komunikat do listy.
		*
		* Metoda dodaje komunikat do listy wyœwietlanych komunikatów.
		* \param[in] numer - Numer okreœlaj¹cy rodzaj komunikatu.
		* \param[in] tekst - Tekst komunikatu.
		* \return Zwracana jest wartoœæ true, je¿eli uda³o sie dodaæ komunikat lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool addMessage( MessageType numer, std::string tekst);

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
		LogListGui* clone() override;

		/**
		* \brief Metoda czyszcz¹ca listê komunikatów.
		*
		* Metoda czyœci listê wyœwietlanych komunikatów.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void clear();

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

	private:

		/**
		* \brief Metoda przeliczaj¹ca pozycjê komunikatów w oknie.
		*
		* Metoda przelicza pozycje komunikatów w oknie.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void recalculatePosition();

		typedef std::vector< std::pair< MessageType, Label::Ptr> > ObjectList; /// Typ kontenera przechowuj¹cego kontrolki z treœci¹ komunikatów.

		/**
		* \brief Metoda przeliczaj¹ca pozycjê komunikatu.
		*
		* Metoda oblicza pozycjê komunikatów w liœcie kontrolek.
		* \param[in] pozycja - pozycja do przeliczenia.
		* \return Przeliczona wartoœæ pozycji.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		ObjectList::size_type pos(int pozycja)const;

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

		std::string m_LoadedConfigFile = ""; /// Adres pliku konfiguracyjnego.

		ObjectList listaObiektow_; /// Lista kontrolek wyœwietlaj¹cych komunikaty.
		std::vector<MessageTypeDescription> opisTypowKomunikatow_; /// Lista opisów typów komunikatów.
		Borders margines_; /// Margines napisów w kontrolce.
		float odstep_ = 0.f; /// Odstêp miêdzy napisami.
		unsigned int zajete_ = 0; /// Zajête linie komunikatów.
		unsigned int puste_ = 0; /// Puste linie komunikatów.
		unsigned int wszystkie_ = 0; /// Wszystkie linie komunikatów.
		bool czyAutoRozmiar_ = true; /// Automatyczne wyliczanie rozmiarów.

		WYROWNANIE_WERTYKALNE wPionie_ = TOP; /// Wyrównanie w pionie.
		WYROWNANIE_HORYZONTALNE wPoziomie_ = CENTER; /// Wyrównanie w poziomie.

	};
};
