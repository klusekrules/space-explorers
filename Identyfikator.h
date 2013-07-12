#pragma once
#include "Main.h"
#include "TypyProste.h"
#include "parser\ticpp.h"
#include "Ilosc.h"

class Identyfikator :
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Identyfikator>
{
public:
	
	Identyfikator();
	explicit Identyfikator( const type_name& ID );
	explicit Identyfikator( const Ilosc& ID );
	Identyfikator( const Identyfikator& a );
	virtual ~Identyfikator();

	bool operator==( const Identyfikator& )const;
	bool operator!=( const Identyfikator& )const;

	bool operator<( const Identyfikator& )const;

	explicit operator size_t()const;
	
	string napis()const override;
};

struct IdTypeHash {
    size_t operator()(const Identyfikator& t) const {
		return static_cast<size_t>(t());
    }
};
