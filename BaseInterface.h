#pragma once
template < typename T >
 class BaseInterface
{
public:
	typedef T type_name;

	BaseInterface( const type_name& wartosc )
		: wartosc_ ( wartosc )
	{
	}

	virtual ~BaseInterface(){
	}

	type_name operator()() const {
		return wartosc_;
	}

	void operator()( const type_name& wartosc ){
		wartosc_ = wartosc;
	}

protected:
	type_name wartosc_;
};

