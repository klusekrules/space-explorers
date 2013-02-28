#pragma once
/*
class Statek :
	public JednostkaAtakujaca,
	public JednostkaLatajaca,
	public Ladownia,
	public Obiekt
{
	friend StatekInfo;
public:
	
	Statek( const Statek& );
	virtual ~Statek();

	Obiekt* Kopia() const override;
	Obiekt* Podziel( const SPG::IloscJednostek& ) throw( OgolnyWyjatek ) override;

	bool Polacz( const Obiekt& ) throw( std::bad_cast ) override;
	SPG::Obrazenia Atak()const override;
	SPG::Obrazenia Pancerz( const SPG::Obrazenia& )const override;	
	SPG::Obrazenia Oslona( const SPG::Obrazenia& )const override;
	SPG::ZuzyciePaliwa ZuzyciePaliwa( const SPG::Dystans& , const SPG::Predkosc& ) const override;
	SPG::Predkosc PredkoscMaksymalna() const override;
	SPG::Objetosc MaksymalnaPojemnosc() const override;
	SPG::Objetosc Objetosc() const override;
	SPG::Masa Masa() const override;

	SPG::IloscJednostek getIlosc() const;
	void setIlosc( const SPG::IloscJednostek& );

	string toString() const override;
private:

	Statek();
	Statek( const SPG::IloscJednostek& , const Statek& );
	Statek( const SPG::IloscJednostek& , const StatekInfo& );

	SPG::IloscJednostek ilosc;

};
*/
