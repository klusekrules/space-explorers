#pragma once
#include "Main.h"
#include "TypyProste.h"
#include "parser\ticpp.h"
#include "Ilosc.h"

class IdType :
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::IdType>
{
public:
	
	IdType();
	explicit IdType( const type_name& ID );
	explicit IdType( const Ilosc& ID );
	IdType( const IdType& a );
	virtual ~IdType();

	bool operator==( const IdType& )const;
	bool operator!=( const IdType& )const;

	bool operator<( const IdType& )const;

	explicit operator size_t()const;
	
	string napis()const override;
};

struct IdTypeHash {
    size_t operator()(const IdType& t) const {
		return static_cast<size_t>(t());
    }
};
