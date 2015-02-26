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
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		ZarzadcaUzytkownikow() = default;

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ZarzadcaUzytkownikow() = default;

		/**
		* \brief Metoda inicjuj¹ca dane zarz¹dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz¹dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz¹ca œlad stosu.
		* \return Zwracana jest wartoœæ true je¿eli uda siê poprawnie zainicjowaæ obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		bool inicjalizuj(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos);
		
		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj¹ca.
		*
		* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		* \warning Metoda nie modyfikuje wêz³a.
		* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		std::string pobierzHash(const std::string nazwaUzytkownika) const;

		/**
		* \brief Metoda loguj¹ca u¿ytkownika.
		*
		* Metoda s³u¿y do logowania u¿ytkownika. Zostaj¹ za³adowane do pamiêci planety nale¿¹ce do u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return Zwraca wartoœæ true, je¿eli uda siê zalogowaæ, false w przeciwnym przypadku.
		*/
		std::shared_ptr<Uzytkownik> logowanie(Gra& gra, const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda dodaj¹ca nowego u¿ytkownika.
		*
		* Metoda tworzy wêze³ oraz plik z danymi gracza. Sprawdza czy gracz ju¿ istnieje.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return Zwraca wartoœæ true, je¿eli uda siê dodaæ u¿ytkownika, false w przeciwnym przypadku.
		*/
		bool nowyGracz(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda usuwaj¹ca u¿ytkownika.
		*
		* Metoda usuwa plik u¿ytkownika, odpinaj¹æ przypisane do niego planety. Usuwa wszystkie obiektu przypisane do planety.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return true je¿eli uda siê usun¹æ u¿ytkownika, false w przeciwnym przypadku.
		*/
		bool usunGracza(Gra& gra, const std::string& nazwa, const std::string& hash);
				
		bool zapiszGracza(std::shared_ptr<Uzytkownik>);

		bool zapiszDane() const;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;

	private:
		typedef std::map< std::string, std::string > MapaAutoryzacji;

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
		* \version 1
		* \date 25-11-2014
		*/
		std::shared_ptr<SPar::ParserDokument> plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik = true) const;


		std::string folderPlikowUzytkownika_; /// Œcie¿ka do folderu w którym znajduj¹ siê pliki gry.
		std::string plikAutoryzacji_; /// Nazwa pliku autoryzacji u¿ytkowników.

		MapaAutoryzacji autoryzacja_;
		mutable std::mutex mutexAutoryzacja_;

	};
};
