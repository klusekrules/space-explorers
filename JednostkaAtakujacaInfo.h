
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
	* Konstruktor domy�lny.
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
	* Destruktor domy�lny.
	*/
	virtual ~JednostkaAtakujacaInfo();

	/**
	* Metoda zwraca podstawowe obra�enia zadawane przez obiekt.
	* \return Podstawowe obra�enia zadawane przez obiekt.
	*/
	const Obrazenia& getAtak() const;	

	/**
	* Metoda ustawia podstawowe obra�enia zadawane przez obiekt.
	* \param a - Nowe podstawowe obra�enia obiektu.
	*/
	void setAtak( const Obrazenia& a );
	
	/**
	* Metoda zwraca podstawowe obra�enia jakie zniszcz� obiekt.
	* \return Podstawowe obra�enia jakie zniszcz� obiekt.
	*/
	const Obrazenia& getPancerz() const;	

	/**
	* Metoda ustawia podstawowe obra�enia jakie zniszcz� obiekt.
	* \param p - Nowe podstawowe obra�enia jakie zniszcz� obiekt.
	*/
	void setPancerz( const Obrazenia&  p );
	
	/**
	* Metoda zwraca podstawowe obra�enia jakie mo�e poch�on�� os�ona obiektu.
	* \return Podstawowe obra�enia jakie mo�e poch�on�� os�ona obiektu.
	*/
	const Obrazenia& getOslona() const;	

	/**
	* Metoda ustawia podstawowe obra�enia jakie mo�e poch�on�� os�ona obiektu.
	* \param o - Nowe podstawowe obra�enia jakie mo�e poch�on�� os�ona obiektu.
	*/
	void setOslona( const Obrazenia& o );
	
	/**
	* Przeci��ona funkcja generuj�ca tekstowy opis klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string toString() const override;

private:
	Obrazenia atak; /// Podstawowa warto�� ataku obiektu.
	Obrazenia pancerz; /// Podstawowa warto�� pancerza obiektu.
	Obrazenia oslona; /// Podstawowa warto�� os�ony obiektu.
};

