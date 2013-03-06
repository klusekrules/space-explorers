#pragma once

#include <string>
#include <time.h>
#include <iostream>
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
*	
* W przysz�o�ci zostanie dodana mo�liwo�� logowania do konkretnych strumieni.
*/
class Log
{
private:

	/**
	* Funkcja wysy�aj�ca napis do strumienia.
	* \param p Napis wysy�any do strumienia.
	*/
	static void print( const string p );
	static bool blogEnable; /**< Zmmienna blokuj�ca wysy�anie wszystkich komunikat�w do strumienia */
	static bool blogDebugEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Debug do strumienia */
	static bool blogInfoEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Info do strumienia */
	static bool blogWarnEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Warning do strumienia */
	static bool blogErrorEnable; /**< Zmmienna blokuj�ca wysy�anie komunikat�w typu Error do strumienia */
public:

	/**
	* Funkcja informuj�ca czy wysy�anie log�w jest odblokowane
	* \return Je�eli wysy�anie log�w jest odblokowane zwraca true, je�eli nie zwraca false.
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
	* Funkcja informuj�ca czy wysy�anie log�w typu Debug jest odblokowane
	* \return Je�eli wysy�anie log�w typu Debug jest odblokowane zwraca true, je�eli nie zwraca false.
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
	* Funkcja informuj�ca czy wysy�anie log�w typu Info jest odblokowane
	* \return Je�eli wysy�anie log�w typu Info jest odblokowane zwraca true, je�eli nie zwraca false.
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
	* Funkcja informuj�ca czy wysy�anie log�w typu Warning jest odblokowane
	* \return Je�eli wysy�anie log�w typu Warning jest odblokowane zwraca true, je�eli nie zwraca false.
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
	* Funkcja informuj�ca czy wysy�anie log�w typu Error jest odblokowane
	* \return Je�eli wysy�anie log�w typu Error jest odblokowane zwraca true, je�eli nie zwraca false.
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
	* Odblokowanie wysy�ania log�w do strumienia.
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
	* Zablokowanie wysy�ania log�w do strumienia.
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
	* Odblokowanie wysy�ania log�w typu Debug do strumienia.
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
	* Zablokowanie wysy�ania log�w typu Debug do strumienia.
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
	* Odblokowanie wysy�ania log�w typu Info do strumienia.
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
	* Zablokowanie wysy�ania log�w typu Info do strumienia.
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
	* Odblokowanie wysy�ania log�w typu Warning do strumienia.
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
	* Zablokowanie wysy�ania log�w typu Warning do strumienia.
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
	* Odblokowanie wysy�ania log�w typu Error do strumienia.
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
	* Zablokowanie wysy�ania log�w typu Error do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Info do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Warning do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Warning do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Error do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Error do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Debug do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
	* Funkcja wysy�aj�ca komunikat typu Debug do strumienia.
	* \param p Wiadomo�� u�ytkownika wysy�ana do strumienia.
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
