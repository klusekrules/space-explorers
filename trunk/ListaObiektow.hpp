#pragma once
#include "ObiektBazowy.h"
#include "NieznalezionoObiektu.h"
#include "BladLaczeniaObiektow.h"
#include <map>

using std::map;

/**
* \brief Klasa zarz�dzaj�ca list� obiekt�w.
*
* Klasa przechowuje i zarz�dza list� obiekt�w. Obiekty przechowuje jako sprytne wska�niki. Automatycznie ��czy i dzieli obiekty.
* \author Daniel Wojdak
* \version 1
* \date 23-07-2013
*/
template < class T >
class ListaObiektow:
	private map< Klucz , shared_ptr<T> >,
	virtual public LoggerInterface
{
	static_assert(!is_pointer< T >::value, "Wartosc nie moze byc wskaznikiem.");
	static_assert(is_base_of< ObiektBazowy , T >::value, "Uzyto typ niezgodny z ObiektBazowy");

public:	
	typedef typename map< Klucz , shared_ptr<T> >::iterator iterator;
	typedef typename map< Klucz , shared_ptr<T> >::const_iterator const_iterator;

	/**
	* \brief Konstruktor.
	*/
	ListaObiektow(){
	}

	/**
	* \brief Destruktor.
	*/
	virtual ~ListaObiektow(){
	}

	/**
	* \brief Konstruktor kopiuj�cy.
	* \param[in] lista - Lista obiekt�w, kt�ra zostanie skopiowana do tworzonego obiektu.
	*/
	ListaObiektow( const ListaObiektow& lista ){
		for(auto element : lista ){
			insert(make_pair(element.first,shared_ptr<T>(element.second->kopia())));
		}
	}

	/**
	* \brief Konstruktor przenosz�cy.
	* \param[in] lista - Lista obiekt�w, kt�ra zostanie przeniesiona do tworzonego obiektu.
	*/
	ListaObiektow( ListaObiektow&& lista ){
		for(auto element : lista ){
			insert(make_pair(element.first,element.second));
		}
		lista.wyczysc();
	}
	
	/**
	* \brief Metoda dodaj�ca obiekt do listy.
	*
	* Metoda s�u�aca do dodawania obiekt�w do listy. Metoda �aczy obiekt z obiektem z listy,
	* je�eli taki znajdzie lub tworzy kopie obiektu przekazanego i dodaje do listy. Metoda nie modyfikuje obiektu przekazanego przez referencje.
	* \param[in] obiekt - Obiekt, kt�ry ma zosta� dodany do biblioteki.
	* \return true je�eli uda si� doda� obiekt. false w przeciwnym wypadku.
	* \remark Metoda jest tranzakcyjna.
	*/
	bool dodaj( const T& obiekt ){
		Klucz klucz = obiekt.ID();
		auto element = find(klucz);
		if( element == end() ){
			insert(make_pair(klucz,shared_ptr<T>(obiekt.kopia())));
		}else{
			return element->second->polacz(obiekt);
		}
		return true;
	}

	/**
	* \brief Metoda dodaj�ca obiekt do listy.
	*
	* Metoda s�u�aca do dodawania obiekt�w do listy. Metoda �aczy obiekt z obiektem z listy,
	* je�eli taki znajdzie lub dodaje do listy przekazany wska�nik bez tworzenia kopii.
	* \param[in] obiekt - Obiekt, kt�ry ma zosta� dodany do biblioteki.
	* \return true je�eli uda si� doda� obiekt. false w przeciwnym wypadku.
	* \remark Metoda jest tranzakcyjna.
	*/
	bool dodaj( shared_ptr<T> obiekt ){
		Klucz klucz = obiekt->ID();
		auto element = find(klucz);
		if( element == end() ){
			insert(make_pair(klucz,obiekt));
		}else{
			return element->second->polacz(*obiekt);
		}
		return true;
	}

	/**
	* \brief Metoda wyjmuj�ca obiekt z listy.
	*
	* Metoda usuwa obiekt z listy i zwraca go.
	* \param[in] klucz - Klucz obiektu, kt�ry ma zosta� wyj�ty z listy.
	* \return Sprytny wska�nik na obiekt o podanym kluczu.
	* \remark Metoda jest tranzakcyjna.
	*/
	shared_ptr<T> wyjmij ( const Klucz& klucz ){
		auto element = find(klucz);
		if(element==end())
			return nullptr;
		shared_ptr<T> obiekt = element->second;
		erase(klucz);
		return obiekt;
	}

	/**
	* \brief Metoda pobieraj�ca obiekt z listy.
	*
	* Metoda s�u�aca do pobierania wska�nika na obiekt z listy. Metoda nie usuwa obiektu z listy.
	* \param[in] klucz - Klucz obiektu, kt�ry ma zosta� pobrany z listy.
	* \return Sprytny wska�nik na obiekt o podanym kluczu.
	*/
	shared_ptr<T> pobierz ( const Klucz& klucz )const{
		auto element = find(klucz);
		if(element==end())
			return nullptr;
		return element->second;
	}


	/**
	* \brief Metoda przenosz�ca list�.
	*
	* Metoda przenosi ca�� list� obiekt�w do drugiego kontenera.
	* \param[in] kontener - kontener, z kt�rego zostanie przeniesiona lista element�w.
	* \remark Metoda jest tranzakcyjna.
	*/
	bool przeniesWszystkie( ListaObiektow<T>& kontener ){
		if(kontener.empty())
			return true;

		ListaObiektow<T> tmp(*this);
		for(auto element : kontener){
			if(!tmp.dodaj(element.second))
				return false;
		}
		wyczysc();
		kontener.wyczysc();
		operator=(tmp);
		return true;
	}

	/**
	* \brief Metoda usuwaj�ca obiekt z listy.
	*
	* Metoda s�u�aca do usuwania obiektu z listy.
	* \param[in] klucz - Klucz obiektu, kt�ry ma zosta� usuni�ty z listy.
	* \return true je�eli uda si� usun��. false je�eli nie znaleziono obiektu.
	* \remark Metoda jest tranzakcyjna.
	*/
	bool usun ( const Klucz& klucz ){
		auto element = find(klucz);
		if(element==end())
			return false;
		return erase(klucz) > 0;
	}

	/**
	* \brief Metoda pobieraj�ca rozmiar kontenera.
	*
	* Metoda s�u�aca do pobierania ilo�ci element�w w kontenerze.
	* \return Ilo�� r�nych obiekt�w na li�cie.
	*/
	size_t rozmiar()const{
		return size();
	}

	/**
	* \brief Metoda czyszc�ca kontener
	*
	* Metoda s�u�aca do czyszcenia danych w kontenerze.
	*/
	void wyczysc(){
		clear();
	}
	
	/**
	* \brief Metoda pobieraj�ca list� wszystkich obiekt�w w kontenerze.
	*
	* Metoda s�u�aca do pobierania listy wszystkich obiekt�w znajduj�cych si� w kontenerze.
	* Metoda nie tworzy kopii element�w.
	* \return Lista obiekt�w kontenera.
	*/
	list< shared_ptr<T> > listaObiektow() const {
		list< shared_ptr<T> > lista;
		for(auto element : *this){
			lista.push_back(element.second);
		}
		return lista;
	}
	
	/**
	* \brief Metoda pobieraj�ca list� wszystkich kluczy obiekt�w w kontenerze.
	*
	* Metoda s�u�aca do pobierania listy wszystkich kluczy obiekt�w znajduj�cych si� w kontenerze.
	* \return Lista kluczy obiekt�w kontenera.
	*/
	list<Klucz> listaKluczy() const {
		list<Klucz> lista;
		for(auto element : *this){
			lista.push_back(element.first);
		}
		return lista;
	}

	/**
	* \brief Metoda informuj�ca czy zbiornik jest pusty.
	*
	* Metoda s�u�aca do sprawdzania czy kontener jest pusty.
	* \return true je�eli kontener jest pusty. false w przeciwnym wypadku.
	*/
	bool pusty() const{
		return empty();
	}

	/**
	* \brief Metoda pobieraj�ca iterator
	*
	* Metoda s�u�aca do pobierania iteratora wskazuj�cego na pierwszy element.
	* \return Iterator wskazuj�cy na pierwszy element.
	*/
	iterator begin(){
		return map< Klucz , shared_ptr<T> >::begin();
	}

	/**
	* \brief Metoda pobieraj�ca iterator
	*
	* Metoda s�u�aca do pobierania iteratora wskazuj�cego za ostatni element.
	* \return Iterator wskazuj�cy za ostatni element.
	*/
	iterator end(){
		return map< Klucz , shared_ptr<T> >::end();
	}

	/**
	* \brief Metoda pobieraj�ca sta�y iterator
	*
	* Metoda s�u�aca do pobierania sta�ego iteratora wskazuj�cego na pierwszy element.
	* \return Sta�y iterator wskazuj�cy na pierwszy element.
	*/
	const_iterator begin() const{
		return map< Klucz , shared_ptr<T> >::cbegin();
	}

	/**
	* \brief Metoda pobieraj�ca iterator
	*
	* Metoda s�u�aca do pobierania sta�ego iteratora wskazuj�cego za ostatni element.
	* \return Sta�y iterator wskazuj�cy za ostatni element.
	*/
	const_iterator end() const{
		return map< Klucz , shared_ptr<T> >::cend();
	}
	
	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override{
		Logger str(NAZWAKLASY(ListaObiektow<T>));
		str.rozpocznijPodKlase("map");
		for(auto element : *this){
			str.dodajPole( "", element.first , *( element.second ) );
		}
		str.zakonczPodKlase();
		return str.napis();
	}

	/**
	* \brief Metoda przenosz�ca element z jednej listy do drugiej.
	*
	* Metoda przenosi element z listy obiekt�w do drugiego kontenera.
	* \param[in] klucz - Klucz przenoszonego elementu.
	* \param[in,out] zrodlo - �r�d�owa lista element�w.
	* \param[out] docelowy - Docelowa lista element�w.
	* \return true je�eli uda�o si� przeni�� obiekt. false w przeciwnym wypadku.
	* \remark Metoda jest tranzakcyjna.
	*/
	template < class N >
	static bool przenies( const Klucz& klucz , ListaObiektow<N> & zrodlowa , ListaObiektow<N>& docelowa ){
		shared_ptr<N> obiekt = zrodlowa.pobierz(klucz);
		if(obiekt)
			if(docelowa.dodaj(obiekt))
				zrodlowa.usun(klucz);
			else
				return false;
		else
			return false;		
		return true;
	}

	/**
	* \brief Metoda przenosz�ca element o podanej ilo�ci z jednej listy do drugiej.
	*
	* Metoda przenosi element o podanej ilo�ci z listy obiekt�w do drugiego kontenera.
	* \param[in] klucz - Klucz przenoszonego elementu.
	* \param[in] ilosc - Atrybut ilo�ci przenoszonego elementu.
	* \param[in,out] zrodlo - �r�d�owa lista element�w.
	* \param[out] docelowy - Docelowa lista element�w.
	* \return true je�eli uda�o si� przeni�� obiekt. false w przeciwnym wypadku.
	* \throws BladDzieleniaLadowni, OgolnyWyjatek
	* \remark Metoda jest tranzakcyjna.
	*/
	template < class N >
	static bool przenies( const Klucz& klucz ,const Ilosc& ilosc, ListaObiektow<N> & zrodlowa , ListaObiektow<N>& docelowa ){
		shared_ptr<N> obiekt = zrodlowa.pobierz(klucz);
		shared_ptr<N> obiektPodzielony = shared_ptr<N>(obiekt->podziel(ilosc));
		if (obiekt == nullptr){
			return false;
		}
		if(!docelowa.dodaj(obiekt)){
			if(!zrodlowa.dodaj(obiekt))
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("Nieoczekiwany wyjatek"),Tekst("Wystapi� nieoczekiwany wyjatek, kt�ry zaburzy� dzia�anie aplikacji."));
			else
				return false;
		}
		return true;
	}
};
