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
*	
* W przysz³oœci zostanie dodana mo¿liwoœæ logowania do konkretnych strumieni.
*/
class LOGGER_API Log
{
private:

	vector< shared_ptr<ostream> > outstream;

	/**
	* Funkcja wysy³aj¹ca napis do strumienia.
	* \param p Napis wysy³any do strumienia.
	*/
	void print( const string& p ) const;

	bool blogEnable; /**< Zmmienna blokuj¹ca wysy³anie wszystkich komunikatów do strumienia */
	bool blogDebugEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Debug do strumienia */
	bool blogInfoEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Info do strumienia */
	bool blogWarnEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Warning do strumienia */
	bool blogErrorEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Error do strumienia */
	string formatCzasu;
	Log();

public:

	enum FormatCzasu{
		Data,
		Czas,
		DataCzas
	};

	void dodajGniazdoWyjsciowe(shared_ptr<ostream> &t);

	void ustawFormatCzasu( FormatCzasu format );

	static Log& getInstance();

	/**
	* Funkcja informuj¹ca czy wysy³anie logów jest odblokowane
	* \return Je¿eli wysy³anie logów jest odblokowane zwraca true, je¿eli nie zwraca false.
	* \sa isLogDebugEnable()
	* \sa isLogInfoEnable()
	* \sa isLogWarnEnable()
	* \sa isLogErrorEnable()
	* \sa logEnable()
	* \sa logDisable()
	*/
	bool isLogEnable()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Debug jest odblokowane
	* \return Je¿eli wysy³anie logów typu Debug jest odblokowane zwraca true, je¿eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogInfoEnable()
	* \sa isLogWarnEnable()
	* \sa isLogErrorEnable()
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	*/
	bool isLogDebugEnable()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Info jest odblokowane
	* \return Je¿eli wysy³anie logów typu Info jest odblokowane zwraca true, je¿eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogDebugEnable()
	* \sa isLogWarnEnable()
	* \sa isLogErrorEnable()
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	*/
	bool isLogInfoEnable()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Warning jest odblokowane
	* \return Je¿eli wysy³anie logów typu Warning jest odblokowane zwraca true, je¿eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogDebugEnable()
	* \sa isLogInfoEnable()
	* \sa isLogErrorEnable()
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	*/
	bool isLogWarnEnable()const;

	/**
	* Funkcja informuj¹ca czy wysy³anie logów typu Error jest odblokowane
	* \return Je¿eli wysy³anie logów typu Error jest odblokowane zwraca true, je¿eli nie zwraca false.
	* \sa isLogEnable()
	* \sa isLogDebugEnable()
	* \sa isLogInfoEnable()
	* \sa isLogWarnEnable()
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	*/
	bool isLogErrorEnable()const;

	/**
	* Odblokowanie wysy³ania logów do strumienia.
	* \sa logDisable()
	* \sa logDebugEnable()
	* \sa logInfoEnable()
	* \sa logWarnEnable()
	* \sa logErrorEnable()
	* \sa isLogEnable()
	*/
	void logEnable();
	
	/**
	* Zablokowanie wysy³ania logów do strumienia.
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa logErrorDisable()
	* \sa isLogEnable()
	*/
	void logDisable();

	/**
	* Odblokowanie wysy³ania logów typu Debug do strumienia.
	* \sa logDebugDisable()
	* \sa logEnable()
	* \sa logInfoEnable()
	* \sa logWarnEnable()
	* \sa logErrorEnable()
	* \sa isLogDebugEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logDebugEnable();
	
	/**
	* Zablokowanie wysy³ania logów typu Debug do strumienia.
	* \sa logDebugEnable()
	* \sa logDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa logErrorDisable()
	* \sa isLogDebugEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logDebugDisable();

	/**
	* Odblokowanie wysy³ania logów typu Info do strumienia.
	* \sa logInfoDisable()
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logWarnEnable()
	* \sa logErrorEnable()
	* \sa isLogInfoEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logInfoEnable();
	
	/**
	* Zablokowanie wysy³ania logów typu Info do strumienia.
	* \sa logInfoEnable()
	* \sa logDisable()
	* \sa logDebugDisable()
	* \sa logWarnDisable()
	* \sa logErrorDisable()
	* \sa isLogInfoEnable()
	* \sa debug( string p )
	* \sa debug( LoggerInterface<T> &p )
	*/
	void logInfoDisable();

	/**
	* Odblokowanie wysy³ania logów typu Warning do strumienia.
	* \sa logWarnDisable()
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logErrorEnable()
	* \sa isLogWarnEnable()
	* \sa warn( string p )
	* \sa warn( LoggerInterface<T> &p )
	*/
	void logWarnEnable();
	
	/**
	* Zablokowanie wysy³ania logów typu Warning do strumienia.
	* \sa logWarnEnable()
	* \sa logDisable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logErrorDisable()
	* \sa isLogWarnEnable()
	* \sa warn( string p )
	* \sa warn( LoggerInterface<T> &p )
	*/
	void logWarnDisable();

	/**
	* Odblokowanie wysy³ania logów typu Error do strumienia.
	* \sa logErrorDisable()
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa isLogErrorEnable()
	* \sa error( string p )
	* \sa error( LoggerInterface<T> &p )
	*/
	void logErrorEnable();
	
	/**
	* Zablokowanie wysy³ania logów typu Error do strumienia.
	* \sa logErrorEnable()
	* \sa logDisable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa isLogErrorEnable()
	* \sa error( string p )
	* \sa error( LoggerInterface<T> &p )
	*/
	void logErrorDisable();

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa info( LoggerInterface<T> &p )
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	* \sa isLogInfoEnable()
	*/
	void info( const string& p );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa info( string p )
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	* \sa isLogInfoEnable()
	*/
	void info( const LoggerInterface& p );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Warning do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa warn( LoggerInterface<T> &p )
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	* \sa isLogWarnEnable()
	*/
	void warn( const string& p );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Warning do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa warn( string p )
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	* \sa isLogWarnEnable()
	*/
	void warn( const LoggerInterface& p );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Error do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa error( LoggerInterface<T> &p )
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	* \sa isLogErrorEnable()
	*/
	void error( const string& p );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Error do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa error( string p )
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	* \sa isLogErrorEnable()
	*/
	void error( const LoggerInterface& p );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Debug do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa debug( LoggerInterface<T> &p )
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	* \sa isLogDebugEnable()
	*/
	void debug( const string& p );

	/**
	* Funkcja wysy³aj¹ca komunikat typu Debug do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa debug( string p )
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	* \sa isLogDebugEnable()
	*/
	void debug( const LoggerInterface& p );

	string getTimeStamp() const;
};
