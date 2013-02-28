#pragma once
#include "Main.h"
#include "Info.h"
#include "Masa.h"
#include "Objetosc.h"
#include "Powierzchnia.h"
#include "Obiekt.h"

class ObiektInfo :
	public Info,
	virtual public Base,
	public ObiektBase,
	public Masa,
	public Objetosc,
	public Powierzchnia,
	public LoggerInterface<ObiektInfo>
{
public:
	typedef LoggerInterface<ObiektInfo> LogObiektInfo;
	ObiektInfo( );
	ObiektInfo( const Masa&, const Objetosc&, const Powierzchnia&, const Info& ,const ObiektBase& );
	~ObiektInfo( );
	
	virtual Obiekt* TworzEgzemplarz( const Ilosc& ) const;

	string toString() const override;
};

