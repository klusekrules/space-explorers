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
* \brief Klasa reprezentuj¹ca grê.
*
* Klasa przechowuje wszystkie informacje i obiekty do poprawnego dzia³ania gry.
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
	* \brief Metoda wszytuj¹ca dane z pliku.
	* 
	* \param[in] adresPliku - Adres pliku z którego maj¹ zostaæ wczytane dane.
	* \return true je¿eli uda siê wczytaæ dane, false w przeciwnym wypadku.
	*/
	bool wczytajDane( const string& adresPliku );

	/**
	* \brief Metoda loguj¹ca u¿ytkownika.
	* 
	* Metoda s³u¿y do logowania u¿ytkownika.
	* \param[in] nazwa - Nazwa u¿ytkownika.
	* \param [in] hash - Hash has³a u¿ytkownika.
	* \return true je¿eli uda siê zalogowaæ, false w przeciwnym przypadku.
	*/
	bool logowanie(const string& nazwa, const string& hash);

	/**
	* \brief Metoda dodaj¹ca nowego u¿ytkownika.
	* 
	* Metoda s³u¿y do dodawania nowego u¿ytkownika.
	* \param[in] nazwa - Nazwa u¿ytkownika.
	* \param [in] hash - Hash has³a u¿ytkownika.
	* \return true je¿eli uda siê dodaæ u¿ytkownika, false w przeciwnym przypadku.
	*/
	bool nowyGracz(const string& nazwa, const string& hash);

	/**
	* \brief Metoda usuwaj¹ca u¿ytkownika.
	* 
	* Metoda s³u¿y do usuwania u¿ytkownika.
	* \param[in] nazwa - Nazwa u¿ytkownika.
	* \param [in] hash - Hash has³a u¿ytkownika.
	* \return true je¿eli uda siê usun¹æ u¿ytkownika, false w przeciwnym przypadku.
	*/
	bool usunGracza(const string& nazwa, const string& hash);

	/**
	* \brief Metoda pobiera aktualnie zalogowanego u¿ytkownika.
	*
	* Metoda s³u¿y do pobrania aktualnie zalogowanego u¿ytkownika.
	* \return Referencja do zalogowanego u¿ytkownika.
	* \throw NieznalezionoObiektu
	*/
	Uzytkownik& pobierzUzytkownika() const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda tworzy planetê.
	*
	* Metoda tworzy planetê i dodaje j¹ do listy wolnych planet.
	* \return Sprytny wskaŸnika na obiekt planety.
	* \todo Metoda nie dokoñczona. 
	*/
	shared_ptr<Planeta> stworzPlanete();

	/**
	* \brief Metoda przenosi planetê do zalogowane u¿ytkownika.
	*
	* Metoda przenosi planetê o podanym identyfikatorze do aktualnie zalogowanego u¿ytkownika. Przypisuje jego jako w³aœciciela. Usuwa planetê z listy wolnych planet.
	* \param[in] identyfikator - identyfikator planety.
	* \return true je¿eli uda siê przeniœæ, false w przeciwnym wypadku.
	*/
	bool przeniesPlaneteDoUzytkownika( const Identyfikator& identyfikator );

	/**
	* \brief Metoda pobiera planetê.
	*
	* Metoda s³u¿y do pobierania planety o podanym identyfikatorze.
	* \param[in] identyfikator - identyfikator planety.
	* \return Sprytny wskaŸnika na obiekt planety lub nullptr je¿eli nie znaleziono planety o takim identyfikatorze.
	*/
	shared_ptr<Planeta> pobierzPlanete( const Identyfikator& identyfikator );

	/**
	* \brief Metoda s³u¿y do dodawania planety do listy planet.
	*
	* Metoda s³u¿y do dodawania planety do listy wszytskich planet. Metoda sprawdza czy planeta posiada w³aœciciela, je¿eli nie to dodaje j¹ do listy wolnych planet.
	* \param[in] planeta - Sprytny wskaŸnika na obiekt planety.
	* \return true je¿eli uda sie dodaæ palnetê, false w przeciwnym przypadku.
	*/
	bool dodajPlanete( shared_ptr<Planeta> planeta );

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] identyfikator - Identyfikator obiektu do wybudiwania.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const Identyfikator& identyfikator, const Ilosc& ilosc)const;

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] identyfikator - Identyfikator obiektu do wybudiwania.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const Identyfikator& identyfikator, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie którego ma zostaæ zbudowany obiekt.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const ObiektBazowyInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom ) const;

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie którego ma zostaæ zbudowany obiekt.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const BudynekInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie którego ma zostaæ zbudowany obiekt.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const TechnologiaInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie którego ma zostaæ zbudowany obiekt.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const StatekInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie którego ma zostaæ zbudowany obiekt.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const SurowceInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda s³u¿¹ca do wybudownia na planecie obiektu.
	*
	* Metoda buduj¹ca obiekt na planecie.
	* \param[in] planeta - Planeta na której ma zostaæ wybudowany obiekt.
	* \param[in] obiektInfo - Obiekt opisowy na bazie którego ma zostaæ zbudowany obiekt.
	* \param[in] ilosc - Atrybut iloœci tworzonego obiektu.
	* \param[in] poziom - Poziom tworzonego obiektu.
	* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
	*/
	bool wybudujNaPlanecie( Planeta& planeta, const ObronaInfo& obiektInfo, const Ilosc& ilosc, const Poziom& poziom )const;

	/**
	* \brief Metoda pobieraj¹ca instacjê fabryki zmian.
	*
	* \return Instacja fabryki zmian.
	*/
	ZmianaFabryka& pobierzFabrykeZmian() const;

	/**
	* \brief Metoda pobieraj¹ca obiekt opisowy Obrony.
	*
	* Metoda pobiera obiekt opisowy obrony.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
	* \throw NieznalezionoObiektu
	*/
	ObronaInfo& pobierzObrone( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj¹ca obiekt opisowy Statku.
	*
	* Metoda pobiera obiekt opisowy statku.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
	* \throw NieznalezionoObiektu
	*/
	StatekInfo& pobierzStatek( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj¹ca obiekt opisowy Surowca.
	*
	* Metoda pobiera obiekt opisowy surowca.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
	* \throw NieznalezionoObiektu
	*/
	SurowceInfo& pobierzSurowce( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj¹ca obiekt opisowy Technologii.
	*
	* Metoda pobiera obiekt opisowy technologii.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
	* \throw NieznalezionoObiektu
	*/
	TechnologiaInfo& pobierzTechnologia( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj¹ca obiekt opisowy Budynku.
	*
	* Metoda pobiera obiekt opisowy budynku.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
	* \throw NieznalezionoObiektu
	*/
	BudynekInfo& pobierzBudynek( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda pobieraj¹ca obiekt opisowy.
	*
	* Metoda pobiera obiekt opisowy.
	* \param[in] identyfikator - identyfikator obiektu.
	* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
	* \throw NieznalezionoObiektu
	*/
	ObiektInfo& pobierzObiekt( const Identyfikator& identyfikator )const throw (NieznalezionoObiektu);

	/**
	* \brief Metoda tworz¹ca instancje surowców nie przypisan¹ do planety.
	*
	* Metoda tworzy obiekt surowców na podstawie wêz³a xml, nie przypisuje go do ¿adnej planety.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Sprytny wskaŸnik do obiektu surowców. WskaŸnik na nullptr, je¿eli wyst¹pi³ b³¹d.
	*/
	shared_ptr<Surowce> tworzSurowce( TiXmlElement* wezel )const;

	/**
	* \brief Metoda tworz¹ca instancje statków nie przypisan¹ do planety.
	*
	* Metoda tworzy obiekt statku na podstawie wêz³a xml, nie przypisuje go do ¿adnej planety.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Sprytny wskaŸnik do obiektu statku. WskaŸnik na nullptr, je¿eli wyst¹pi³ b³¹d.
	*/
	shared_ptr<Statek> tworzStatek( TiXmlElement* wezel )const;

	/**
	* \brief Metoda zapisuj¹ca.
	*
	* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
	* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
	* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
	*/
	bool zapisz( TiXmlElement* wezel ) const override;
	
	/**
	* \brief Metoda zapisuj¹ca.
	*
	* Metoda s³u¿¹ca do zapisu danych u¿ytkownika do pliku xml generowanego z nazwy u¿ytkownika.
	* \param[in] nazwa - Nazwa u¿ytkownika.
	* \param[in] hash - Hash has³a u¿ytkownika.
	* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
	*/
	bool zapisz( const string& nazwa, const string& hash ) const;

	/**
	* \brief Metoda odczytuj¹ca.
	*
	* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
	* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
	* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
	* \warning Metoda nie modyfikuje wêz³a.
	* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
	*/
	bool odczytaj( TiXmlElement* wezel ) override;

	/**
	* \brief Metoda odczytuj¹ca.
	*
	* Metoda s³u¿¹ca do odczytu danych uzytkownika.
	* \param[in] nazwa - Nazwa u¿ytkownika.
	* \param[in] hash - Hash has³a u¿ytkownika.
	* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
	*/
	bool odczytaj( const string& nazwa, const string& hash );

private:

	/**
	* \brief Konstruktor.
	*
	* \param[in] aplikacja - instancja aplikacji dla której jest tworzona gra..
	*/
	Gra( Aplikacja& aplikacja );

	/**
	* \brief Konstrutkor kopiuj¹cy.
	*
	* \param[in] gra - Obiekt z którego jest tworzona kopia.
	* \todo Oznaczenie metody jako delete kiedy kompilator bêdzie to wspieraæ.
	*/
	Gra( const Gra& gra );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] gra - Obiekt z którego jest tworzona kopia.
	* \todo Oznaczenie metody jako delete kiedy kompilator bêdzie to wspieraæ.
	*/
	Gra& operator=( const Gra& gra );

	/**
	* \brief Metoda wczytuj¹ca dane surowców.
	*
	* Metoda wczytuje z wêz³a xml dane opisowe surowców. Tworzy obiekty SurowceInfo oraz dodaje je do listy.
	* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
	* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajSurowce(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj¹ca dane statków.
	*
	* Metoda wczytuje z wêz³a xml dane opisowe statków. Tworzy obiekty StatekInfo oraz dodaje je do listy.
	* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
	* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajStatki(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj¹ca dane technologii.
	*
	* Metoda wczytuje z wêz³a xml dane opisowe technologii. Tworzy obiekty TechnologiaInfo oraz dodaje je do listy.
	* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
	* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajTechnologie(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj¹ca dane budynków.
	*
	* Metoda wczytuje z wêz³a xml dane opisowe budynków. Tworzy obiekty BudynekInfo oraz dodaje je do listy.
	* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
	* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajBudynki(TiXmlElement* wezel);

	/**
	* \brief Metoda wczytuj¹ca dane obrony.
	*
	* Metoda wczytuje z wêz³a xml dane opisowe budynków. Tworzy obiekty ObronaInfo oraz dodaje je do listy.
	* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
	* \return true je¿eli wszystkie dane zostaj¹ poprawnie wczytane, fasle w przeciwnym wypadku.
	*/
	bool wczytajObrone(TiXmlElement* wezel);

	/**
	* \brief Metoda otwieraj¹ca plik u¿ytkownika
	*
	* Metoda na podstawie nazwy i hashu has³a u¿ytkownika otwiera plik z danymi u¿ytkownika. 
	* \param[in] nazwa - Nazwa u¿ytkownika.
	* \param[in] hash - Hash has³a u¿ytkownika.
	* \return nullptr je¿eli hash sie nie zgadza, wska¿nik na dokument.
	*/
	shared_ptr<TiXmlDocument> plikUzytkownika(const string& nazwa, const string& hash , bool tworzPlik = true ) const;

	ZmianaFabryka &fabryka_; /// Referencja do obiektu fabryki zmian.
	Aplikacja& aplikacja_; /// Referencja do obiektu aplikacji.
	shared_ptr<Uzytkownik> uzytkownik_; /// Aktualnie zalogowany u¿ytkownik.

	unordered_map<Identyfikator, shared_ptr<SurowceInfo>, IdTypeHash > listaSurowcowInfo_; /// Lista obiektów opisowych surowców.
	unordered_map<Identyfikator, shared_ptr<StatekInfo>, IdTypeHash > listaStatkowInfo_; /// Lista obiektów opisowych statku.
	unordered_map<Identyfikator, shared_ptr<ObronaInfo>, IdTypeHash > listaObronaInfo_; /// Lista obiektów opisowych obrony.
	unordered_map<Identyfikator, shared_ptr<TechnologiaInfo>, IdTypeHash > listaTechnologiInfo_; /// Lista obiektów opisowych  technologii.
	unordered_map<Identyfikator, shared_ptr<BudynekInfo>, IdTypeHash > listaBudynkowInfo_; /// Lista obiektów opisowych budynku.
	unordered_map<Identyfikator, shared_ptr<ObiektInfo>, IdTypeHash > listaObiektowInfo_; /// Lista obiektów opisowych.
	unordered_map<Identyfikator, shared_ptr<ObiektBazowyInfo>, IdTypeHash > listaObiektowBaseInfo_; /// Lista bazowych obiektów opisowych.

	Licznik licznikIdentyfikatorowPlanet_; /// Licznik identyfikatorów planet.
	Uzytkownik::ListaPlanet wolnePlanety_; /// Lista wolnych planet.
	Uzytkownik::ListaPlanet wszystkiePlanety_; /// Lista wszystkich planet.
};
