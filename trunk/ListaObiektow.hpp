#pragma once
#include "ObiektBazowy.h"
#include "NieznalezionoObiektu.h"
#include "BladLaczeniaObiektow.h"
#include <map>

using std::map;

/**
* \brief Klasa zarzπdzajπca listπ obiektÛw.
*
* Klasa przechowuje i zarzπdza listπ obiektÛw. Obiekty przechowuje jako sprytne wskaüniki. Automatycznie ≥πczy i dzieli obiekty.
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
	* \brief Konstruktor kopiujπcy.
	* \param[in] lista - Lista obiektÛw, ktÛra zostanie skopiowana do tworzonego obiektu.
	*/
	ListaObiektow( const ListaObiektow& lista ){
		for(auto element : lista ){
			insert(make_pair(element.first,shared_ptr<T>(element.second->kopia())));
		}
	}

	/**
	* \brief Konstruktor przenoszπcy.
	* \param[in] lista - Lista obiektÛw, ktÛra zostanie przeniesiona do tworzonego obiektu.
	*/
	ListaObiektow( ListaObiektow&& lista ){
		for(auto element : lista ){
			insert(make_pair(element.first,element.second));
		}
		lista.wyczysc();
	}
	
	/**
	* \brief Metoda dodajπca obiekt do listy.
	*
	* Metoda s≥uøaca do dodawania obiektÛw do listy. Metoda ≥aczy obiekt z obiektem z listy,
	* jeøeli taki znajdzie lub tworzy kopie obiektu przekazanego i dodaje do listy. Metoda nie modyfikuje obiektu przekazanego przez referencje.
	* \param[in] obiekt - Obiekt, ktÛry ma zostaÊ dodany do biblioteki.
	* \return true jeøeli uda siÍ dodaÊ obiekt. false w przeciwnym wypadku.
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
	* \brief Metoda dodajπca obiekt do listy.
	*
	* Metoda s≥uøaca do dodawania obiektÛw do listy. Metoda ≥aczy obiekt z obiektem z listy,
	* jeøeli taki znajdzie lub dodaje do listy przekazany wskaünik bez tworzenia kopii.
	* \param[in] obiekt - Obiekt, ktÛry ma zostaÊ dodany do biblioteki.
	* \return true jeøeli uda siÍ dodaÊ obiekt. false w przeciwnym wypadku.
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
	* \brief Metoda wyjmujπca obiekt z listy.
	*
	* Metoda usuwa obiekt z listy i zwraca go.
	* \param[in] klucz - Klucz obiektu, ktÛry ma zostaÊ wyjÍty z listy.
	* \return Sprytny wskaünik na obiekt o podanym kluczu.
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
	* \brief Metoda pobierajπca obiekt z listy.
	*
	* Metoda s≥uøaca do pobierania wskaünika na obiekt z listy. Metoda nie usuwa obiektu z listy.
	* \param[in] klucz - Klucz obiektu, ktÛry ma zostaÊ pobrany z listy.
	* \return Sprytny wskaünik na obiekt o podanym kluczu.
	*/
	shared_ptr<T> pobierz ( const Klucz& klucz )const{
		auto element = find(klucz);
		if(element==end())
			return nullptr;
		return element->second;
	}


	/**
	* \brief Metoda przenoszπca listÍ.
	*
	* Metoda przenosi ca≥π listÍ obiektÛw do drugiego kontenera.
	* \param[in] kontener - kontener, z ktÛrego zostanie przeniesiona lista elementÛw.
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
	* \brief Metoda usuwajπca obiekt z listy.
	*
	* Metoda s≥uøaca do usuwania obiektu z listy.
	* \param[in] klucz - Klucz obiektu, ktÛry ma zostaÊ usuniÍty z listy.
	* \return true jeøeli uda siÍ usunπÊ. false jeøeli nie znaleziono obiektu.
	* \remark Metoda jest tranzakcyjna.
	*/
	bool usun ( const Klucz& klucz ){
		auto element = find(klucz);
		if(element==end())
			return false;
		return erase(klucz) > 0;
	}

	/**
	* \brief Metoda pobierajπca rozmiar kontenera.
	*
	* Metoda s≥uøaca do pobierania iloúci elementÛw w kontenerze.
	* \return IloúÊ rÛønych obiektÛw na liúcie.
	*/
	size_t rozmiar()const{
		return size();
	}

	/**
	* \brief Metoda czyszcπca kontener
	*
	* Metoda s≥uøaca do czyszcenia danych w kontenerze.
	*/
	void wyczysc(){
		clear();
	}
	
	/**
	* \brief Metoda pobierajπca listÍ wszystkich obiektÛw w kontenerze.
	*
	* Metoda s≥uøaca do pobierania listy wszystkich obiektÛw znajdujπcych siÍ w kontenerze.
	* Metoda nie tworzy kopii elementÛw.
	* \return Lista obiektÛw kontenera.
	*/
	list< shared_ptr<T> > listaObiektow() const {
		list< shared_ptr<T> > lista;
		for(auto element : *this){
			lista.push_back(element.second);
		}
		return lista;
	}
	
	/**
	* \brief Metoda pobierajπca listÍ wszystkich kluczy obiektÛw w kontenerze.
	*
	* Metoda s≥uøaca do pobierania listy wszystkich kluczy obiektÛw znajdujπcych siÍ w kontenerze.
	* \return Lista kluczy obiektÛw kontenera.
	*/
	list<Klucz> listaKluczy() const {
		list<Klucz> lista;
		for(auto element : *this){
			lista.push_back(element.first);
		}
		return lista;
	}

	/**
	* \brief Metoda informujπca czy zbiornik jest pusty.
	*
	* Metoda s≥uøaca do sprawdzania czy kontener jest pusty.
	* \return true jeøeli kontener jest pusty. false w przeciwnym wypadku.
	*/
	bool pusty() const{
		return empty();
	}

	/**
	* \brief Metoda pobierajπca iterator
	*
	* Metoda s≥uøaca do pobierania iteratora wskazujπcego na pierwszy element.
	* \return Iterator wskazujπcy na pierwszy element.
	*/
	iterator begin(){
		return map< Klucz , shared_ptr<T> >::begin();
	}

	/**
	* \brief Metoda pobierajπca iterator
	*
	* Metoda s≥uøaca do pobierania iteratora wskazujπcego za ostatni element.
	* \return Iterator wskazujπcy za ostatni element.
	*/
	iterator end(){
		return map< Klucz , shared_ptr<T> >::end();
	}

	/**
	* \brief Metoda pobierajπca sta≥y iterator
	*
	* Metoda s≥uøaca do pobierania sta≥ego iteratora wskazujπcego na pierwszy element.
	* \return Sta≥y iterator wskazujπcy na pierwszy element.
	*/
	const_iterator begin() const{
		return map< Klucz , shared_ptr<T> >::cbegin();
	}

	/**
	* \brief Metoda pobierajπca iterator
	*
	* Metoda s≥uøaca do pobierania sta≥ego iteratora wskazujπcego za ostatni element.
	* \return Sta≥y iterator wskazujπcy za ostatni element.
	*/
	const_iterator end() const{
		return map< Klucz , shared_ptr<T> >::cend();
	}
	
	/**
	* Metoda generujπca opis klasy w postaci ciπgu znakÛw.
	* \return Napis zwierajπcy opis klasy.
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
	* \brief Metoda przenoszπca element z jednej listy do drugiej.
	*
	* Metoda przenosi element z listy obiektÛw do drugiego kontenera.
	* \param[in] klucz - Klucz przenoszonego elementu.
	* \param[in,out] zrodlo - èrÛd≥owa lista elementÛw.
	* \param[out] docelowy - Docelowa lista elementÛw.
	* \return true jeøeli uda≥o siÍ przeniúÊ obiekt. false w przeciwnym wypadku.
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
	* \brief Metoda przenoszπca element o podanej iloúci z jednej listy do drugiej.
	*
	* Metoda przenosi element o podanej iloúci z listy obiektÛw do drugiego kontenera.
	* \param[in] klucz - Klucz przenoszonego elementu.
	* \param[in] ilosc - Atrybut iloúci przenoszonego elementu.
	* \param[in,out] zrodlo - èrÛd≥owa lista elementÛw.
	* \param[out] docelowy - Docelowa lista elementÛw.
	* \return true jeøeli uda≥o siÍ przeniúÊ obiekt. false w przeciwnym wypadku.
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
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("Nieoczekiwany wyjatek"),Tekst("Wystapi≥ nieoczekiwany wyjatek, ktÛry zaburzy≥ dzia≥anie aplikacji."));
			else
				return false;
		}
		return true;
	}
};
