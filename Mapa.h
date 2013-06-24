#pragma once
#include "Main.h"
#include <unordered_map>
#include "Base.h"
#include "Logger.h"

template< class Klucz, class Wartosc, class Hasher>
class Mapa:
	public Base,
	virtual public LoggerInterface,
	public unordered_map<Klucz,Wartosc*, Hasher >
{
	static_assert(!is_pointer< Klucz >::value, "Klucz nie moze byc wskaznikiem.");
	static_assert(!is_pointer< Wartosc >::value, "Wartosc nie moze byc wskaznikiem.");
private:
	typedef Mapa<Klucz,Wartosc, Hasher > TYP;
public:
	typedef unordered_map<Klucz,Wartosc*, Hasher > HashMapa;

	explicit Mapa( const IdType& id )
		: Base(id), unordered_map()
	{
	}

	explicit Mapa( const Base& base )
		: Base(base), unordered_map()
	{
	}

	explicit Mapa( const map<Klucz,Wartosc* >& mapa )
		: Base(), unordered_map(mapa)
	{
	}

	Mapa( const map<Klucz,Wartosc* >& mapa, const IdType& id )
		: Base(id), unordered_map(mapa)
	{
	}

	Mapa( const map<Klucz,Wartosc* >& mapa, const Base& base )
		: Base(base), unordered_map(mapa)
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
		Logger str(CLASSNAME( TYP ));
		str.addClass(Base::toString());
		str.startSubClass("hash_map");
		for(const_iterator iter=begin(); iter!=end(); ++iter){
			str.addField( "", (*iter).first , *( (*iter).second ) );
		}
		str.endSubClass();
		return str.toString();
	}
};