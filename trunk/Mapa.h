#pragma once
#include "Main.h"
#include <map>
#include "Logger.h"

/**
* \brief Szablon klasy do przechowywania zbioru obiektów.
*
* Klasa specjalnie zaprojektowana jako dodatkowy interfejs dla mapy obiektów.
* \author Daniel Wojdak
* \version 1
* \date 18-07-2013
*/
template< class Klucz, class Wartosc >
class Mapa:
	virtual public LoggerInterface,
	public map<Klucz,Wartosc* >
{
	static_assert(!is_pointer< Klucz >::value, "Klucz nie moze byc wskaznikiem.");
	static_assert(!is_pointer< Wartosc >::value, "Wartosc nie moze byc wskaznikiem.");
private:
	typedef Mapa<Klucz,Wartosc > TYP;
public:
	typedef map<Klucz,Wartosc* > HashMapa;
	/**
	* \brief Konstruktor.
	*/
	Mapa()
		: map()
	{
	}

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Mapa( const map<Klucz,Wartosc* >& wartosc )
		: map(wartosc)
	{
	}

	/**
	* \brief Destruktor.
	*/
	virtual ~Mapa(){
	}

	/**
	* \brief Metoda dodajaca obiekt.
	* 
	* Metoda dodaje obiekt do kolekcji.
	* \param[in] wartosc - WskaŸnik na dodawany obiekt.
	* \param[in] klucz - Identyfikator dodawanego obiektu.
	*/
	void put( const Klucz& klucz, Wartosc* wartosc){
		this->operator[](klucz)=wartosc;
	}
	/**
	* \brief Metoda pobieraj¹ca wskaŸnik do obiektu.
	* 
	* Metoda pobiera klucz identyfikuj¹cy obiekt.
	* \param[in] klucz - Identyfikator obiektu w kolekcji.
	* \return WskaŸnik do obiektu.
	*/
	Wartosc* get( const Klucz& klucz ) const{
		return this->at(klucz);
	}

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override{
		Logger str(NAZWAKLASY( TYP ));
		str.rozpocznijPodKlase("map");
		for(const_iterator iter=begin(); iter!=end(); ++iter){
			str.dodajPole( "", (*iter).first , *( (*iter).second ) );
		}
		str.zakonczPodKlase();
		return str.napis();
	}
};