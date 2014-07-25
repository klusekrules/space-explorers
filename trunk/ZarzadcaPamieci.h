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
	* \deprecated Klasa do usuniêcia. Fukcjonalnoœæ zostanie przeniesiona do zarz¹dcy zasobów.
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
		* \brief Metoda zwraca wezel z opisem stanów w maszynie stanu.
		*
		* Metoda zwraca wêze³ zawieraj¹cy opis stanów maszyny stanów.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla pobierzWezelKonfiguracyjnyMaszynyStanow()const;

		/**
		* \brief Metoda zwraca wezel z opisem okien gry.
		*
		* Metoda zwraca wêze³ a opisem okien gry.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla pobierzWezelKonfiguracyjnyOknaGry()const;
		
		/**
		* \brief Metoda tworzy wêze³ gry.
		*
		* Metoda tworzy wêze³ gry do zapisu listy planet, uk³adów i galaktyk.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla tworzWezelGry();

		/**
		* \brief Metoda zapisuje wêze³ gry.
		*
		* Metoda zapisuje wêze³ gry.
		* \return Zwracana jest wartoœæ true, je¿eli zapis siê powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		bool zapiszWezelGry();

		/**
		* \brief Metoda otwiera wêze³ gry.
		*
		* Metoda otwiera wêze³ gry z list¹ planet, uk³adów i galaktyk.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla otworzWezelGry();
				
		/**
		* \brief Metoda otwieraj¹ca plik u¿ytkownika
		*
		* Metoda na podstawie nazwy i hashu has³a u¿ytkownika otwiera plik z danymi u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \param[out] nazwaPliku - Nazwa pliku u¿ytkownika.
		* \param[in] tworzPlik - informacje czy ma zostaæ utworzony plik je¿eli nie istnieje.
		* \return nullptr je¿eli hash sie nie zgadza, wska¿nik na dokument.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::shared_ptr<SPar::ParserDokument> plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik = true) const;

		/**
		* \brief Metoda inicjuj¹ca dane zarz¹dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz¹dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz¹ca œlad stosu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		void zaladujPliki(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos);

		/**
		* \brief Destruktor.
		*
		* Domyœlny destruktor obiektu.
		*/
		virtual ~ZarzadcaPamieci() = default;

	private:

		std::shared_ptr<SPar::ParserDokument> dokumentMaszynyStanow_; /// Dokument z opisem stanów.
		std::shared_ptr<SPar::ParserDokument> dokumentOknaGry_; /// Dokument z list¹ okien.
		std::shared_ptr<SPar::ParserDokument> dokumentGry_; /// Dokument z opisem obiektów gry.

		std::string folderPlikuUzytkownika_; /// Adres folderu z plikami u¿ytkownika.
		std::string adresPlikuGry_; /// Adres pliku z opisem obiektów gry.		
	};
}
