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
		Debug, /// Sama data
		Info, /// Sam czas
		Warning, /// Data i Czas
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

	typedef std::function<void(TypLogow,const std::string&)> Strumien;

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
	* Funkcja informuj¹ca czy wysy³anie logów jest odblokowane
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
	void loguj( TypLogow typ, const std::string& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void loguj( TypLogow typ, const LoggerInterface& komunikat );

	/**
	* Funkcja polecaj¹ca aktualn¹ datê i czas.
	* \return Aktualna data i czas.
	* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
	* \sa ustawFormatCzasu()
	*/
	std::string pobierzDateCzas() const;

	/**
	* 
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
		
	std::vector< bool > poziomy_;

	std::string formatCzasu_; /// Format w jakim ma zostaæ wyœiwetlany czas logowania. Domyœlenie: \%Y-\%m-\%d \%H:\%M:\%S.

	/**
	* Konstruktor.
	*/
	Log();

	Log( const Log& );

	Log( Log&& );

	Log& operator=( const Log& );
};
