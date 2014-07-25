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
	* \brief Klasa reprezentuj¹ca grê.
	*
	* Klasa przechowuje wszystkie informacje i obiekty do poprawnego dzia³ania gry.
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
		* \param[in] zarzadcaLokacji - instancja zarz¹dcy lokacji.
		* \param[in] zarzadcaPamieci - instancja zarz¹dcy pamiêci.
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
		* \brief Metoda wszytuj¹ca dane z pliku.
		*
		* Metoda wczytuje obiekty opisowe.
		* \param[in] root - Wêze³ z którego maj¹ zostaæ wczytane dane.
		* \return Zwraca wartoœæ true, je¿eli uda siê wczytaæ dane, false w przeciwnym wypadku.
		*/
		bool wczytajDane(std::shared_ptr<SPar::ParserElement> root);

		/**
		* \brief Metoda loguj¹ca u¿ytkownika.
		*
		* Metoda s³u¿y do logowania u¿ytkownika. Zostaj¹ za³adowane do pamiêci planety nale¿¹ce do u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return Zwraca wartoœæ true, je¿eli uda siê zalogowaæ, false w przeciwnym przypadku.
		*/
		bool logowanie(const std::string& nazwa, const std::string& hash);

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
		bool usunGracza(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda pobiera aktualnie zalogowanego u¿ytkownika.
		*
		* Metoda s³u¿y do pobrania aktualnie zalogowanego u¿ytkownika.
		* \return Referencja do zalogowanego u¿ytkownika.
		* \throw NieznalezionoObiektu
		*/
		Uzytkownik& pobierzUzytkownika() const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda przenosi planetê do zalogowane u¿ytkownika.
		*
		* Metoda przenosi planetê o podanym identyfikatorze do aktualnie zalogowanego u¿ytkownika. Przypisuje jego jako w³aœciciela. Usuwa planetê z listy wolnych planet.
		* \param[in] identyfikator - identyfikator planety.
		* \return true je¿eli uda siê przeniœæ, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda przenosi planetê do zalogowane u¿ytkownika.
		*
		* Metoda przenosi pierwsz¹ woln¹ planetê do aktualnie zalogowanego u¿ytkownika. Przypisuje jego jako w³aœciciela. Usuwa planetê z listy wolnych planet.
		* \return true je¿eli uda siê przeniœæ, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika();

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy Obrony.
		*
		* Metoda pobiera obiekt opisowy obrony.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
		* \throw NieznalezionoObiektu
		*/
		ObronaInfo& pobierzObrone(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy Statku.
		*
		* Metoda pobiera obiekt opisowy statku.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
		* \throw NieznalezionoObiektu
		*/
		StatekInfo& pobierzStatek(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy Surowca.
		*
		* Metoda pobiera obiekt opisowy surowca.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
		* \throw NieznalezionoObiektu
		*/
		SurowceInfo& pobierzSurowce(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy Technologii.
		*
		* Metoda pobiera obiekt opisowy technologii.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
		* \throw NieznalezionoObiektu
		*/
		TechnologiaInfo& pobierzTechnologia(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy Budynku.
		*
		* Metoda pobiera obiekt opisowy budynku.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
		* \throw NieznalezionoObiektu
		*/
		BudynekInfo& pobierzBudynek(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
		* \throw NieznalezionoObiektu
		*/
		ObiektInfo& pobierzObiekt(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda tworz¹ca instancje surowców nie przypisan¹ do planety.
		*
		* Metoda tworzy obiekt surowców na podstawie wêz³a xml, nie przypisuje go do ¿adnej planety.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Sprytny wskaŸnik do obiektu surowców. WskaŸnik na nullptr, je¿eli wyst¹pi³ b³¹d.
		*/
		std::shared_ptr<Surowce> tworzSurowce(XmlBO::ElementWezla wezel)const;

		/**
		* \brief Metoda tworz¹ca instancje statków nie przypisan¹ do planety.
		*
		* Metoda tworzy obiekt statku na podstawie wêz³a xml, nie przypisuje go do ¿adnej planety.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Sprytny wskaŸnik do obiektu statku. WskaŸnik na nullptr, je¿eli wyst¹pi³ b³¹d.
		*/
		std::shared_ptr<Statek> tworzStatek(XmlBO::ElementWezla wezel)const;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych u¿ytkownika do pliku xml generowanego z nazwy u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		*/
		bool zapisz(const std::string& nazwa, const std::string& hash) const;

		/**
		* \brief Metoda odczytuj¹ca.
		*
		* Metoda s³u¿¹ca do odczytu danych uzytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		*/
		bool odczytaj(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na planetê o wskazanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator planety.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		*/
		std::shared_ptr<Planeta> pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz¹dzancyh przez zarz¹dcê pamiêci.
		* \return Liczba galaktyk.
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now¹ galaktykê.
		*
		* Metoda generuje now¹ galaktykê.
		* \return true je¿eli siê powiedzie, false w przeciwnym wypadku.
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Metoda zwraca listê wszystkich obiektów opisowych.
		*
		* Metoda zwraca listê wszystkich obiektów opisowych.
		* \return Zwraca listê obiektów.
		*/
		const std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash >& pobierzObiektyInfo(){
			return listaObiektowInfo_;
		}

		/**
		* \brief Metoda Zwraca listê obiektów info spe³niaj¹chych wymagania.
		*
		* Metoda zwraca listê obiektów info, które spe³niaj¹ wymagania rozbudowy na planecie podanej w parametrze oraz obiekt jest tego samego typu przezkazanego w parametrze.
		* \param[in] planeta - Planeta, dla której obliczane s¹ wymagania.
		* \param[in] typObiektu - Typ obiektu jaki ma byæ brany pod uwagê.
		* \param[out] listaIdentyfikatorow - Lista identyfikatorów obiektów zwróconych przez metodê.
		* \return Zwraca listê obiektów spe³niaj¹cych warunki.
		*/
		const std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash >& pobierzDostepneObiektyInfo(const Planeta& planeta, const STyp::Identyfikator& typObiektu, std::vector<STyp::Identyfikator>& listaIdentyfikatorow);

		/**
		* \brief Metoda sprawdza czy u¿ytkownik jest zalogowany.
		*
		* Metoda metoda sprawdzaj¹ca czy zalogowano u¿ytkownika.
		* \return Zwraca wartoœæ true je¿eli u¿ytkownik jest zalogowany, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-06-2014
		*/
		bool czyZalogowano()const{
			return uzytkownik_ != nullptr;
		}

	private:

		/**
		* \brief Metoda wczytuj¹ca dane surowców.
		*
		* Metoda wczytuje z wêz³a xml dane opisowe surowców. Tworzy obiekty SurowceInfo oraz dodaje je do listy.
		* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
		* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajSurowce(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj¹ca dane statków.
		*
		* Metoda wczytuje z wêz³a xml dane opisowe statków. Tworzy obiekty StatekInfo oraz dodaje je do listy.
		* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
		* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajStatki(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj¹ca dane technologii.
		*
		* Metoda wczytuje z wêz³a xml dane opisowe technologii. Tworzy obiekty TechnologiaInfo oraz dodaje je do listy.
		* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
		* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajTechnologie(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj¹ca dane budynków.
		*
		* Metoda wczytuje z wêz³a xml dane opisowe budynków. Tworzy obiekty BudynekInfo oraz dodaje je do listy.
		* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
		* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajBudynki(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda wczytuj¹ca dane obrony.
		*
		* Metoda wczytuje z wêz³a xml dane opisowe budynków. Tworzy obiekty ObronaInfo oraz dodaje je do listy.
		* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
		* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
		*/
		bool wczytajObrone(XmlBO::ElementWezla wezel);

		SLog::Log& logger_; /// Referencja do obiektu loguj¹cego.
		ZarzadcaLokacji& zarzadcaLokacji_; /// Referencja do aktualnego obiektu zarz¹dcy lokacji.
		ZarzadcaPamieci& zarzadcaPamieci_; /// Referencja do aktualnego obiektu zarz¹dcy pamiêci.
		std::shared_ptr<Uzytkownik> uzytkownik_; /// Aktualnie zalogowany u¿ytkownik.

		std::unordered_map<STyp::Identyfikator, std::shared_ptr<SurowceInfo>, STyp::IdTypeHash > listaSurowcowInfo_; /// Lista obiektów opisowych surowców.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<StatekInfo>, STyp::IdTypeHash > listaStatkowInfo_; /// Lista obiektów opisowych statku.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObronaInfo>, STyp::IdTypeHash > listaObronaInfo_; /// Lista obiektów opisowych obrony.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<TechnologiaInfo>, STyp::IdTypeHash > listaTechnologiInfo_; /// Lista obiektów opisowych  technologii.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<BudynekInfo>, STyp::IdTypeHash > listaBudynkowInfo_; /// Lista obiektów opisowych budynku.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash > listaObiektowInfo_; /// Lista obiektów opisowych.
		
	};
}
