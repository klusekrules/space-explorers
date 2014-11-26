#pragma once
#include <sstream>
#include <memory>
#include "LoggerSymbol.h"
#include "LoggerInterface.h"

namespace SLog{
	/**
	* \brief Klasa pomocnicza w tworzeniu napisu z innej klasy.
	*
	* Klasa s³u¿y do sklejania atrybutów i klas bazowych. U³atwia tworzenie napisów klas dziedzicz¹cych po LoggerInterface.
	* \author Daniel Wojdak
	* \version 4
	* \date 18-11-2014
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
		* \param[in] obiekt - Zawartoœæ pola.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajPole(const std::string& nazwa, const std::shared_ptr<const LoggerInterface> obiekt);

		/**
		* Metoda dodaj¹ca pole o podanej nazwie i zawartoœci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] opisPola - Zawartoœæ pola.
		* \author Daniel Wojdak
		* \version 3
		* \date 17-11-2014
		*/
		void dodajPole(const std::string& nazwa, const std::string& typ, const std::string& opisPola);
				
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
		void rozpocznijPodKlase(const std::string& zmienna, const std::string& nazwa);

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
		
		void wstaw(const std::string& nazwa, const std::string& opisPola);

		std::stringstream napis_; /// Strumieñ zawieraj¹cy tworzony napis.
	};
}
