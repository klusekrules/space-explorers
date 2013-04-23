#pragma once
template < typename T >
 class BaseInterface
{
public:
	typedef T type_name;

	BaseInterface(){
	}

	virtual ~BaseInterface(){
	}

	virtual type_name value() const abstract;
};

