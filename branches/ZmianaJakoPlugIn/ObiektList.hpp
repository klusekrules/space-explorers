#pragma once
#include "Klucz.h"
#include "Biblioteki.h"
#include "Obiekt.h"
#include "NieznalezionoObiektu.h"
#include "BladLaczeniaObiektow.h"
#include "Stale.h"
#include "Mapa.h"

template < class T >
class ObiektList:
	virtual public LoggerInterface
{
	static_assert(is_base_of< ObiektBase , T >::value, "Uzyto typ niezgodny z ObiektBase* ");
public:
	typedef typename Mapa< Klucz , T >::iterator iterator;
	typedef typename Mapa< Klucz , T >::const_iterator const_iterator;
	
	ObiektList()
		: lista(IdType(-1))
	{
	}

	~ObiektList(){
		for( auto i : lista){
			delete i.second;
		}
	}

	ObiektList(const ObiektList& a)
		: lista(IdType(-1))
	{
		lista.clear();
		for( auto i : a.lista){
			lista.put(i.first,i.second->Kopia());
		}
	}

	ObiektList& operator=(const ObiektList& a){
		clear();
		for( auto i : a.lista){
			lista.put(i.first,i.second->Kopia());
		}
		return (*this);
	}

	//Metoda tworzy kopiê obiektu.
	Klucz add( const T& o ) throw( BladLaczeniaObiektow ){
		Klucz k = o.ID();
		if( lista.find(k) == lista.end() ){
			lista.put(k,o.Kopia());
		}else{
			if(!lista.get(k)->Polacz(o))
				throw BladLaczeniaObiektow( EXCEPTION_PLACE , lista.get(k)->toString(), o.toString() );
		}
		return k;
	}

	//Metoda nie tworzy kopi obiektu, je¿eli po³¹czy oba obiekty usuwa obiekt przekazany przez parametr
	Klucz add( T* o ) throw( BladLaczeniaObiektow ){
		Klucz k = o->ID();
		if( lista.find(k) == lista.end() ){
			lista.put(k,o);
		}else{
			if(!lista.get(k)->Polacz(*o))
				throw BladLaczeniaObiektow( EXCEPTION_PLACE , lista.get(k)->toString(), o->toString() );
			else
				delete o;
		}
		return k;
	}

	//Nie usuwa obiektu z mapy
	T& get ( const Klucz& k ) const throw( NieznalezionoObiektu ){
		if(lista.find(k)==lista.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, k.toString());
		return *lista.get(k);
	}

	//Usuwa obiekt z mapy ale nie wywo³uje metody delete
	T* getAndDel ( const Klucz& k ) throw( NieznalezionoObiektu ){
		if(lista.find(k)==lista.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, k.toString());
		T* o = lista.get(k);
		lista.erase(k);
		return o;
	}
	
	/*T find(){
		auto i = lista.find(k);
		if( i != lista.end() ){			
			return *i;
		}
		return T();
	}*/

	//Usuniecie obiektu z listy i wywo³anie metody delete
	bool del( const Klucz& k ){
		auto iter = lista.find(k);
		if( iter != lista.end() ){
			T* tmp = iter->second;
			lista.erase(k);
			delete tmp;
			return true;
		}
		return false;
	}

	string toString() const override{
		Logger str(CLASSNAME(ObiektList<T>));
		str.addField("Lista Obiektow",lista);
		return str.toString();
	}
	list<T*> rawObiektList() const {
		list<T*> l;
		for(auto i : lista){
			l.push_back(i.second);
		}
		return l;
	}
	
	list<Klucz> rawKluczList() const {
		list<Klucz> l;
		for(auto i : lista){
			l.push_back(i.first);
		}
		return l;
	}

	bool isEmpty(){
		return lista.empty();
	}

	iterator begin(){
		return  lista.begin();
	}

	iterator end(){
		return  lista.end();
	}

	const_iterator begin() const{
		return  lista.cbegin();
	}

	const_iterator end() const{
		return  lista.cend();
	}

	void moveAll( ObiektList<T>& s ){
		for(auto k : s.rawKluczList()){
			add(s.getAndDel(k));
		}
	}
	
	template < class N >
	static bool move( const Klucz& k , ObiektList<N> & z , ObiektList<N>& d ){
		try{
			N* o = z.getAndDel(k);
			try{
				d.add(o);
			}catch(...){
				z.add(o);
				throw;
			}
		}catch( OgolnyWyjatek& e ){
			Aplikacja::getInstance().getLog().warn(e.generujKomunikat());
			return false;
		}
		return true;
	}

	template < class N >
	static bool move( const Klucz& k ,const Ilosc& i, ObiektList<N> & z , ObiektList<N>& d ){
		try{
			N& o = z.get(k);
			N* p = o.Podziel(i);
			if (p == nullptr){
				return false;
			}
			try{
				d.add(p);								
			}catch(...){
				z.add(p);
				throw;
			}
		}catch( OgolnyWyjatek e ){
			Aplikacja::getInstance().getLog().warn(e.generujKomunikat());
			return false;
		}
		return true;
	}

	void clear(){
		for( auto i : lista){
			delete i.second;
		}
		lista.clear();
	}

	size_t size(){
		return lista.size();
	}

private:
	Mapa< Klucz , T > lista;
};
