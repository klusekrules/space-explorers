#pragma once
#include <sstream>
#include <vector>
#include <functional>
#include "LoggerSymbol.h"
#include "LoggerInterface.h"

namespace SLog{
	/**
	* Klasa zarz�dzaj�ca wy�wietlaniem komunikat�w loguj�cych.
	* Udowst�pnia mo�liwo�� blokowania pojedy�czych poziom�w komunikat�w jak i wszystkich jednocze�nie.
	* \par Typy komunikat�w
	* Klasa implementuje 4 rodzaje komunikat�w:
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
		* Enumeracja zawieraj�ca definicje poziom�w logowania.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		enum TypLogow{
			/// Wy�wietlane s� wszystkie komunikaty logowania.
			All,
			/// Wy�wietlane s� logi typu Debug.
			Debug,
			/// Wy�wietlane s� logi typu Info.
			Info,
			/// Wy�wietlane s� logi typu Warning.
			Warning,
			/// Wy�wietlane s� logi typu Error
			Error
		};

		/**
		* Enumeracja zawieraj�ca definicje dost�pnych format�w daty i czasu zwracanych przez funkcj� pobierzDateCzas().
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
		* Typ funkcji wysy�aj�cej logi do strumienia. Funkcja otrzymuje informacje jaki jest poziom log�w oraz napis do wy�wietlenia.
		* Napis jest pe�nym komunikatem z dat� i nazw� poziomu log�w.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		typedef std::function<void(TypLogow, const std::string&, const std::string&)> Strumien;

		
		/**
		* Metoda dodaj�ca strumien wyj�ciowy do
		* \param[in] strumien - Strumie� do wysy�ania danych
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajGniazdoWyjsciowe(const Strumien& strumien);

		/**
		* Metoda ustawiaj�ca fomat w jakim ma by� wy�wietlana data i czas w logach.
		* \param[in] format - Format wy�wietlanegej daty i czasu.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void ustawFormatCzasu(FormatCzasu format);

		/**
		* Funkcja informuj�ca czy wysy�anie log�w jest odblokowane.
		* \return Je�eli wysy�anie log�w jest odblokowane zwraca true, je�eli nie zwraca false.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		bool czyLogiOdblokowane(TypLogow typ)const;

		/**
		* Odblokowanie wysy�ania log�w do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void odblokujLogi(TypLogow typ);

		/**
		* Zablokowanie wysy�ania log�w do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void zablokujLogi(TypLogow typ);

		/**
		* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa�no�ci komunikatu.
		* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void loguj(TypLogow typ, const std::string& komunikat) const;

		/**
		* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
		* \param[in] typ - poziom wa�no�ci komunikatu.
		* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void loguj(TypLogow typ, const LoggerInterface& komunikat) const;

		/**
		* Funkcja polecaj�ca aktualn� dat� i czas.
		* \return Aktualna data i czas.
		* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		* \sa ustawFormatCzasu()
		*/
		std::string pobierzDateCzas() const;

		/**
		* Metoda pobieraj�ca instancj� klasy zapisuj�cej logi.
		* \return Instancja obiektu log�w.
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
		* \param[in] czas - czas stworzenia komunikatu.
		* \param[in] napis - Napis wysy�any do strumienia.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void wyswietl(TypLogow typ, const std::string& czas, const std::string& napis) const;

		std::vector< bool > poziomy_ = { { true, true, true, true, true } }; /// Warto�� w��czenia/wy��czenia poziom�w logowania. Domy�lenie wszystkie na w��czone.
		std::string formatCzasu_ = "%Y-%m-%d %H:%M:%S"; /// Format w jakim ma zosta� wy�iwetlany czas logowania. Domy�lenie: \%Y-\%m-\%d \%H:\%M:\%S.

	};
}
