#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "LoggerSymbol.h"
#include "LoggerInterface.h"

namespace SLog{
	/**
	* Klasa zarz¹dzaj¹ca wyœwietlaniem komunikatów loguj¹cych.
	* Udowstêpnia mo¿liwoœæ blokowania pojedyñczych poziomów komunikatów jak i wszystkich jednoczeœnie.
	* \par Typy komunikatów
	* Klasa implementuje 4 rodzaje komunikatów:
	*	- Debug
	*	- Info
	*	- Warning
	*	- Error
	* \author Daniel Wojdak
	* \version 2
	* \date 18-06-2014
	*/
	class LOGGER_API Log
	{
	public:
		/**
		* Enumeracja zawieraj¹ca definicje poziomów logowania.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		enum TypLogow{
			/// Wyœwietlane s¹ wszystkie komunikaty logowania.
			All,
			/// Wyœwietlane s¹ logi typu Debug.
			Debug,
			/// Wyœwietlane s¹ logi typu Info.
			Info,
			/// Wyœwietlane s¹ logi typu Warning.
			Warning,
			/// Wyœwietlane s¹ logi typu Error
			Error
		};

		/**
		* Enumeracja zawieraj¹ca definicje dostêpnych formatów daty i czasu zwracanych przez funkcjê pobierzDateCzas().
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		enum FormatCzasu{
			/// Sama data
			Data,
			/// Sam czas
			Czas,
			/// Data i Czas
			DataCzas 
		};

		/**
		* Typ funkcji wysy³aj¹cej logi do strumienia. Funkcja otrzymuje informacje jaki jest poziom logów oraz napis do wyœwietlenia.
		* Napis jest pe³nym komunikatem z datê i nazwê poziomu logów.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		typedef std::function<void(TypLogow, const std::string&, const std::string&)> Strumien;

		
		/**
		* Metoda dodaj¹ca strumien wyjœciowy do
		* \param[in] strumien - Strumieñ do wysy³ania danych
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajGniazdoWyjsciowe(const Strumien& strumien);

		/**
		* Metoda ustawiaj¹ca fomat w jakim ma byæ wyœwietlana data i czas w logach.
		* \param[in] format - Format wyœwietlanegej daty i czasu.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void ustawFormatCzasu(FormatCzasu format);

		/**
		* Funkcja informuj¹ca czy wysy³anie logów jest odblokowane.
		* \return Je¿eli wysy³anie logów jest odblokowane zwraca true, je¿eli nie zwraca false.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		bool czyLogiOdblokowane(TypLogow typ)const;

		/**
		* Odblokowanie wysy³ania logów do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void odblokujLogi(TypLogow typ);

		/**
		* Zablokowanie wysy³ania logów do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void zablokujLogi(TypLogow typ);

		/**
		* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa¿noœci komunikatu.
		* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void loguj(TypLogow typ, const std::string& komunikat) const;

		/**
		* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa¿noœci komunikatu.
		* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void loguj(TypLogow typ, const LoggerInterface& komunikat) const;

		/**
		* Funkcja polecaj¹ca aktualn¹ datê i czas.
		* \return Aktualna data i czas.
		* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		* \sa ustawFormatCzasu()
		*/
		std::string pobierzDateCzas() const;

		/**
		* Metoda pobieraj¹ca instancjê klasy zapisuj¹cej logi.
		* \return Instancja obiektu logów.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		static Log& pobierzInstancje();
		
		/**
		* Destruktor.
		*/
		~Log() = default;

	private:

		/**
		* Konstruktor.
		*/
		Log() = default;

		/**
		* Konstruktor kopiuj¹cy.
		*/
		Log(const Log&) = default;

		/**
		* Operator przypisania.
		*/
		Log& operator=(const Log&) = default;


		std::vector< Strumien > outstream; /// Tablica strumieni do których ma zostaæ wysy³any log.

		/**
		* Funkcja wysy³aj¹ca napis do strumienia.
		* \param[in] typ - poziom wa¿noœci komunikatu.
		* \param[in] czas - czas stworzenia komunikatu.
		* \param[in] napis - Napis wysy³any do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void wyswietl(TypLogow typ, const std::string& czas, const std::string& napis) const;

		std::vector< bool > poziomy_ = { { true, true, true, true, true } }; /// Wartoœæ w³¹czenia/wy³¹czenia poziomów logowania. Domyœlenie wszystkie na w³¹czone.
		std::string formatCzasu_ = "%Y-%m-%d %H:%M:%S"; /// Format w jakim ma zosta³ wyœiwetlany czas logowania. Domyœlenie: \%Y-\%m-\%d \%H:\%M:\%S.

	};
}
