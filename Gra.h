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
#include "ZarzadcaPamieci.h"
#include "Zmiana\ZmianaFabryka.h"


namespace SpEx {
	/**
	* \brief Klasa reprezentuj¹ca grê.
	*
	* Klasa przechowuje wszystkie informacje i obiekty do poprawnego dzia³ania gry.
	* \author Daniel Wojdak
	* \version 1
	* \date 26-07-2013
	*/
	class Gra :
		virtual public Serializacja,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* \param[in] aplikacja - instancja aplikacji dla której jest tworzona gra..
		*/
		explicit Gra(SLog::Log& logger, ZarzadcaPamieci& zarzadca);

		/**
		* \brief Destruktor.
		*/
		virtual ~Gra() = default;

		/**
		* \brief Metoda wszytuj¹ca dane z pliku.
		*
		* \param[in] adresPliku - Adres pliku z którego maj¹ zostaæ wczytane dane.
		* \return true je¿eli uda siê wczytaæ dane, false w przeciwnym wypadku.
		*/
		bool wczytajDane(std::shared_ptr<SPar::ParserElement> root);

		/**
		* \brief Metoda loguj¹ca u¿ytkownika.
		*
		* Metoda s³u¿y do logowania u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param [in] hash - Hash has³a u¿ytkownika.
		* \return true je¿eli uda siê zalogowaæ, false w przeciwnym przypadku.
		*/
		bool logowanie(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda dodaj¹ca nowego u¿ytkownika.
		*
		* Metoda s³u¿y do dodawania nowego u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param [in] hash - Hash has³a u¿ytkownika.
		* \return true je¿eli uda siê dodaæ u¿ytkownika, false w przeciwnym przypadku.
		*/
		bool nowyGracz(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda usuwaj¹ca u¿ytkownika.
		*
		* Metoda s³u¿y do usuwania u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param [in] hash - Hash has³a u¿ytkownika.
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
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

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
		* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		* \warning Metoda nie modyfikuje wêz³a.
		* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

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

		std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash > pobierzObiektyInfo(){
			return listaObiektowInfo_;
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

		SLog::Log& logger_;
		ZarzadcaPamieci& zarzadca_;
		std::shared_ptr<Uzytkownik> uzytkownik_; /// Aktualnie zalogowany u¿ytkownik.

		std::unordered_map<STyp::Identyfikator, std::shared_ptr<SurowceInfo>, STyp::IdTypeHash > listaSurowcowInfo_; /// Lista obiektów opisowych surowców.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<StatekInfo>, STyp::IdTypeHash > listaStatkowInfo_; /// Lista obiektów opisowych statku.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObronaInfo>, STyp::IdTypeHash > listaObronaInfo_; /// Lista obiektów opisowych obrony.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<TechnologiaInfo>, STyp::IdTypeHash > listaTechnologiInfo_; /// Lista obiektów opisowych  technologii.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<BudynekInfo>, STyp::IdTypeHash > listaBudynkowInfo_; /// Lista obiektów opisowych budynku.
		std::unordered_map<STyp::Identyfikator, std::shared_ptr<ObiektInfo>, STyp::IdTypeHash > listaObiektowInfo_; /// Lista obiektów opisowych.
		
	};
}
