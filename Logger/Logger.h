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
* Klasa s³u¿y do sklejania atrybutów i klas bazowych. U³atwia tworzenie napisów klas dziedzicz¹cych po LoggerInterface.
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
	* Konstruktor klasy Logger. Tworzy obiekt z nadan¹ nazw¹ klasy g³ównej.
	* \param[in] nazwaKlasy - Nazwa klasy glównej dla której jest generowany napis.
	*/
	explicit Logger( const string& nazwaKlasy );

	/**
	* Destruktor.
	*/
	virtual ~Logger();

	/**
	* Metoda statyczna tworz¹ca napis z obiektu przekazanego jako argument.
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
	* Metoda statyczna tworz¹ca napis z obiektu przekazanego jako argument.
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
	* Metoda statyczna tworz¹ca napis z obiektów przekazanych jako argumenty.
	* \param[in] nazwa - Nazwa pola. 
	* \param[in] obiektPierwszy - Obiekt przekazany do utworzenia napisu.
	* \param[in] obiektDrugi - Obiekt przekazany do utworzenia napisu.
	* \return Utworzony napis.
	*/
	static string tworzPole( const string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi );

	/**
	* Metoda statyczna tworz¹ca napis z obiektów przekazanych jako argumenty.
	* \param[in] nazwa - Nazwa klasy. 
	* \param[in] opisKlasy - Opis zawartoœci klasy.
	* \return Utworzony napis.
	*/
	static string tworzKlase( const string& nazwa, const string& opisKlasy );

	/**
	* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
	* \param[in] nazwa - Nazwa pola.
	* \param[in] obiekt - Zawartoœæ pola.
	*/
	void dodajPole( const string& nazwa, const LoggerInterface& obiekt );

	/**
	* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
	* \param[in] nazwa - Nazwa pola.
	* \param[in] opisPola - Zawartoœæ pola.
	*/
	void dodajPole( const string& nazwa, const string& opisPola );

	/**
	* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
	* \param[in] nazwa - Nazwa pola.
	* \param[in] obiektPierwszy - Zawartoœæ pierwszej czêœci pola.
	* \param[in] obiektDrugi - Zawartoœæ drugiej czêœci pola.
	*/
	void dodajPole( const string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi );

	/**
	* Metoda dodaj¹ca klase.
	* \param[in] opisKlasy - Opis klasy.
	*/
	void dodajKlase( const string& opisKlasy );

	/**
	* Metoda s³u¿aca do zbudowania podklasy. Rozpoczyna dodawanie podklasy. Metody mog¹ byæ zag³ebiane jedna w drug¹.
	* \param[in] nazwa - Nazwa podklasy.
	*/
	void rozpocznijPodKlase( const string& nazwa );

	/**
	* Metoda s³u¿aca do konczenia podklasy. Koñczy ona ostatnio otwart¹ podklasê.
	*/
	void zakonczPodKlase();

	/**
	* Funkcja s³u¿¹ca do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override;

private:

	/**
	* Metoda sprawdzaj¹ca czy pole jest pierwsze. Je¿eli nie to dopisuje przecinek to ci¹gu znaków.
	*/
	void testPierwszegoPola( );

	stringstream napis_; /// Strumieñ zawieraj¹cy tworzony napis.
	stack<bool> stos_; /// Stos zawieraj¹cy informacje, które pole jest pierwsze.

};

