#pragma once
#include "SurowceInfo.h"
#include "StatekInfo.h"
#include "TechnologiaInfo.h"
#include "BudynekInfo.h"
#include "ObronaInfo.h"
#include "Uzytkownik.h"
#include <unordered_map>
#include "Licznik.h"
#include "GeneratorUkladow.h"
#include "ZarzadcaLokacji.h"
#include "ZarzadcaPamieci.h"
#include "Zmiana\ZmianaFabryka.h"


namespace SpEx {
	/**
	* \brief Klasa reprezentuj�ca gr�.
	*
	* Klasa przechowuje wszystkie informacje i obiekty do poprawnego dzia�ania gry.
	* \author Daniel Wojdak
	* \version 3
	* \date 25-07-2014
	*/
	class Gra :
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* \param[in] logger - instancja loggera.
		* \param[in] zarzadcaLokacji - instancja zarz�dcy lokacji.
		* \param[in] zarzadcaPamieci - instancja zarz�dcy pami�ci.
		* \author Daniel Wojdak
		* \version 2
		* \date 25-07-2014
		*/
		explicit Gra(SLog::Log& logger, ZarzadcaLokacji& zarzadcaLokacji, ZarzadcaPamieci& zarzadcaPamieci);

		/**
		* \brief Destruktor.
		*/
		virtual ~Gra() = default;

		/**
		* \brief Metoda wszytuj�ca dane z pliku.
		*
		* Metoda wczytuje obiekty opisowe.
		* \param[in] root - W�ze� z kt�rego maj� zosta� wczytane dane.
		* \return Zwraca warto�� true, je�eli uda si� wczyta� dane, false w przeciwnym wypadku.
		*/
		bool wczytajDane(std::shared_ptr<SPar::ParserElement> root);

		/**
		* \brief Metoda loguj�ca u�ytkownika.
		*
		* Metoda s�u�y do logowania u�ytkownika. Zostaj� za�adowane do pami�ci planety nale��ce do u�ytkownika.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return Zwraca warto�� true, je�eli uda si� zalogowa�, false w przeciwnym przypadku.
		*/
		bool logowanie(const std::string& nazwa, const std::string& hash);

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
		bool usunGracza(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda pobiera aktualnie zalogowanego u�ytkownika.
		*
		* Metoda s�u�y do pobrania aktualnie zalogowanego u�ytkownika.
		* \return Referencja do zalogowanego u�ytkownika.
		* \throw NieznalezionoObiektu
		*/
		Uzytkownik& pobierzUzytkownika() const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda przenosi planet� do zalogowane u�ytkownika.
		*
		* Metoda przenosi planet� o podanym identyfikatorze do aktualnie zalogowanego u�ytkownika. Przypisuje jego jako w�a�ciciela. Usuwa planet� z listy wolnych planet.
		* \param[in] identyfikator - identyfikator planety.
		* \return true je�eli uda si� przeni��, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda przenosi planet� do zalogowane u�ytkownika.
		*
		* Metoda przenosi pierwsz� woln� planet� do aktualnie zalogowanego u�ytkownika. Przypisuje jego jako w�a�ciciela. Usuwa planet� z listy wolnych planet.
		* \return true je�eli uda si� przeni��, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika();

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy Obrony.
		*
		* Metoda pobiera obiekt opisowy obrony.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		*/
		ObronaInfo& pobierzObrone(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy Statku.
		*
		* Metoda pobiera obiekt opisowy statku.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		*/
		StatekInfo& pobierzStatek(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy Surowca.
		*
		* Metoda pobiera obiekt opisowy surowca.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		*/
		SurowceInfo& pobierzSurowce(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy Technologii.
		*
		* Metoda pobiera obiekt opisowy technologii.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		*/
		TechnologiaInfo& pobierzTechnologia(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy Budynku.
		*
		* Metoda pobiera obiekt opisowy budynku.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		*/
		BudynekInfo& pobierzBudynek(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		*/
		ObiektInfo& pobierzObiekt(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda tworz�ca instancje surowc�w nie przypisan� do planety.
		*
		* Metoda tworzy obiekt surowc�w na podstawie w�z�a xml, nie przypisuje go do �adnej planety.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Sprytny wska�nik do obiektu surowc�w. Wska�nik na nullptr, je�eli wyst�pi� b��d.
		*/
		std::shared_ptr<Surowce> tworzSurowce(XmlBO::ElementWezla wezel)const;

		/**
		* \brief Metoda tworz�ca instancje statk�w nie przypisan� do planety.
		*
		* Metoda tworzy obiekt statku na podstawie w�z�a xml, nie przypisuje go do �adnej planety.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Sprytny wska�nik do obiektu statku. Wska�nik na nullptr, je�eli wyst�pi� b��d.
		*/
		std::shared_ptr<Statek> tworzStatek(XmlBO::ElementWezla wezel)const;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych u�ytkownika do pliku xml generowanego z nazwy u�ytkownika.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		*/
		bool zapisz(const std::string& nazwa, const std::string& hash) const;

		/**
		* \brief Metoda odczytuj�ca.
		*
		* Metoda s�u��ca do odczytu danych uzytkownika.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
		*/
		bool odczytaj(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda zwracaj�ca wska�nik na planet�.
		*
		* Metoda zwraca wska�nik na planet� o wskazanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator planety.
		* \return Wska�nik na planet� je�eli planeta zosta�a znaleziona, nullptr w przeciwnym wypadku.
		*/
		std::shared_ptr<Planeta> pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz�dzancyh przez zarz�dc� pami�ci.
		* \return Liczba galaktyk.
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now� galaktyk�.
		*
		* Metoda generuje now� galaktyk�.
		* \return true je�eli si� powiedzie, false w przeciwnym wypadku.
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Metoda zwraca list� wszystkich obiekt�w opisowych.
		*
		* Metoda zwraca list� wszystkich obiekt�w opisowych.
		* \return Zwraca list� obiekt�w.
		*/
		const std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash >& pobierzObiektyInfo(){
			return listaObiektowInfo_;
		}

		/**
		* \brief Metoda Zwraca list� obiekt�w info spe�niaj�chych wymagania.
		*
		* Metoda zwraca list� obiekt�w info, kt�re spe�niaj� wymagania rozbudowy na planecie podanej w parametrze oraz obiekt jest tego samego typu przezkazanego w parametrze.
		* \param[in] planeta - Planeta, dla kt�rej obliczane s� wymagania.
		* \param[in] typObiektu - Typ obiektu jaki ma by� brany pod uwag�.
		* \param[out] listaIdentyfikatorow - Lista identyfikator�w obiekt�w zwr�conych przez metod�.
		* \return Zwraca list� obiekt�w spe�niaj�cych warunki.
		*/
		const std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash >& pobierzDostepneObiektyInfo(const Planeta& planeta, const STyp::Identyfikator& typObiektu, std::vector<STyp::Identyfikator>& listaIdentyfikatorow);

		/**
		* \brief Metoda sprawdza czy u�ytkownik jest zalogowany.
		*
		* Metoda metoda sprawdzaj�ca czy zalogowano u�ytkownika.
		* \return Zwraca warto�� true je�eli u�ytkownik jest zalogowany, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-06-2014
		*/
		bool czyZalogowano()const{
			return uzytkownik_ != nullptr;
		}

	private:

		/**
		* \brief Metoda wczytuj�ca dane surowc�w.
		*
		* Metoda wczytuje z w�z�a xml dane opisowe surowc�w. Tworzy obiekty SurowceInfo oraz dodaje je do listy.
		* \param[in] wezel - W�ze� xml zawieraj�cy dane.
		* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajSurowce(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj�ca dane statk�w.
		*
		* Metoda wczytuje z w�z�a xml dane opisowe statk�w. Tworzy obiekty StatekInfo oraz dodaje je do listy.
		* \param[in] wezel - W�ze� xml zawieraj�cy dane.
		* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajStatki(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj�ca dane technologii.
		*
		* Metoda wczytuje z w�z�a xml dane opisowe technologii. Tworzy obiekty TechnologiaInfo oraz dodaje je do listy.
		* \param[in] wezel - W�ze� xml zawieraj�cy dane.
		* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajTechnologie(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj�ca dane budynk�w.
		*
		* Metoda wczytuje z w�z�a xml dane opisowe budynk�w. Tworzy obiekty BudynekInfo oraz dodaje je do listy.
		* \param[in] wezel - W�ze� xml zawieraj�cy dane.
		* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajBudynki(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj�ca dane obrony.
		*
		* Metoda wczytuje z w�z�a xml dane opisowe budynk�w. Tworzy obiekty ObronaInfo oraz dodaje je do listy.
		* \param[in] wezel - W�ze� xml zawieraj�cy dane.
		* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajObrone(XmlBO::ElementWezla wezel);

		SLog::Log& logger_; /// Referencja do obiektu loguj�cego.
		ZarzadcaLokacji& zarzadcaLokacji_; /// Referencja do aktualnego obiektu zarz�dcy lokacji.
		ZarzadcaPamieci& zarzadcaPamieci_; /// Referencja do aktualnego obiektu zarz�dcy pami�ci.
		std::shared_ptr<Uzytkownik> uzytkownik_; /// Aktualnie zalogowany u�ytkownik.

		std::unordered_map<STyp::Identyfikator, std::shared_ptr<SurowceInfo>, STyp::IdTypeHash > listaSurowcowInfo_; /// Lista obiekt�w opisowych surowc�w.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<StatekInfo>, STyp::IdTypeHash > listaStatkowInfo_; /// Lista obiekt�w opisowych statku.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObronaInfo>, STyp::IdTypeHash > listaObronaInfo_; /// Lista obiekt�w opisowych obrony.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<TechnologiaInfo>, STyp::IdTypeHash > listaTechnologiInfo_; /// Lista obiekt�w opisowych  technologii.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<BudynekInfo>, STyp::IdTypeHash > listaBudynkowInfo_; /// Lista obiekt�w opisowych budynku.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash > listaObiektowInfo_; /// Lista obiekt�w opisowych.
		
	};
}
