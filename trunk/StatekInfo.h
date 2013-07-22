#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "LadowniaInfo.h"
#include "JednostkaLatajacaInfo.h"
#include "JednostkaAtakujacaInfo.h"
#include "Statek.h"
#include "parser\ticpp.h"

class StatekInfo:
	public ObiektInfo,
	public JednostkaLatajacaInfo,
	public JednostkaAtakujacaInfo,
	public LadowniaInfo,
	virtual public LoggerInterface
{
public:
	StatekInfo(	const ObiektInfo& o , const JednostkaLatajacaInfo& j , const JednostkaAtakujacaInfo& a , const LadowniaInfo& l ) throw();

	explicit StatekInfo( TiXmlElement* ) throw(WyjatekParseraXML);

	virtual ~StatekInfo();

	const Identyfikator& getId() const;
		
	Statek* tworzEgzemplarz( const Ilosc&, const Identyfikator& ) const override;

	string napis() const override;

private:
	bool tworz( const Gra& g, Planeta& p , const Ilosc& i ) const override;

};