#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "LadowniaInfo.h"
#include "JednostkaLatajacaInfo.h"
#include "JednostkaAtakujacaInfo.h"
#include "Statek.h"

class StatekInfo:
	public ObiektInfo,
	public JednostkaLatajacaInfo,
	public JednostkaAtakujacaInfo,
	public LadowniaInfo,
	public LoggerInterface < StatekInfo >
{
public:	
	typedef LoggerInterface < StatekInfo > LogStatekInfo;

	StatekInfo(	const ObiektInfo& o , const JednostkaLatajacaInfo& j , const JednostkaAtakujacaInfo& a , const LadowniaInfo& l );

	virtual ~StatekInfo();

	const IdType& getId() const;
		
	Statek* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;
};