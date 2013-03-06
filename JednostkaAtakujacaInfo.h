
#pragma once
#include "Main.h"
#include "Obrazenia.h"
#include "Info.h"

class JednostkaAtakujacaInfo :
	public Info,
	public LoggerInterface < JednostkaAtakujacaInfo >
{
public:
	typedef LoggerInterface<JednostkaAtakujacaInfo> LogJednostkaAtakujacaInfo;
	/**
	* Konstruktor domyœlny.
	*/
	JednostkaAtakujacaInfo();
	/**
	* Konstruktor parametryczny.
	* \param oAtak - podstawowny atak obiektu
	* \param oPancerz - podstawowy pancerz obiektu
	* \param oOslona - postawowa oslona obiektu
	*/
	JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona );

	/**
	* Destruktor domyœlny.
	*/
	virtual ~JednostkaAtakujacaInfo();

	/**
	* Metoda zwraca podstawowe obra¿enia zadawane przez obiekt.
	* \return Podstawowe obra¿enia zadawane przez obiekt.
	*/
	const Obrazenia& getAtak() const;	

	/**
	* Metoda ustawia podstawowe obra¿enia zadawane przez obiekt.
	* \param a - Nowe podstawowe obra¿enia obiektu.
	*/
	void setAtak( const Obrazenia& a );
	
	/**
	* Metoda zwraca podstawowe obra¿enia jakie zniszcz¹ obiekt.
	* \return Podstawowe obra¿enia jakie zniszcz¹ obiekt.
	*/
	const Obrazenia& getPancerz() const;	

	/**
	* Metoda ustawia podstawowe obra¿enia jakie zniszcz¹ obiekt.
	* \param p - Nowe podstawowe obra¿enia jakie zniszcz¹ obiekt.
	*/
	void setPancerz( const Obrazenia&  p );
	
	/**
	* Metoda zwraca podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	* \return Podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	*/
	const Obrazenia& getOslona() const;	

	/**
	* Metoda ustawia podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	* \param o - Nowe podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	*/
	void setOslona( const Obrazenia& o );
	
	/**
	* Przeci¹¿ona funkcja generuj¹ca tekstowy opis klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string toString() const override;

private:
	Obrazenia atak; /// Podstawowa wartoœæ ataku obiektu.
	Obrazenia pancerz; /// Podstawowa wartoœæ pancerza obiektu.
	Obrazenia oslona; /// Podstawowa wartoœæ os³ony obiektu.
};

