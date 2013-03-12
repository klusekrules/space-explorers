
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
	* Destruktor domyœlny.
	*/
	virtual ~JednostkaAtakujacaInfo();

	/**
	* Metoda zwraca podstawowe obra¿enia zadawane przez obiekt.
	* \return Podstawowe obra¿enia zadawane przez obiekt.
	*/
	const Obrazenia& getAtak() const;	

	/**
	* Metoda zwraca podstawowe obra¿enia jakie zniszcz¹ obiekt.
	* \return Podstawowe obra¿enia jakie zniszcz¹ obiekt.
	*/
	const Obrazenia& getPancerz() const;	

	/**
	* Metoda zwraca podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	* \return Podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	*/
	const Obrazenia& getOslona() const;	

	/**
	* Przeci¹¿ona funkcja generuj¹ca tekstowy opis klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string toString() const override;

private:
	Obrazenia atak; /// Podstawowa wartoœæ ataku obiektu.
	ZmianaInterfejs<Obrazenia>* zmAtak; /// Procentowa zmiana ataku wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

	Obrazenia pancerz; /// Podstawowa wartoœæ pancerza obiektu.
	ZmianaInterfejs<Obrazenia>* zmPancerz; /// Procentowa zmiana pancerza wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

	Obrazenia oslona; /// Podstawowa wartoœæ os³ony obiektu.
	ZmianaInterfejs<Obrazenia>* zmOslona; /// Procentowa zmiana os³ony wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.
};

