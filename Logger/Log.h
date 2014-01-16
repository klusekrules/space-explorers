#pragma once
#include "stdafx.h"
#include "ExportSymbol.h"
#include "LoggerInterface.h"

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
		Data, /// Sama data
		Czas, /// Sam czas
		DataCzas /// Data i Czas
	};
 
	/**
	* Typ funkcji wysy?aj?cej logi do strumienia. Funkcja otrzymuje informacje jaki jest poziom log?w oraz napis do wy?wietlenia.
	* Napis jest pe?nym komunikatem z dat? i nazw? poziomu log?w.
	*/
	typedef std::function<void(TypLogow,const std::string&)> Strumien;

	/**
	* Konstruktor.
 	*/
	Log() = default;

	/**
	* Destruktor.
	*/
	~Log() = default;

	/**
	* Konstruktor kopiuj?cy.
	*/
	Log(const Log&) = delete;

	/**
	* Konstruktor przenosz?cy.
	*/
	Log(Log&&) = delete;

	/**
	* Operator przypisania.
	*/
	Log& operator=(const Log&) = delete;

	/**
	* Operator przenoszenia.
	*/
	Log&& operator=(Log&&) = delete;

	/**
	* Metoda dodaj¹ca strumien wyjœciowy do 
	* \param[in] strumien - Strumieñ do wysy³ania danych 
	*/
	void dodajGniazdoWyjsciowe( const Strumien& strumien );

	/**
	* Metoda ustawiaj¹ca fomat w jakim ma byæ wyœwietlana data i czas w logach.
	* \param[in] format - Format wyœwietlanegej daty i czasu.
	*/
	void ustawFormatCzasu( FormatCzasu format );

	/**
	* Funkcja informuj¹ca czy wysy³anie logów jest odblokowane.
	* \return Je¿eli wysy³anie logów jest odblokowane zwraca true, je¿eli nie zwraca false.
	*/
	bool czyLogiOdblokowane( TypLogow typ )const;

	/**
	* Odblokowanie wysy³ania logów do strumienia.
	*/
	void odblokujLogi( TypLogow typ );

	/**
	* Zablokowanie wysy³ania logów do strumienia.
	*/
	void zablokujLogi( TypLogow typ );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void loguj( TypLogow typ, const std::string& komunikat ) const;

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void loguj( TypLogow typ, const LoggerInterface& komunikat ) const;

	/**
	* Funkcja polecaj¹ca aktualn¹ datê i czas.
	* \return Aktualna data i czas.
	* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
	* \sa ustawFormatCzasu()
	*/
	std::string&& pobierzDateCzas() const;

	/**
	* Metoda pobieraj?ca instancj? klasy zapisuj?cej logi. 
	* \return Instancja obiektu logów.
	*/
	static Log& pobierzInstancje();

private:

	std::vector< Strumien > outstream; /// Tablica strumieni do których ma zostaæ wysy³any log.

	/**
	* Funkcja wysy³aj¹ca napis do strumienia.
	* \param[in] napis - Napis wysy³any do strumienia.
	*/
	void wyswietl( TypLogow typ, const std::string& napis ) const;
		
	std::vector< bool > poziomy_ = { { true, true, true, true, true } }; /// Warto?? w??czenia/wy??czenia poziom?w logowania. Domy?lenie wszystkie na w??czone.
	std::string formatCzasu_ = "%Y-%m-%d %H:%M:%S"; /// Format w jakim ma zosta? wy?iwetlany czas logowania. Domy?lenie: \%Y-\%m-\%d \%H:\%M:\%S.
 };
