#pragma once
#include <mutex>
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"
#include "NonCopyable.h"
#include "NonMoveable.h"
#include "UstawieniaAplikacji.h"
#include "Uzytkownik.h"

namespace SpEx{
	class ZarzadcaUzytkownikow :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja,
		public se::NonMoveable,
		public se::NonCopyable
	{
	public:
		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		ZarzadcaUzytkownikow() = default;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ZarzadcaUzytkownikow() = default;

		/**
		* \brief Metoda inicjuj�ca dane zarz�dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz�dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz�ca �lad stosu.
		* \return Zwracana jest warto�� true je�eli uda si� poprawnie zainicjowa� obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		bool inicjalizuj(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos);
		
		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj�ca.
		*
		* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
		* \warning Metoda nie modyfikuje w�z�a.
		* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		std::string pobierzHash(const std::string nazwaUzytkownika) const;

		/**
		* \brief Metoda loguj�ca u�ytkownika.
		*
		* Metoda s�u�y do logowania u�ytkownika. Zostaj� za�adowane do pami�ci planety nale��ce do u�ytkownika.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return Zwraca warto�� true, je�eli uda si� zalogowa�, false w przeciwnym przypadku.
		*/
		std::shared_ptr<Uzytkownik> logowanie(Gra& gra, const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda dodaj�ca nowego u�ytkownika.
		*
		* Metoda tworzy w�ze� oraz plik z danymi gracza. Sprawdza czy gracz ju� istnieje.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return Zwraca warto�� true, je�eli uda si� doda� u�ytkownika, false w przeciwnym przypadku.
		*/
		bool nowyGracz(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda usuwaj�ca u�ytkownika.
		*
		* Metoda usuwa plik u�ytkownika, odpinaj�� przypisane do niego planety. Usuwa wszystkie obiektu przypisane do planety.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return true je�eli uda si� usun�� u�ytkownika, false w przeciwnym przypadku.
		*/
		bool usunGracza(Gra& gra, const std::string& nazwa, const std::string& hash);
				
		bool zapiszGracza(std::shared_ptr<Uzytkownik>);

		bool zapiszDane() const;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;

	private:
		typedef std::map< std::string, std::string > MapaAutoryzacji;

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
		* \version 1
		* \date 25-11-2014
		*/
		std::shared_ptr<SPar::ParserDokument> plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik = true) const;


		std::string folderPlikowUzytkownika_; /// �cie�ka do folderu w kt�rym znajduj� si� pliki gry.
		std::string plikAutoryzacji_; /// Nazwa pliku autoryzacji u�ytkownik�w.

		MapaAutoryzacji autoryzacja_;
		mutable std::mutex mutexAutoryzacja_;

	};
};
