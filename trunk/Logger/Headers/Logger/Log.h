#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "LoggerSymbol.h"
#include "LoggerInterface.h"

namespace SLog{
	/**
	* Klasa zarz�dzaj�ca wy�wietlaniem komunikat�w loguj�cych.
	* Udowst�pnia mo�liwo�� blokowania pojedy�czych poziom�w komunikat�w jak i wszystkich jednocze�nie.\n
	* Klasa implementuje 4 rodzaje komunikat�w:
	*	- Debug
	*	- Info
	*	- Warning
	*	- Error
	*/
	class LOGGER_API Log
	{
	public:
		/**
		* Enumeracja zawieraj�ca definicje poziom�w logowania.
		*/
		enum TypLogow{
			All,
			Debug,
			Info,
			Warning,
			Error
		};

		/**
		* Enumeracja zawieraj�ca definicje dost�pnych format�w daty i czasu zwracanych przez funkcj� pobierzDateCzas().
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
		* Typ funkcji wysy�aj�cej logi do strumienia. Funkcja otrzymuje informacje jaki jest poziom log�w oraz napis do wy�wietlenia.
		* Napis jest pe�nym komunikatem z dat� i nazw� poziomu log�w.
		*/
		typedef std::function<void(TypLogow, const std::string&)> Strumien;

		
		/**
		* Metoda dodaj�ca strumien wyj�ciowy do
		* \param[in] strumien - Strumie� do wysy�ania danych
		*/
		void dodajGniazdoWyjsciowe(const Strumien& strumien);

		/**
		* Metoda ustawiaj�ca fomat w jakim ma by� wy�wietlana data i czas w logach.
		* \param[in] format - Format wy�wietlanegej daty i czasu.
		*/
		void ustawFormatCzasu(FormatCzasu format);

		/**
		* Funkcja informuj�ca czy wysy�anie log�w jest odblokowane.
		* \return Je�eli wysy�anie log�w jest odblokowane zwraca true, je�eli nie zwraca false.
		*/
		bool czyLogiOdblokowane(TypLogow typ)const;

		/**
		* Odblokowanie wysy�ania log�w do strumienia.
		*/
		void odblokujLogi(TypLogow typ);

		/**
		* Zablokowanie wysy�ania log�w do strumienia.
		*/
		void zablokujLogi(TypLogow typ);

		/**
		* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa�no�ci komunikatu.
		* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
		*/
		void loguj(TypLogow typ, const std::string& komunikat) const;

		/**
		* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa�no�ci komunikatu.
		* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
		*/
		void loguj(TypLogow typ, const LoggerInterface& komunikat) const;

		/**
		* Funkcja polecaj�ca aktualn� dat� i czas.
		* \return Aktualna data i czas.
		* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
		* \sa ustawFormatCzasu()
		*/
		std::string pobierzDateCzas() const;

		/**
		* Metoda pobieraj�ca instancj� klasy zapisuj�cej logi.
		* \return Instancja obiektu log�w.
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
		* Konstruktor kopiuj�cy.
		*/
		Log(const Log&) = default;

		/**
		* Operator przypisania.
		*/
		Log& operator=(const Log&) = default;


		std::vector< Strumien > outstream; /// Tablica strumieni do kt�rych ma zosta� wysy�any log.

		/**
		* Funkcja wysy�aj�ca napis do strumienia.
		* \param[in] typ - poziom wa�no�ci komunikatu.
		* \param[in] napis - Napis wysy�any do strumienia.
		*/
		void wyswietl(TypLogow typ, const std::string& napis) const;

		std::vector< bool > poziomy_ = { { true, true, true, true, true } }; /// Warto�� w��czenia/wy��czenia poziom�w logowania. Domy�lenie wszystkie na w��czone.
		std::string formatCzasu_ = "%Y-%m-%d %H:%M:%S"; /// Format w jakim ma zosta� wy�iwetlany czas logowania. Domy�lenie: \%Y-\%m-\%d \%H:\%M:\%S.

	};
}
