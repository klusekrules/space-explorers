#pragma once
#include "Main.h"
#include <hash_map>
#include "Base.h"
#include "Logger.h"

template< class Klucz, class Wartosc >
class Mapa:
	public Base,
	public LoggerInterface< Mapa< Klucz, Wartosc > >,
	public hash_map<Klucz,Wartosc* >
{
	static_assert(!is_pointer< Klucz >::value, "Klucz nie moze byc wskaznikiem.");
	static_assert(!is_pointer< Wartosc >::value, "Wartosc nie moze byc wskaznikiem.");
public:
	typedef LoggerInterface< Mapa< Klucz, Wartosc > > LogMapa;
	typedef hash_map<Klucz,Wartosc* > HashMapa;
	
	explicit Mapa( const IdType& id )
		: Base(id), hash_map()
	{
	}

	explicit Mapa( const Base& base )
		: Base(base), hash_map()
	{
	}

	explicit Mapa( const map<Klucz,Wartosc* >& mapa )
		: Base(), hash_map(mapa)
	{
	}

	Mapa( const map<Klucz,Wartosc* >& mapa, const IdType& id )
		: Base(id), hash_map(mapa)
	{
	}

	Mapa( const map<Klucz,Wartosc* >& mapa, const Base& base )
		: Base(base), hash_map(mapa)
	{
	}

	virtual ~Mapa(){
	}

	void put( const Klucz& k, Wartosc* w){
		this->operator[](k)=w;
	}

	Wartosc* get( const Klucz& k ) const{
		return this->at(k);
	}

	string toString() const override{
		Logger str(LogMapa::className());
		str.addClass(Base::toString());
		str.startSubClass("hash_map");
		for(const_iterator iter=begin(); iter!=end(); ++iter){
			str.addField<Klucz,Wartosc>( "", (*iter).first , *( (*iter).second ) );
		}
		str.endSubClass();
		return str.toString();
	}
};