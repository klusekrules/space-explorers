#pragma once
#include "Logger\LoggerInterface.h"
#include "Bazowa.h"
#include "Tekst.h"
#include <memory>

class Planeta;

class SygnaturaPlanety :
	public Bazowa,
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:
	/**
	* Konstruktor
	*/
	SygnaturaPlanety();

	/**
	* Konstruktor tworz¹cy obiekt na podstawie identyfikatora.
	* \param[in] identyfikator - Identyfikator jaki ma zostaæ przypisany do obiektu.
	* \param[in] nazwaPlanety - Nazwa planety jak¹ reprezentuje sygnatura.
	* \param[in] nazwaGracza - Nazwa gracza posiadaj¹cego planetê.
	*/
	explicit SygnaturaPlanety( const Identyfikator& id , const Tekst& nazwaPlanety, const Tekst& nazwaGracza );

	/**
	* \brief Destruktor.
	*/
	virtual ~SygnaturaPlanety();

	/**
	* \brief Metoda pobieraj¹ca nazwê planety
	* 
	* Metoda pobiera nazwê planety reprezentowana przez sygnaturê.
	* \return Nazwa planety reprezentowanej przez sygnaturê.
	*/
	Tekst pobierzNazwePlanety()const;
	
	/**
	* \brief Metoda ustawiaj¹ca nazwê planety
	*
	* Metoda ustawia nazwê planety reprezentowanej przez syganturê.
	* \param[in] nazwa - Nowa nazwa planety reprezentowanej przez sygnaturê.
	* \warning Nazwa jest zmieniana tylko lokalnie. Zmiana w tym obiekcie nie wp³ywa na nazwê o obiekcie g³ównym.
	*/
	void ustawNazwePlanety( const Tekst& nazwa );

	/**
	* \brief Metoda pobieraj¹ca nazwê gracza
	* 
	* Metoda pobiera nazwê gracza posaidaj¹cego reprezentowan¹ przez sygnaturê planetê.
	* \return Nazwa gracza posaidaj¹cego reprezentowan¹ przez sygnaturê planetê.
	*/
	Tekst pobierzNazweGracza()const;

	/**
	* \brief Metoda ustawiaj¹ca nazwê gracza
	*
	* Metoda ustawia nazwê gracza posiadaj¹cego reprezentowan¹ przez syganturê planetê.
	* \param[in] nazwa - Nowa nazwa gracza posiadaj¹cego reprezentowan¹ przez syganturê planetê.
	* \warning Nazwa jest zmieniana tylko lokalnie. Zmiana w tym obiekcie nie wp³ywa na nazwê o obiekcie g³ównym.
	*/
	void ustawNazweGracza( const Tekst& nazwa );

	std::shared_ptr<SygnaturaPlanety> pobierzOryginalnyWskaznik() const;

	std::shared_ptr<Planeta> pobierzPlanete() const;

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

	Tekst nazwaPlanety_; /// Nazwa planety, która reprezentuje skrót.
	Tekst nazwaGracza_; ///Nazwa gracza, do którego nale¿y planeta.

};

