#pragma once
#include "ExportSymbol.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

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
private:

	vector< shared_ptr<ostream> > outstream; /// Tablica strumieni do których ma zostaæ wysy³any log.

	/**
	* Funkcja wysy³aj¹ca napis do strumienia.
	* \param[in] napis - Napis wysy³any do strumienia.
	*/
	void wyswietl( const string& napis ) const;

	bool logiOdblokowane_; /**< Zmmienna blokuj¹ca wysy³anie wszystkich komunikatów do strumienia */
	bool logiDebugOdblokowane_; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Debug do strumienia */
	bool logiInfoOdblokowane_; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Info do strumienia */
	bool logiWarnOdblokowane_; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Warning do strumienia */
	bool logiErrorOdblokowane_; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Error do strumienia */
	string formatCzasu_; /// Format w jakim ma zostaæ wyœiwetlany czas logowania. Domyœlenie: \%Y-\%m-\%d \%H:\%M:\%S.

	/**
	* Konstruktor.
	*/
	Log();

public:

	/**
	* Enumeracja zawieraj¹ca definicje dostêpnych formatów daty i czasu zwracanych przez funkcjê pobierzDateCzas().
	*/
	enum FormatCzasu{
		Data, /// Sama data
		Czas, /// Sam czas
		DataCzas /// Data i Czas
	};

	/**
	* Metoda dodaj¹ca strumien wyjœciowy do 
	* \param[in] strumien - Strumieñ do wysy³ania danych 
	*/
	void dodajGniazdoWyjsciowe( shared_ptr<ostream>& strumien );

	/**
	* Metoda ustawiaj¹ca fomat w jakim ma byæ wyœwietlana data i czas w logach.
	* \param[in] format - Format wyœwietlanegej daty i czasu.
	*/
	void ustawFormatCzasu( FormatCzasu format );

	/**
	* 
	* \return Instancja obiektu logów.
	*/
	static Log& pobierzInstancje();

	/**
	* Funkcja informuj¹ca czy wysy³anie logów jest odblokowane
	* \return Je¿eli wysy³anie logów jest odblokowane zwraca true, je¿eli nie zwraca false.
	*/
	bool czyLogiOdblokowane()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Debug jest odblokowane
	* \return Je¿eli wysy³anie logów typu Debug jest odblokowane zwraca true, je¿eli nie zwraca false.
	*/
	bool czyLogiDebugOdblokowane()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Info jest odblokowane
	* \return Je¿eli wysy³anie logów typu Info jest odblokowane zwraca true, je¿eli nie zwraca false.
	*/
	bool czyLogiInfoOdblokowane()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Warning jest odblokowane
	* \return Je¿eli wysy³anie logów typu Warning jest odblokowane zwraca true, je¿eli nie zwraca false.
	*/
	bool czyLogiWarnOdblokowane()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Error jest odblokowane
	* \return Je¿eli wysy³anie logów typu Error jest odblokowane zwraca true, je¿eli nie zwraca false.
	*/
	bool czyLogiErrorOdblokowane()const;

	/**
	* Odblokowanie wysy³ania logów do strumienia.
	*/
	void odblokujLogi();

	/**
	* Zablokowanie wysy³ania logów do strumienia.
	*/
	void zablokujLogi();

	/**
	* Odblokowanie wysy³ania logów typu Debug do strumienia.
	*/
	void odblokujLogiDebug();

	/**
	* Zablokowanie wysy³ania logów typu Debug do strumienia.
	*/
	void zablokujLogiDebug();

	/**
	* Odblokowanie wysy³ania logów typu Info do strumienia.
	*/
	void odblokujLogiInfo();

	/**
	* Zablokowanie wysy³ania logów typu Info do strumienia.
	*/
	void zablokujLogiInfo();

	/**
	* Odblokowanie wysy³ania logów typu Warning do strumienia.
	*/
	void odblokujLogiWarn();

	/**
	* Zablokowanie wysy³ania logów typu Warning do strumienia.
	*/
	void zablokujLogiWarn();

	/**
	* Odblokowanie wysy³ania logów typu Error do strumienia.
	*/
	void odblokujLogiError();

	/**
	* Zablokowanie wysy³ania logów typu Error do strumienia.
	*/
	void zablokujLogiError();

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void info( const string& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void info( const LoggerInterface& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Warning do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void warn( const string& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Warning do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void warn( const LoggerInterface& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Error do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void error( const string& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Error do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void error( const LoggerInterface& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Debug do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void debug( const string& komunikat );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Debug do strumienia.
	* \param[in] komunikat - Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	*/
	void debug( const LoggerInterface& komunikat );

	/**
	* Funkcja polecaj¹ca aktualn¹ datê i czas.
	* \return Aktualna data i czas.
	* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
	* \sa ustawFormatCzasu()
	*/
	string pobierzDateCzas() const;
};
