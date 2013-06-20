
#pragma once
#include "Main.h"
#include "Obrazenia.h"
#include "Info.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "WyjatekParseraXML.h"

class JednostkaAtakujacaInfo :
	public Info,
	virtual public LoggerInterface
{
public:
	/**
	* Konstruktor parametryczny.
	* \param oAtak - podstawowny atak obiektu
	* \param oPancerz - podstawowy pancerz obiektu
	* \param oOslona - postawowa oslona obiektu
	*/
	JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona ) throw();

	explicit JednostkaAtakujacaInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	/**
	* Destruktor domyœlny.
	*/
	virtual ~JednostkaAtakujacaInfo();

	/**
	* Metoda zwraca podstawowe obra¿enia zadawane przez obiekt.
	* \return Podstawowe obra¿enia zadawane przez obiekt.
	*/
	Obrazenia getAtak(const Poziom& p ) const;	

	/**
	* Metoda zwraca podstawowe obra¿enia jakie zniszcz¹ obiekt.
	* \return Podstawowe obra¿enia jakie zniszcz¹ obiekt.
	*/
	Obrazenia getPancerz(const Poziom& p ) const;	

	/**
	* Metoda zwraca podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	* \return Podstawowe obra¿enia jakie mo¿e poch³on¹æ os³ona obiektu.
	*/
	Obrazenia getOslona(const Poziom& p ) const;	

	/**
	* Przeci¹¿ona funkcja generuj¹ca tekstowy opis klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string toString() const override;

private:
	Obrazenia atak; /// Podstawowa wartoœæ ataku obiektu.
	ZmianaInterfejs* zmAtak; /// Procentowa zmiana ataku wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

	Obrazenia pancerz; /// Podstawowa wartoœæ pancerza obiektu.
	ZmianaInterfejs* zmPancerz; /// Procentowa zmiana pancerza wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.

	Obrazenia oslona; /// Podstawowa wartoœæ os³ony obiektu.
	ZmianaInterfejs* zmOslona; /// Procentowa zmiana os³ony wzglêdem wartoœci podstawowej. Domyœlnie 1.0 - 100% wartoœci podstawowej.
};

