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
	* Konstruktor tworz�cy obiekt na podstawie identyfikatora.
	* \param[in] identyfikator - Identyfikator jaki ma zosta� przypisany do obiektu.
	* \param[in] nazwaPlanety - Nazwa planety jak� reprezentuje sygnatura.
	* \param[in] nazwaGracza - Nazwa gracza posiadaj�cego planet�.
	*/
	explicit SygnaturaPlanety( const Identyfikator& id , const Tekst& nazwaPlanety, const Tekst& nazwaGracza );

	/**
	* \brief Destruktor.
	*/
	virtual ~SygnaturaPlanety();

	/**
	* \brief Metoda pobieraj�ca nazw� planety
	* 
	* Metoda pobiera nazw� planety reprezentowana przez sygnatur�.
	* \return Nazwa planety reprezentowanej przez sygnatur�.
	*/
	Tekst pobierzNazwePlanety()const;
	
	/**
	* \brief Metoda ustawiaj�ca nazw� planety
	*
	* Metoda ustawia nazw� planety reprezentowanej przez sygantur�.
	* \param[in] nazwa - Nowa nazwa planety reprezentowanej przez sygnatur�.
	* \warning Nazwa jest zmieniana tylko lokalnie. Zmiana w tym obiekcie nie wp�ywa na nazw� o obiekcie g��wnym.
	*/
	void ustawNazwePlanety( const Tekst& nazwa );

	/**
	* \brief Metoda pobieraj�ca nazw� gracza
	* 
	* Metoda pobiera nazw� gracza posaidaj�cego reprezentowan� przez sygnatur� planet�.
	* \return Nazwa gracza posaidaj�cego reprezentowan� przez sygnatur� planet�.
	*/
	Tekst pobierzNazweGracza()const;

	/**
	* \brief Metoda ustawiaj�ca nazw� gracza
	*
	* Metoda ustawia nazw� gracza posiadaj�cego reprezentowan� przez sygantur� planet�.
	* \param[in] nazwa - Nowa nazwa gracza posiadaj�cego reprezentowan� przez sygantur� planet�.
	* \warning Nazwa jest zmieniana tylko lokalnie. Zmiana w tym obiekcie nie wp�ywa na nazw� o obiekcie g��wnym.
	*/
	void ustawNazweGracza( const Tekst& nazwa );

	std::shared_ptr<SygnaturaPlanety> pobierzOryginalnyWskaznik() const;

	std::shared_ptr<Planeta> pobierzPlanete() const;

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
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

private:

	Tekst nazwaPlanety_; /// Nazwa planety, kt�ra reprezentuje skr�t.
	Tekst nazwaGracza_; ///Nazwa gracza, do kt�rego nale�y planeta.

};

