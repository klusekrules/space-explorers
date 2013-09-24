#pragma once
#include "FuncTransf\ZmianaFabryka.h"
#include "SurowceInfo.h"
#include "StatekInfo.h"
#include "TechnologiaInfo.h"
#include "BudynekInfo.h"
#include "ObronaInfo.h"
#include "Uzytkownik.h"
#include <unordered_map>
#include "Licznik.h"

/**
* \brief Klasa reprezentuj�ca gr�.
*
* Klasa przechowuje wszystkie informacje i obiekty do poprawnego dzia�ania gry.
* \author Daniel Wojdak
* \version 1
* \date 26-07-2013
*/
class Gra :
	virtual public Serializacja
{
	friend class Aplikacja;

public:

	/**
	* \brief Destruktor.
	*/
	virtual ~Gra();

	/**
	* \brief Metoda wszytuj�ca dane z pliku.
	* 
	* \param[in] adresPliku - Adres pliku z kt�rego maj� zosta� wczytane dane.
	* \return true je�eli uda si� wczyta� dane, false w przeciwnym wypadku.
	*/
	bool wczytajDane( const string& adresPliku );

	/**
	* \brief Metoda loguj�ca u�ytkownika.
	* 
	* Metoda s�u�y do logowania u�ytkownika.
	* \param[in] nazwa - Nazwa u�ytkownika.
	* \param [in] hash - Hash has�a u�ytkownika.
	* \return true je�eli uda si� zalogowa�, false w przeciwnym przypadku.
	*/
	bool logowanie(const string& nazwa, const string& hash);

	/**
	* \brief Metoda dodaj�ca nowego u�ytkownika.
	* 
	* Metoda s�u�y do dodawania nowego u�ytkownika.
	* \param[in] nazwa - Nazwa u�ytkownika.
	* \param [in] hash - Hash has�a u�ytkownika.
	* \return true je�eli uda si� doda� u�ytkownika, false w przeciwnym przypadku.
	*/
	bool nowyGracz(const string& nazwa, const string& hash);

	/**
	* \brief Metoda usuwaj�ca u�ytkownika.
	* 
	* Metoda s�u�y do usuwania u�ytkownika.
	* \param[in] nazwa - Nazwa u�ytkownika.
	* \param [in] hash - Hash has�a u�ytkownika.
	* \return true je�eli uda si� usun�� u�ytkownika, false w przeciwnym przypadku.
	*/
	bool usunGracza(const string& nazwa, const string& hash);

	/**
	* \brief Metoda pobiera aktualnie zalogowanego u�ytkownika.
	*
	* Metoda s�u�y do pobrania aktualnie zalogowanego u�ytkownika.
	* \return Referencja do zalogowanego u�ytkownika.
	* \throw NieznalezionoObiektu
	*/
	Uzytkownik& pobierzUzytkownika() const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda tworzy planet�.
	*
	* Metoda tworzy planet� i dodaje j� do listy wolnych planet.
	* \return Sprytny wska�nika na obiekt planety.
	* \todo Metoda nie doko�czona. 
	*/
	shared_ptr<Planeta> stworzPlanete();

	/**
	* \brief Metoda przenosi planet� do zalogowane u�ytkownika.
	*
	* Metoda przenosi planet� o podanym identyfikatorze do aktualnie zalogowanego u�ytkownika. Przypisuje jego jako w�a�ciciela. Usuwa planet� z listy wolnych planet.
	* \param[in] identyfikator - identyfikator planety.
	* \return true je�eli uda si� przeni��, false w przeciwnym wypadku.
	*/
	bool przeniesPlaneteDoUzytkownika( const Identyfikator& identyfikator );

	/**
	* \brief Metoda pobiera planet�.
	*
	* Metoda s�u�y do pobierania planety o podanym identyfikatorze.
	* \param[in] identyfikator - identyfikator planety.
	* \return Sprytny wska�nika na obiekt planety lub nullptr je�eli nie znaleziono planety o takim identyfikatorze.
	*/
	shared_ptr<Planeta> pobierzPlanete( const Identyfikator& identyfikator );

	/**
	* \brief Metoda s�u�y do dodawania planety do listy planet.
	*
	* Metoda s�u�y do dodawania planety do listy wszytskich planet. Metoda sprawdza czy planeta posiada w�a�ciciela, je�eli nie to dodaje j� do listy wolnych planet.
	* \param[in] planeta - Sprytny wska�nika na obiekt planety.
	* \return true je�eli uda sie doda� palnet�, false w przeciwnym przypadku.
	*/
	bool dodajPlanete( shared_ptr<Planeta> planeta );

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] identyfikator - Identyfikator obiektu do wybudiwania.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const Identyfikator& identyfikator, const Ilosc& ilosc)const;

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] identyfikator - Identyfikator obiektu do wybudiwania.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const Identyfikator& identyfikator, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie kt�rego ma zosta� zbudowany obiekt.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const ObiektBazowyInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom ) const;

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie kt�rego ma zosta� zbudowany obiekt.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const BudynekInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie kt�rego ma zosta� zbudowany obiekt.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const TechnologiaInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie kt�rego ma zosta� zbudowany obiekt.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const StatekInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie kt�rego ma zosta� zbudowany obiekt.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const SurowceInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s�u��ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj�ca obiekt na planecie.
	* \param[in] planeta - Planeta na kt�rej ma zosta� wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie kt�rego ma zosta� zbudowany obiekt.
	* \param[in] ilosc - Atrybut ilo�ci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const ObronaInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda pobieraj�ca instacj� fabryki zmian.
	*
	* \return Instacja fabryki zmian.
	*/
	ZmianaFabryka& pobierzFabrykeZmian() const;

	/**
	* \brief Metoda pobieraj�ca obiekt opisowy Obrony.
	*
	* Metoda pobiera obiekt opisowy obrony.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
	* \throw NieznalezionoObiektu
	*/
	ObronaInfo& pobierzObrone( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj�ca obiekt opisowy Statku.
	*
	* Metoda pobiera obiekt opisowy statku.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
	* \throw NieznalezionoObiektu
	*/
	StatekInfo& pobierzStatek( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj�ca obiekt opisowy Surowca.
	*
	* Metoda pobiera obiekt opisowy surowca.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
	* \throw NieznalezionoObiektu
	*/
	SurowceInfo& pobierzSurowce( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj�ca obiekt opisowy Technologii.
	*
	* Metoda pobiera obiekt opisowy technologii.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
	* \throw NieznalezionoObiektu
	*/
	TechnologiaInfo& pobierzTechnologia( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj�ca obiekt opisowy Budynku.
	*
	* Metoda pobiera obiekt opisowy budynku.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
	* \throw NieznalezionoObiektu
	*/
	BudynekInfo& pobierzBudynek( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj�ca obiekt opisowy.
	*
	* Metoda pobiera obiekt opisowy.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
	* \throw NieznalezionoObiektu
	*/
	ObiektInfo& pobierzObiekt( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda tworz�ca instancje surowc�w nie przypisan� do planety.
	*
	* Metoda tworzy obiekt surowc�w na podstawie w�z�a xml, nie przypisuje go do �adnej planety.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Sprytny wska�nik do obiektu surowc�w. Wska�nik na nullptr, je�eli wyst�pi� b��d.
	*/
	shared_ptr<Surowce> tworzSurowce( TiXmlElement* wezel )const;

	/**
	* \brief Metoda tworz�ca instancje statk�w nie przypisan� do planety.
	*
	* Metoda tworzy obiekt statku na podstawie w�z�a xml, nie przypisuje go do �adnej planety.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Sprytny wska�nik do obiektu statku. Wska�nik na nullptr, je�eli wyst�pi� b��d.
	*/
	shared_ptr<Statek> tworzStatek( TiXmlElement* wezel )const;

	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;
	
	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych u�ytkownika do pliku xml generowanego z nazwy u�ytkownika.
	* \param[in] nazwa - Nazwa u�ytkownika.
	* \param[in] hash - Hash has�a u�ytkownika.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	*/
	bool zapisz( const string& nazwa, const string& hash ) const;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych uzytkownika.
	* \param[in] nazwa - Nazwa u�ytkownika.
	* \param[in] hash - Hash has�a u�ytkownika.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	*/
	bool odczytaj( const string& nazwa, const string& hash );

private:

	/**
	* \brief Konstruktor.
	*
	* \param[in] aplikacja - instancja aplikacji dla kt�rej jest tworzona gra..
	*/
	Gra( Aplikacja& aplikacja );

	/**
	* \brief Konstrutkor kopiuj�cy.
	*
	* \param[in] gra - Obiekt z kt�rego jest tworzona kopia.
	* \todo Oznaczenie metody jako delete kiedy kompilator b�dzie to wspiera�.
	*/
	Gra( const Gra& gra );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] gra - Obiekt z kt�rego jest tworzona kopia.
	* \todo Oznaczenie metody jako delete kiedy kompilator b�dzie to wspiera�.
	*/
	Gra& operator=( const Gra& gra );

	/**
	* \brief Metoda wczytuj�ca dane surowc�w.
	*
	* Metoda wczytuje z w�z�a xml dane opisowe surowc�w. Tworzy obiekty SurowceInfo oraz dodaje je do listy.
	* \param[in] wezel - W�ze� xml zawieraj�cy dane.
	* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajSurowce(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj�ca dane statk�w.
	*
	* Metoda wczytuje z w�z�a xml dane opisowe statk�w. Tworzy obiekty StatekInfo oraz dodaje je do listy.
	* \param[in] wezel - W�ze� xml zawieraj�cy dane.
	* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajStatki(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj�ca dane technologii.
	*
	* Metoda wczytuje z w�z�a xml dane opisowe technologii. Tworzy obiekty TechnologiaInfo oraz dodaje je do listy.
	* \param[in] wezel - W�ze� xml zawieraj�cy dane.
	* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajTechnologie(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj�ca dane budynk�w.
	*
	* Metoda wczytuje z w�z�a xml dane opisowe budynk�w. Tworzy obiekty BudynekInfo oraz dodaje je do listy.
	* \param[in] wezel - W�ze� xml zawieraj�cy dane.
	* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajBudynki(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj�ca dane obrony.
	*
	* Metoda wczytuje z w�z�a xml dane opisowe budynk�w. Tworzy obiekty ObronaInfo oraz dodaje je do listy.
	* \param[in] wezel - W�ze� xml zawieraj�cy dane.
	* \return true je�eli wszystkie dane zostaj� poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajObrone(TiXmlElement* wezel);

	/**
	* \brief Metoda otwieraj�ca plik u�ytkownika
	*
	* Metoda na podstawie nazwy i hashu has�a u�ytkownika otwiera plik z danymi u�ytkownika. 
	* \param[in] nazwa - Nazwa u�ytkownika.
	* \param[in] hash - Hash has�a u�ytkownika.
	* \return nullptr je�eli hash sie nie zgadza, wska�nik na dokument.
	*/
	shared_ptr<TiXmlDocument> plikUzytkownika(const string& nazwa, const string& hash , bool tworzPlik = true ) const;

	ZmianaFabryka &fabryka_; /// Referencja do obiektu fabryki zmian.
	Aplikacja& aplikacja_; /// Referencja do obiektu aplikacji.
	shared_ptr<Uzytkownik> uzytkownik_; /// Aktualnie zalogowany u�ytkownik.

	unordered_map<Identyfikator, shared_ptr<SurowceInfo>, IdTypeHash > listaSurowcowInfo_; /// Lista obiekt�w opisowych surowc�w.
	unordered_map<Identyfikator, shared_ptr<StatekInfo>, IdTypeHash > listaStatkowInfo_; /// Lista obiekt�w opisowych statku.
	unordered_map<Identyfikator, shared_ptr<ObronaInfo>, IdTypeHash > listaObronaInfo_; /// Lista obiekt�w opisowych obrony.
	unordered_map<Identyfikator, shared_ptr<TechnologiaInfo>, IdTypeHash > listaTechnologiInfo_; /// Lista obiekt�w opisowych  technologii.
	unordered_map<Identyfikator, shared_ptr<BudynekInfo>, IdTypeHash > listaBudynkowInfo_; /// Lista obiekt�w opisowych budynku.
	unordered_map<Identyfikator, shared_ptr<ObiektInfo>, IdTypeHash > listaObiektowInfo_; /// Lista obiekt�w opisowych.
	unordered_map<Identyfikator, shared_ptr<ObiektBazowyInfo>, IdTypeHash > listaObiektowBaseInfo_; /// Lista bazowych obiekt�w opisowych.

	Licznik licznikIdentyfikatorowPlanet_; /// Licznik identyfikator�w planet.
	Uzytkownik::ListaPlanet wolnePlanety_; /// Lista wolnych planet.
	Uzytkownik::ListaPlanet wszystkiePlanety_; /// Lista wszystkich planet.
};
