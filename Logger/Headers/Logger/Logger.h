#pragma once
#include <sstream>
#include <memory>
#include <stack>
#include "LoggerSymbol.h"
#include "LoggerInterface.h"

namespace SLog{
	/**
	* \brief Klasa pomocnicza w tworzeniu napisu z innej klasy.
	*
	* Klasa s³u¿y do sklejania atrybutów i klas bazowych. U³atwia tworzenie napisów klas dziedzicz¹cych po LoggerInterface.
	* \author Daniel Wojdak
	* \version 2
	* \date 18-06-2014
	*/
	class LOGGER_API Logger :
		virtual public LoggerInterface
	{
	public:

		/**
		* Konstruktor bezparametrowy.
		*/
		Logger() = default;

		/**
		* Konstruktor klasy Logger. Tworzy obiekt z nadan¹ nazw¹ klasy g³ównej.
		* \param[in] nazwaKlasy - Nazwa klasy glównej dla której jest generowany napis.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		explicit Logger(const std::string& nazwaKlasy);

		/**
		* Destruktor.
		*/
		virtual ~Logger() = default;

		/**
		* Metoda statyczna tworz¹ca napis z obiektu przekazanego jako argument.
		* \param[in] obiekt - Obiekt przekazany do utworzenia napisu.
		* \return Napis z przekazanego obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		template< class T >
		static std::string tworzPole(const T& obiekt){
			std::stringstream napis;
			napis << obiekt;
			return std::move(napis.str());
		}

		/**
		* Metoda statyczna tworz¹ca napis z obiektu przekazanego jako argument.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] obiekt - Obiekt przekazany do utworzenia napisu.
		* \return Napis z przekazanego obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		template< class T >
		static std::string tworzPole(const std::string& nazwa, const T& obiekt){
			std::stringstream napis;
			napis << obiekt;
			return std::move(napis.str());
		}

		/**
		* Metoda statyczna tworz¹ca napis z obiektów przekazanych jako argumenty.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] obiektPierwszy - Obiekt przekazany do utworzenia napisu.
		* \param[in] obiektDrugi - Obiekt przekazany do utworzenia napisu.
		* \return Utworzony napis.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		static std::string tworzPole(const std::string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi);

		/**
		* Metoda statyczna tworz¹ca napis z obiektów przekazanych jako argumenty.
		* \param[in] nazwa - Nazwa klasy.
		* \param[in] opisKlasy - Opis zawartoœci klasy.
		* \return Utworzony napis.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		static std::string tworzKlase(const std::string& nazwa, const std::string& opisKlasy);

		/**
		* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] obiekt - Zawartoœæ pola.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajPole(const std::string& nazwa, const LoggerInterface& obiekt);

		/**
		* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] opisPola - Zawartoœæ pola.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajPole(const std::string& nazwa, const std::string& opisPola);

		/**
		* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] obiektPierwszy - Zawartoœæ pierwszej czêœci pola.
		* \param[in] obiektDrugi - Zawartoœæ drugiej czêœci pola.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajPole(const std::string& nazwa, const LoggerInterface& obiektPierwszy, const LoggerInterface& obiektDrugi);


		/**
		* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] obiekt - Zawartoœæ pola.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajPole(const std::string& nazwa, const std::shared_ptr<LoggerInterface> obiekt);

		/**
		* Metoda dodaj¹ca klase.
		* \param[in] opisKlasy - Opis klasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajKlase(const std::string& opisKlasy);

		/**
		* Metoda s³u¿aca do zbudowania podklasy. Rozpoczyna dodawanie podklasy. Metody mog¹ byæ zag³ebiane jedna w drug¹.
		* \param[in] nazwa - Nazwa podklasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void rozpocznijPodKlase(const std::string& nazwa);

		/**
		* Metoda s³u¿aca do konczenia podklasy. Koñczy ona ostatnio otwart¹ podklasê.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void zakonczPodKlase();

		/**
		* Funkcja s³u¿¹ca do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		std::string napis() const override;

	private:

		/**
		* Metoda sprawdzaj¹ca czy pole jest pierwsze. Je¿eli nie to dopisuje przecinek to ci¹gu znaków.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void testPierwszegoPola();

		std::stringstream napis_; /// Strumieñ zawieraj¹cy tworzony napis.
		std::stack<bool> stos_ = std::move(std::stack<bool>({ true })); /// Stos zawieraj¹cy informacje, które pole jest pierwsze.

	};
}
