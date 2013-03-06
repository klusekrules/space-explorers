#pragma once

#include <string>
#include <time.h>
#include <iostream>
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
class Log
{
private:

	/**
	* Funkcja wysy³aj¹ca napis do strumienia.
	* \param p Napis wysy³any do strumienia.
	*/
	static void print( const string p );
	static bool blogEnable; /**< Zmmienna blokuj¹ca wysy³anie wszystkich komunikatów do strumienia */
	static bool blogDebugEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Debug do strumienia */
	static bool blogInfoEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Info do strumienia */
	static bool blogWarnEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Warning do strumienia */
	static bool blogErrorEnable; /**< Zmmienna blokuj¹ca wysy³anie komunikatów typu Error do strumienia */
public:

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
	static bool isLogEnable(){
		return blogEnable;
	}

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
	static bool isLogDebugEnable(){
		return blogEnable ? blogDebugEnable : false;
	}

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
	static bool isLogInfoEnable(){
		return blogEnable ? blogInfoEnable : false;
	}

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
	static bool isLogWarnEnable(){
		return blogEnable ? blogWarnEnable : false;
	}

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
	static bool isLogErrorEnable(){
		return blogEnable ? blogErrorEnable : false;
	}

	/**
	* Odblokowanie wysy³ania logów do strumienia.
	* \sa logDisable()
	* \sa logDebugEnable()
	* \sa logInfoEnable()
	* \sa logWarnEnable()
	* \sa logErrorEnable()
	* \sa isLogEnable()
	*/
	static void logEnable(){
		blogEnable = true;
	}
	
	/**
	* Zablokowanie wysy³ania logów do strumienia.
	* \sa logEnable()
	* \sa logDebugDisable()
	* \sa logInfoDisable()
	* \sa logWarnDisable()
	* \sa logErrorDisable()
	* \sa isLogEnable()
	*/
	static void logDisable(){
		blogEnable = false;
	}

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
	static void logDebugEnable(){
		blogDebugEnable = true;
	}
	
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
	static void logDebugDisable(){
		blogDebugEnable = false;
	}

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
	static void logInfoEnable(){
		blogInfoEnable = true;
	}
	
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
	static void logInfoDisable(){
		blogInfoEnable = false;
	}

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
	static void logWarnEnable(){
		blogWarnEnable = true;
	}
	
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
	static void logWarnDisable(){
		blogWarnEnable = false;
	}

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
	static void logErrorEnable(){
		blogErrorEnable = true;
	}
	
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
	static void logErrorDisable(){
		blogErrorEnable = false;
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa info( LoggerInterface<T> &p )
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	* \sa isLogInfoEnable()
	*/
	static void info( const string p ){
		if(blogEnable && blogInfoEnable){
			print("[Info] ");
			print(p);
			print("\n");
		}
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Info do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa info( string p )
	* \sa logInfoEnable()
	* \sa logInfoDisable()
	* \sa isLogInfoEnable()
	*/
	template< typename T >
	static void info( const LoggerInterface<T> &p ){
		if(blogEnable && blogInfoEnable){
			print("[Info] ");
			print(p.toString());
			print("\n");
		}
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Warning do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa warn( LoggerInterface<T> &p )
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	* \sa isLogWarnEnable()
	*/
	static void warn( const string p ){
		if(blogEnable && blogWarnEnable){
			print("[Warning] ");
			print(p);
			print("\n");
		}
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Warning do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa warn( string p )
	* \sa logWarnEnable()
	* \sa logWarnDisable()
	* \sa isLogWarnEnable()
	*/
	template< typename T >
	static void warn( const LoggerInterface<T> &p ){
		if(blogEnable && blogWarnEnable){
			print("[Warning] ");
			print(p.toString());
			print("\n");
		}
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Error do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa error( LoggerInterface<T> &p )
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	* \sa isLogErrorEnable()
	*/
	static void error( const string p ){
		if(blogEnable && blogErrorEnable){
			print("[Error] ");
			print(p);
			print("\n");
		}
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Error do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa error( string p )
	* \sa logErrorEnable()
	* \sa logErrorDisable()
	* \sa isLogErrorEnable()
	*/
	template< typename T >
	static void error( const LoggerInterface<T> &p ){
		if(blogEnable && blogErrorEnable){
			print("[Error] ");
			print(p.toString());
			print("\n");
		}
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Debug do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa debug( LoggerInterface<T> &p )
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	* \sa isLogDebugEnable()
	*/
	static void debug( const string p ){
		if(blogEnable && blogDebugEnable){
			print("[Debug] ");
			print(p);
			print("\n");
		}
	}

	/**
	* Funkcja wysy³aj¹ca komunikat typu Debug do strumienia.
	* \param p Wiadomoœæ u¿ytkownika wysy³ana do strumienia.
	* \sa debug( string p )
	* \sa logDebugEnable()
	* \sa logDebugDisable()
	* \sa isLogDebugEnable()
	*/
	template< typename T >
	static void debug( const LoggerInterface<T> &p ){
		if(blogEnable && blogDebugEnable){
			print("[Debug] ");
			print(p.toString());
			print("\n");
		}
	}

	static string getTimeStamp(){
		time_t rawtime;
		char buf [30];
		time(&rawtime);
		ctime_s(buf,30,&rawtime);
		return buf;
	}
};
