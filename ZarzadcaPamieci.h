#pragma once
#include <memory>
#include <unordered_map>
#include "Galaktyka.h"
#include "GeneratorUkladow.h"
#include <vector>
#include "UstawieniaAplikacji.h"

namespace SpEx{
	/**
	* \brief Klasa zarzadzajaca dokumentami
	*
	* Klasa zarzadza dokumetami xml.
	* \deprecated Klasa do usuni�cia. Fukcjonalno�� zostanie przeniesiona do zarz�dcy zasob�w.
	* \author Daniel Wojdak
	* \version 3
	* \date 25-07-2014
	*/
	class ZarzadcaPamieci
	{
	public:
		
		/**
		* \brief Konstruktor.
		*
		* Bezparametrowy konstruktor obiektu.
		*/
		ZarzadcaPamieci() = default;

		/**
		* \brief Metoda zwraca wezel z opisem stan�w w maszynie stanu.
		*
		* Metoda zwraca w�ze� zawieraj�cy opis stan�w maszyny stan�w.
		* \return Zwracany jest w�ze�, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla pobierzWezelKonfiguracyjnyMaszynyStanow()const;

		/**
		* \brief Metoda zwraca wezel z opisem okien gry.
		*
		* Metoda zwraca w�ze� a opisem okien gry.
		* \return Zwracany jest w�ze�, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla pobierzWezelKonfiguracyjnyOknaGry()const;
		
		/**
		* \brief Metoda tworzy w�ze� gry.
		*
		* Metoda tworzy w�ze� gry do zapisu listy planet, uk�ad�w i galaktyk.
		* \return Zwracany jest w�ze�, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla tworzWezelGry();

		/**
		* \brief Metoda zapisuje w�ze� gry.
		*
		* Metoda zapisuje w�ze� gry.
		* \return Zwracana jest warto�� true, je�eli zapis si� powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		bool zapiszWezelGry();

		/**
		* \brief Metoda otwiera w�ze� gry.
		*
		* Metoda otwiera w�ze� gry z list� planet, uk�ad�w i galaktyk.
		* \return Zwracany jest w�ze�, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla otworzWezelGry();
				
		/**
		* \brief Metoda otwieraj�ca plik u�ytkownika
		*
		* Metoda na podstawie nazwy i hashu has�a u�ytkownika otwiera plik z danymi u�ytkownika.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \param[out] nazwaPliku - Nazwa pliku u�ytkownika.
		* \param[in] tworzPlik - informacje czy ma zosta� utworzony plik je�eli nie istnieje.
		* \return nullptr je�eli hash sie nie zgadza, wska�nik na dokument.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::shared_ptr<SPar::ParserDokument> plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik = true) const;

		/**
		* \brief Metoda inicjuj�ca dane zarz�dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz�dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz�ca �lad stosu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		void zaladujPliki(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos);

		/**
		* \brief Destruktor.
		*
		* Domy�lny destruktor obiektu.
		*/
		virtual ~ZarzadcaPamieci() = default;

	private:

		std::shared_ptr<SPar::ParserDokument> dokumentMaszynyStanow_; /// Dokument z opisem stan�w.
		std::shared_ptr<SPar::ParserDokument> dokumentOknaGry_; /// Dokument z list� okien.
		std::shared_ptr<SPar::ParserDokument> dokumentGry_; /// Dokument z opisem obiekt�w gry.

		std::string folderPlikuUzytkownika_; /// Adres folderu z plikami u�ytkownika.
		std::string adresPlikuGry_; /// Adres pliku z opisem obiekt�w gry.		
	};
}
