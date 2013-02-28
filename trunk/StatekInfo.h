#pragma once
/*
class StatekInfo:
	public JednostkaAtakujaca,
	public JednostkaLatajaca,
	public Ladownia,
	public Cena,
	public Obiekt,
	public Info
{
public:	
	static const SPG::IdType idStatekMaska;
	StatekInfo();

	StatekInfo(	const Obiekt&,
		const Cena&,
		const Info&,
		const Ladownia&,
		const SPG::RodzajNapedu&,
		const SPG::MocSilnika&,
		const SPG::ZuzyciePaliwa&,
		const SPG::Obrazenia&,
		const SPG::Obrazenia&,
		const SPG::Obrazenia&
		);

	StatekInfo( const StatekInfo& );

	virtual ~StatekInfo();
	
	SPG::ZuzyciePaliwa ZuzyciePaliwa( const SPG::Dystans& , const SPG::Predkosc& ) const override;
	SPG::Predkosc PredkoscMaksymalna() const override;
	SPG::Obrazenia Atak() const override;	
	SPG::Obrazenia Pancerz( const SPG::Obrazenia& ) const override;		
	SPG::Obrazenia Oslona( const SPG::Obrazenia& ) const override;
	
	Statek* TworzEgzemplarz( const SPG::IloscJednostek& ) const;

	string toString() const override;
};*/