#pragma once
#include "Main.h"
#include "BaseTypes.h"
#include "Fluktuacja.h"
#include "Ilosc.h"

class Powierzchnia:	
	virtual public LoggerInterface,
	public BaseInterface<SPG::Powierzchnia>
{
private:
	type_name powierzchnia;
public:
	Powierzchnia();
	Powierzchnia( const Powierzchnia& );
	explicit Powierzchnia( const type_name& );
	virtual ~Powierzchnia();

	bool operator==( const Powierzchnia& )const;
	bool operator!=( const Powierzchnia& )const;
	bool operator<( const Powierzchnia& )const;
	bool operator<=( const Powierzchnia& )const;
	bool operator>( const Powierzchnia& )const;
	bool operator>=( const Powierzchnia& )const;

	Powierzchnia& operator=( const Powierzchnia& );
	Powierzchnia& operator-=( const Powierzchnia& );
	Powierzchnia& operator+=( const Powierzchnia& );
	Powierzchnia operator-( const Powierzchnia& )const;
	Powierzchnia operator+( const Powierzchnia& )const;
	Powierzchnia operator*( const Fluktuacja& )const;
	Powierzchnia& operator*=( const Fluktuacja& );
	Powierzchnia operator*( const Ilosc& )const;
	Powierzchnia& operator*=( const Ilosc& );


	type_name getPowierzchnia() const;

	void setPowierzchnia( const type_name& );

	type_name value() const override;

	string toString() const override; 
};

