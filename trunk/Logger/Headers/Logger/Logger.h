#pragma once
#include <sstream>
#include <memory>
#include "LoggerSymbol.h"
#include "LoggerInterface.h"

namespace SLog{
	/**
	* \brief Klasa pomocnicza w tworzeniu napisu z innej klasy.
	*
	* Klasa s�u�y do sklejania atrybut�w i klas bazowych. U�atwia tworzenie napis�w klas dziedzicz�cych po LoggerInterface.
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
		* Konstruktor klasy Logger. Tworzy obiekt z nadan� nazw� klasy g��wnej.
		* \param[in] nazwaKlasy - Nazwa klasy gl�wnej dla kt�rej jest generowany napis.
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
		* Metoda dodaj�ca pole o podanej nazwie i zawarto�ci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] obiekt - Zawarto�� pola.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajPole(const std::string& nazwa, const LoggerInterface& obiekt);
		
		/**
		* Metoda dodaj�ca pole o podanej nazwie i zawarto�ci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] obiekt - Zawarto�� pola.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajPole(const std::string& nazwa, const std::shared_ptr<const LoggerInterface> obiekt);

		/**
		* Metoda dodaj�ca pole o podanej nazwie i zawarto�ci.
		* \param[in] nazwa - Nazwa pola.
		* \param[in] opisPola - Zawarto�� pola.
		* \author Daniel Wojdak
		* \version 3
		* \date 17-11-2014
		*/
		void dodajPole(const std::string& nazwa, const std::string& typ, const std::string& opisPola);
				
		/**
		* Metoda dodaj�ca klase.
		* \param[in] opisKlasy - Opis klasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void dodajKlase(const std::string& opisKlasy);

		/**
		* Metoda s�u�aca do zbudowania podklasy. Rozpoczyna dodawanie podklasy. Metody mog� by� zag�ebiane jedna w drug�.
		* \param[in] nazwa - Nazwa podklasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void rozpocznijPodKlase(const std::string& zmienna, const std::string& nazwa);

		/**
		* Metoda s�u�aca do zbudowania podklasy. Rozpoczyna dodawanie podklasy. Metody mog� by� zag�ebiane jedna w drug�.
		* \param[in] nazwa - Nazwa podklasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void rozpocznijPodKlase(const std::string& nazwa);

		/**
		* Metoda s�u�aca do konczenia podklasy. Ko�czy ona ostatnio otwart� podklas�.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		void zakonczPodKlase();

		/**
		* Funkcja s�u��ca do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 2
		* \date 18-06-2014
		*/
		std::string napis() const override;

	private:
		
		void wstaw(const std::string& nazwa, const std::string& opisPola);

		std::stringstream napis_; /// Strumie� zawieraj�cy tworzony napis.
	};
}
