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

	explicit StatekInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	virtual ~StatekInfo();

	const IdType& getId() const;
		
	Statek* TworzEgzemplarz( const Ilosc&, const IdType& ) const override;

	string toString() const override;

private:
	bool Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const override;

};