#pragma once
#include "BaseTypes.h"

class Fluktuacja:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Fluktuacja>
{
private:
	type_name fluktuacja;
public:
	Fluktuacja();
	Fluktuacja( const Fluktuacja& );
	explicit Fluktuacja( const type_name& );
	virtual ~Fluktuacja();

	bool operator==( const Fluktuacja& )const;
	bool operator!=( const Fluktuacja& )const;
	bool operator<( const Fluktuacja& )const;
	bool operator>( const Fluktuacja& )const;
	bool operator<=( const Fluktuacja& )const;
	bool operator>=( const Fluktuacja& )const;

	Fluktuacja& operator=( const Fluktuacja& );
	Fluktuacja& operator-=( const Fluktuacja& );
	Fluktuacja& operator+=( const Fluktuacja& );
	Fluktuacja operator-( const Fluktuacja& )const;
	Fluktuacja operator+( const Fluktuacja& )const;

	type_name getFluktuacja() const;

	void setFluktuacja( const type_name& );

	type_name value() const override;

	string toString() const override; 
};

