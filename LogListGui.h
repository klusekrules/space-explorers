#pragma once
#include <TGUI\TGUI.hpp>
#include "PomocniczeTypyTGUI.h"

namespace tgui{

	/**
	* \brief Klasa kontrolki wy�wietlaj�cej logi.
	*
	* Klasa reprezentuje kontrolk� wy�wietlaj�cej logi.
	* \warning Uwaga!!! Klasa przeznaczona do refaktoryzacji. Przesuni�cie refaktoryzacji do czasu migracji do TGUI v7.
	* \author Daniel Wojdak
	* \version 2
	* \date 30-09-2014
	*/
	class LogListGui :
		public Panel
	{
	private:

		/**
		* \brief Klasa opisuj�ca typ kounikatu w logach.
		*
		* Klasa reprezentuje typ komunikatu wy�wietlanego w kontrolce log�w.
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
		* \brief Metoda tworzy kontrolk�.
		*
		* Metoda tworzy obiekt klasy LogListGui.
		* \param[in] kontener - Wska�nik do kontenera, w kt�rym ma znajdowa� si� stworzony obiekt.
		* \param[in] nazwa - Nazwa nowo stworzonego obiektu.
		* \return Wska�nik na nowo stworzony obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		static Widget* createWidget(Container* kontener, const std::string& nazwa);

		typedef std::vector<MessageTypeDescription>::size_type MessageType; /// Typ okre�laj�cy numer u�ytego komunikatu.

		typedef SharedWidgetPtr<LogListGui> Ptr; /// Inteligentny wska�nik na obiekt kontrolki.

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		LogListGui() = default;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~LogListGui() = default;

		/**
		* \brief Metoda usuwaj�ca ostatni komunikat.
		*
		* Metoda usuwa najstarszy komunikat z listy wy�wietlanych komunikat�w.
		* \return Zwracana jest warto�� true, je�eli uda�o sie usun�� komunikat lub false, je�eli nie ma komunikat�w do usuni�cia.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool deleteLastMessage();

		/**
		* \brief Metoda dodaj�ca komunikat do listy.
		*
		* Metoda dodaje komunikat do listy wy�wietlanych komunikat�w.
		* \param[in] numer - Numer okre�laj�cy rodzaj komunikatu.
		* \param[in] tekst - Tekst komunikatu.
		* \return Zwracana jest warto�� true, je�eli uda�o sie doda� komunikat lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		bool addMessage( MessageType numer, std::string tekst);

		/**
		* \brief Metoda ustawiaj�ca rozmiar kontrolki.
		*
		* Metoda ustawia rozmiar kontrolki
		* \param[in] szerokosc - szeroko�� kontrolki.
		* \param[in] wysokosc - wysoko�� kontrolki.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
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
		* \date 30-09-2014
		*/
		bool load(const std::string& adresPlikuKonfiguracyjnego);

		/**
		* \brief Metoda tworz�ca kopi� obiektu.
		*
		* Metoda tworzy kopi� obiektu.
		* \return Wska�nik na skopiowany obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		LogListGui* clone() override;

		/**
		* \brief Metoda czyszcz�ca list� komunikat�w.
		*
		* Metoda czy�ci list� wy�wietlanych komunikat�w.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void clear();

		/**
		* \brief Metoda zwracaj�ca adres pliku konfiguracynego.
		*
		* Metoda zwraca adres pliku konfiguracyjnego, z kt�rego zosta�y zaczytane parametry kontrolki.
		* \return Adres pliku konfiguracyjnego.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
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
		* \date 30-09-2014
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
		* \date 30-09-2014
		*/
		bool getProperty(std::string wlasciwosc, std::string& wartosc) const override;

		/**
		* \brief Metoda zwracaj�ca list� w�a�ciwo�ci.
		*
		* Metoda zwraca list� w�a�ciwo�ci jakie mo�na ustawi� w kontrolce.
		* \return Lista w�a�ciwo�ci.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		std::list< std::pair<std::string, std::string> > getPropertyList() const override;

	private:

		/**
		* \brief Metoda przeliczaj�ca pozycj� komunikat�w w oknie.
		*
		* Metoda przelicza pozycje komunikat�w w oknie.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void recalculatePosition();

		typedef std::vector< std::pair< MessageType, Label::Ptr> > ObjectList; /// Typ kontenera przechowuj�cego kontrolki z tre�ci� komunikat�w.

		/**
		* \brief Metoda przeliczaj�ca pozycj� komunikatu.
		*
		* Metoda oblicza pozycj� komunikat�w w li�cie kontrolek.
		* \param[in] pozycja - pozycja do przeliczenia.
		* \return Przeliczona warto�� pozycji.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		ObjectList::size_type pos(int pozycja)const;

		/**
		* \brief Metoda inicjalizuj�ca obiekt.
		*
		* Metoda inicjalizuje obiekt kontrolki podstawowymi parametrami.
		* \param[in] kontener - Wska�nik na kontener, w kt�rym ma znajdowa� si� obiekt.
		* \author Daniel Wojdak
		* \version 2
		* \date 30-09-2014
		*/
		void initialize(Container *const kontener) override;

		std::string m_LoadedConfigFile = ""; /// Adres pliku konfiguracyjnego.

		ObjectList listaObiektow_; /// Lista kontrolek wy�wietlaj�cych komunikaty.
		std::vector<MessageTypeDescription> opisTypowKomunikatow_; /// Lista opis�w typ�w komunikat�w.
		Borders margines_; /// Margines napis�w w kontrolce.
		float odstep_ = 0.f; /// Odst�p mi�dzy napisami.
		unsigned int zajete_ = 0; /// Zaj�te linie komunikat�w.
		unsigned int puste_ = 0; /// Puste linie komunikat�w.
		unsigned int wszystkie_ = 0; /// Wszystkie linie komunikat�w.
		bool czyAutoRozmiar_ = true; /// Automatyczne wyliczanie rozmiar�w.

		WYROWNANIE_WERTYKALNE wPionie_ = TOP; /// Wyr�wnanie w pionie.
		WYROWNANIE_HORYZONTALNE wPoziomie_ = CENTER; /// Wyr�wnanie w poziomie.

	};
};
