
#pragma once
#include "Main.h"
#include "Obrazenia.h"
#include "Info.h"
#include "ZmianaInterfejs.h"

class JednostkaAtakujacaInfo :
	public Info,
	public LoggerInterface < JednostkaAtakujacaInfo >
{
public:
	typedef LoggerInterface<JednostkaAtakujacaInfo> LogJednostkaAtakujacaInfo;
	
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
	* Metoda zwraca podstawowe obra�enia jakie zniszcz� obiekt.
	* \return Podstawowe obra�enia jakie zniszcz� obiekt.
	*/
	const Obrazenia& getPancerz() const;	

	/**
	* Metoda zwraca podstawowe obra�enia jakie mo�e poch�on�� os�ona obiektu.
	* \return Podstawowe obra�enia jakie mo�e poch�on�� os�ona obiektu.
	*/
	const Obrazenia& getOslona() const;	

	/**
	* Przeci��ona funkcja generuj�ca tekstowy opis klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string toString() const override;

private:
	Obrazenia atak; /// Podstawowa warto�� ataku obiektu.
	ZmianaInterfejs<Obrazenia>* zmAtak; /// Procentowa zmiana ataku wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.

	Obrazenia pancerz; /// Podstawowa warto�� pancerza obiektu.
	ZmianaInterfejs<Obrazenia>* zmPancerz; /// Procentowa zmiana pancerza wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.

	Obrazenia oslona; /// Podstawowa warto�� os�ony obiektu.
	ZmianaInterfejs<Obrazenia>* zmOslona; /// Procentowa zmiana os�ony wzgl�dem warto�ci podstawowej. Domy�lnie 1.0 - 100% warto�ci podstawowej.
};

