#pragma once
#include "ExportSymbol.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

#include "LoggerInterface.h"

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
private:

	vector< shared_ptr<ostream> > outstream; /// Tablica strumieni do kt�rych ma zosta� wysy�any log.

	/**
	* Funkcja wysy�aj�ca napis do strumienia.
	* \param[in] napis - Napis wysy�any do strumienia.
	*/
	void wyswietl( const string& napis ) const;

	bool logiOdblokowane_; /**< Zmmienna blokuj�ca wysy�anie wszystkich komunikat�w do strumienia */
	bool logiDebugOdblokowane_; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Debug do strumienia */
	bool logiInfoOdblokowane_; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Info do strumienia */
	bool logiWarnOdblokowane_; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Warning do strumienia */
	bool logiErrorOdblokowane_; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Error do strumienia */
	string formatCzasu_; /// Format w jakim ma zosta� wy�iwetlany czas logowania. Domy�lenie: \%Y-\%m-\%d \%H:\%M:\%S.

	/**
	* Konstruktor.
	*/
	Log();

public:

	/**
	* Enumeracja zawieraj�ca definicje dost�pnych format�w daty i czasu zwracanych przez funkcj� pobierzDateCzas().
	*/
	enum FormatCzasu{
		Data, /// Sama data
		Czas, /// Sam czas
		DataCzas /// Data i Czas
	};

	/**
	* Metoda dodaj�ca strumien wyj�ciowy do 
	* \param[in] strumien - Strumie� do wysy�ania danych 
	*/
	void dodajGniazdoWyjsciowe( shared_ptr<ostream>& strumien );

	/**
	* Metoda ustawiaj�ca fomat w jakim ma by� wy�wietlana data i czas w logach.
	* \param[in] format - Format wy�wietlanegej daty i czasu.
	*/
	void ustawFormatCzasu( FormatCzasu format );

	/**
	* 
	* \return Instancja obiektu log�w.
	*/
	static Log& pobierzInstancje();

	/**
	* Funkcja informuj�ca czy wysy�anie log�w jest odblokowane
	* \return Je�eli wysy�anie log�w jest odblokowane zwraca true, je�eli nie zwraca false.
	*/
	bool czyLogiOdblokowane()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Debug jest odblokowane
	* \return Je�eli wysy�anie log�w typu Debug jest odblokowane zwraca true, je�eli nie zwraca false.
	*/
	bool czyLogiDebugOdblokowane()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Info jest odblokowane
	* \return Je�eli wysy�anie log�w typu Info jest odblokowane zwraca true, je�eli nie zwraca false.
	*/
	bool czyLogiInfoOdblokowane()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Warning jest odblokowane
	* \return Je�eli wysy�anie log�w typu Warning jest odblokowane zwraca true, je�eli nie zwraca false.
	*/
	bool czyLogiWarnOdblokowane()const;

	/**
	* Funkcja informuj�ca czy wysy�anie log�w typu Error jest odblokowane
	* \return Je�eli wysy�anie log�w typu Error jest odblokowane zwraca true, je�eli nie zwraca false.
	*/
	bool czyLogiErrorOdblokowane()const;

	/**
	* Odblokowanie wysy�ania log�w do strumienia.
	*/
	void odblokujLogi();

	/**
	* Zablokowanie wysy�ania log�w do strumienia.
	*/
	void zablokujLogi();

	/**
	* Odblokowanie wysy�ania log�w typu Debug do strumienia.
	*/
	void odblokujLogiDebug();

	/**
	* Zablokowanie wysy�ania log�w typu Debug do strumienia.
	*/
	void zablokujLogiDebug();

	/**
	* Odblokowanie wysy�ania log�w typu Info do strumienia.
	*/
	void odblokujLogiInfo();

	/**
	* Zablokowanie wysy�ania log�w typu Info do strumienia.
	*/
	void zablokujLogiInfo();

	/**
	* Odblokowanie wysy�ania log�w typu Warning do strumienia.
	*/
	void odblokujLogiWarn();

	/**
	* Zablokowanie wysy�ania log�w typu Warning do strumienia.
	*/
	void zablokujLogiWarn();

	/**
	* Odblokowanie wysy�ania log�w typu Error do strumienia.
	*/
	void odblokujLogiError();

	/**
	* Zablokowanie wysy�ania log�w typu Error do strumienia.
	*/
	void zablokujLogiError();

	/**
	* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void info( const string& komunikat );

	/**
	* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void info( const LoggerInterface& komunikat );

	/**
	* Funkcja wysy�aj�ca komunikat typu Warning do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void warn( const string& komunikat );

	/**
	* Funkcja wysy�aj�ca komunikat typu Warning do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void warn( const LoggerInterface& komunikat );

	/**
	* Funkcja wysy�aj�ca komunikat typu Error do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void error( const string& komunikat );

	/**
	* Funkcja wysy�aj�ca komunikat typu Error do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void error( const LoggerInterface& komunikat );

	/**
	* Funkcja wysy�aj�ca komunikat typu Debug do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void debug( const string& komunikat );

	/**
	* Funkcja wysy�aj�ca komunikat typu Debug do strumienia.
	* \param[in] komunikat - Wiadomo�� u�ytkownika wysy�ana do strumienia.
	*/
	void debug( const LoggerInterface& komunikat );

	/**
	* Funkcja polecaj�ca aktualn� dat� i czas.
	* \return Aktualna data i czas.
	* \warning Format zwracanych danych jest definiowany przez ustawFormatCzasu.
	* \sa ustawFormatCzasu()
	*/
	string pobierzDateCzas() const;
};
