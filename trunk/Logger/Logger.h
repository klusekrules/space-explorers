// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOGGER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOGGER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once
#include "ExportSymbol.h"
#include <sstream>
#include <stack>

using std::stringstream;
using std::stack;
using std::deque;

LOGGER_EXPIMP_TEMPLATE template class LOGGER_API deque<bool>;
LOGGER_EXPIMP_TEMPLATE template class LOGGER_API stack<bool>;

#include "LoggerInterface.h"


/**
* \brief Klasa pomocnicza w tworzeniu napisu z innej klasy.
*
* Klasa s�u�y do sklejania atrybut�w i klas bazowych. U�atwia tworzenie napis�w klas dziedzicz�cych po LoggerInterface.
*/
class LOGGER_API Logger :
	virtual public LoggerInterface
{
public:

	/**
	* Konstruktor bezparametrowy.
	*/
	Logger();

	/**
	* Konstruktor klasy Logger. Tworzy obiekt z nadan� nazw� klasy g��wnej.
	* \param[in] nazwaKlasy - Nazwa klasy gl�wnej dla kt�rej jest generowany napis.
	*/
	explicit Logger( const string& nazwaKlasy );

	/**
	* Destruktor.
	*/
	virtual ~Logger();

	/**
	* Metoda statyczna tworz�ca napis z obiektu przekazanego jako argument.
	* \param[in] obiekt - Obiekt przekazany do utworzenia napisu.
	* \return Napis z przekazanego obiektu.
	*/
	template< class T >
	static string tworzPole( const T& obiekt ){
		stringstream napis;
		napis << obiekt;
		return napis.str();
	}

	/**
	* Metoda statyczna tworz�ca napis z obiektu przekazanego jako argument.
	* \param[in] nazwa - Nazwa pola. 
	* \param[in] obiekt - Obiekt przekazany do utworzenia napisu.
	* \return Napis z przekazanego obiektu.
	*/
	template< class T >
	static string tworzPole( const string& nazwa, const T& obiekt ){
		stringstream napis;
		napis << obiekt;
		return napis.str();
	}

	/**
	* Metoda statyczna tworz�ca napis z obiekt�w przekazanych jako argumenty.
	* \param[in] nazwa - Nazwa pola. 
	* \param[in] obiektPierwszy - Obiekt przekazany do utworzenia napisu.
	* \param[in] obiektDrugi - Obiekt przekazany do utworzenia napisu.
	* \return Utworzony napis.
	*/
	static string tworzPole( const string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi );

	/**
	* Metoda statyczna tworz�ca napis z obiekt�w przekazanych jako argumenty.
	* \param[in] nazwa - Nazwa klasy. 
	* \param[in] opisKlasy - Opis zawarto�ci klasy.
	* \return Utworzony napis.
	*/
	static string tworzKlase( const string& nazwa, const string& opisKlasy );

	/**
	* Metoda dodaj�ca pole o podanej nazwie i zawarto�ci.
	* \param[in] nazwa - Nazwa pola.
	* \param[in] obiekt - Zawarto�� pola.
	*/
	void dodajPole( const string& nazwa, const LoggerInterface& obiekt );

	/**
	* Metoda dodaj�ca pole o podanej nazwie i zawarto�ci.
	* \param[in] nazwa - Nazwa pola.
	* \param[in] opisPola - Zawarto�� pola.
	*/
	void dodajPole( const string& nazwa, const string& opisPola );

	/**
	* Metoda dodaj�ca pole o podanej nazwie i zawarto�ci.
	* \param[in] nazwa - Nazwa pola.
	* \param[in] obiektPierwszy - Zawarto�� pierwszej cz�ci pola.
	* \param[in] obiektDrugi - Zawarto�� drugiej cz�ci pola.
	*/
	void dodajPole( const string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi );

	/**
	* Metoda dodaj�ca klase.
	* \param[in] opisKlasy - Opis klasy.
	*/
	void dodajKlase( const string& opisKlasy );

	/**
	* Metoda s�u�aca do zbudowania podklasy. Rozpoczyna dodawanie podklasy. Metody mog� by� zag�ebiane jedna w drug�.
	* \param[in] nazwa - Nazwa podklasy.
	*/
	void rozpocznijPodKlase( const string& nazwa );

	/**
	* Metoda s�u�aca do konczenia podklasy. Ko�czy ona ostatnio otwart� podklas�.
	*/
	void zakonczPodKlase();

	/**
	* Funkcja s�u��ca do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;

private:

	/**
	* Metoda sprawdzaj�ca czy pole jest pierwsze. Je�eli nie to dopisuje przecinek to ci�gu znak�w.
	*/
	void testPierwszegoPola( );

	stringstream napis_; /// Strumie� zawieraj�cy tworzony napis.
	stack<bool> stos_; /// Stos zawieraj�cy informacje, kt�re pole jest pierwsze.

};

