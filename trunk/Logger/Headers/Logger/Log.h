#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "LoggerSymbol.h"
#include "LoggerInterface.h"

namespace SLog{
	/**
	* Klasa zarz¹dzaj¹ca wyœwietlaniem komunikatów loguj¹cych.
	* Udowstêpnia mo¿liwoœæ blokowania pojedyñczych poziomów komunikatów jak i wszystkich jednoczeœnie.\n
	* Klasa implementuje 4 rodzaje komunikatów:
	*	- Debug
	*	- Info
	*	- Warning
	*	- Error
	*/
	class LOGGER_API Log
	{
	public:
		/**
		* Enumeracja zawieraj¹ca definicje poziomów logowania.
		*/
		enum TypLogow{
			All,
			Debug,
			Info,
			Warning,
			Error
		};

		/**
		* Enumeracja zawieraj¹ca definicje dostêpnych formatów daty i czasu zwracanych przez funkcjê pobierzDateCzas().
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
		*/
		typedef std::function<void(TypLogow, const std::string&)> Strumien;

		
		/**
		* Metoda dodaj¹ca strumien wyjœciowy do
		* \param[in] strumien - Strumieñ do wysy³ania danych
		*/
		void dodajGniazdoWyjsciowe(const Strumien& strumien);

		/**
		* Metoda ustawiaj¹ca fomat w jakim ma byæ wyœwietlana data i czas w logach.
		* \param[in] format - Format wyœwietlanegej daty i czasu.
		*/
		void ustawFormatCzasu(FormatCzasu format);

		/**
		* Funkcja informuj¹ca czy wysy³anie logów jest odblokowane.
		* \return Je¿eli wysy³anie logów jest odblokowane zwraca true, je¿eli nie zwraca false.
		*/
		bool czyLogiOdblokowane(TypLogow typ)const;

		/**
		* Odblokowanie wysy³ania logów do strumienia.
		*/
		void odblokujLogi(TypLogow typ);

		/**
		* Zablokowanie wysy³ania logów do strumienia.
		*/
		void zablokujLogi(TypLogow typ);

		/**
		* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa¿noœci komunikatu.
		* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
		*/
		void loguj(TypLogow typ, const std::string& komunikat) const;

		/**
		* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa¿noœci komunikatu.
		* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
		*/
		void loguj(TypLogow typ, const LoggerInterface& komunikat) const;

		/**
		* Funkcja polecaj¹ca aktualn¹ datê i czas.
		* \return Aktualna data i czas.
		* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
		* \sa ustawFormatCzasu()
		*/
		std::string pobierzDateCzas() const;

		/**
		* Metoda pobieraj¹ca instancjê klasy zapisuj¹cej logi.
		* \return Instancja obiektu logów.
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
		* \param[in] napis - Napis wysy³any do strumienia.
		*/
		void wyswietl(TypLogow typ, const std::string& napis) const;

		std::vector< bool > poziomy_ = { { true, true, true, true, true } }; /// Wartoœæ w³¹czenia/wy³¹czenia poziomów logowania. Domyœlenie wszystkie na w³¹czone.
		std::string formatCzasu_ = "%Y-%m-%d %H:%M:%S"; /// Format w jakim ma zosta³ wyœiwetlany czas logowania. Domyœlenie: \%Y-\%m-\%d \%H:\%M:\%S.

	};
}
