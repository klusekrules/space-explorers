#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"

/**
* \brief Klasa reprezentuj¹ca u¿ytkownika.
*
* Klasa u¿ytkownika przechowuje planety oraz wszystkie potrzebne dane
* \author Daniel Wojdak
* \version 1
* \date 26-07-2013
*/
class Uzytkownik:
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	typedef map<Identyfikator, shared_ptr<Planeta> > ListaPlanet;

	/**
	* \brief Konstruktor.
	*
	* \param[in] gra - instancja gry dla u¿ytkownika..
	*/
	Uzytkownik( Gra& gra );

	/**
	* \brief Destruktor.
	*/
	virtual ~Uzytkownik();

	/**
	* \brief Metoda zwracaj¹ca planetê nale¿¹c¹ do u¿ytkownika.
	*
	* Metoda pobiera planete nale¿¹c¹ do u¿ytkownika. Nie usuwa jej z listy jego planet.
	* \return Referencja do planety u¿ytkownika.
	*/
	Planeta& pobierzPlanete( const Identyfikator& Identyfikator ) const;


	/**
	* \brief Metoda dodaje palanetê do listy planet u¿ytkownika.
	* 
	*  Metoda ustawia w³aœciciela planety na aktualnego u¿ytkownika.
	* \param[in] planeta - Sprytny wskaŸnika na obiekt planety.
	* \return true je¿eli uda siê dodaæ planetê, false je¿eli operacja siê nie powiedzie.
	*/
	bool dodajPlanete( shared_ptr<Planeta> planeta );

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
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;

private:
	ListaPlanet listaPlanet; /// Lista planet u¿ytkownika.
	Gra& instancjaGry; /// Instancja gry do której nale¿y u¿ytkowni.
};
