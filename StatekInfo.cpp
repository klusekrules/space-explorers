#include "StatekInfo.h"
#include "XmlBO.h"

StatekInfo::StatekInfo( const ObiektInfo& o , const JednostkaLatajacaInfo& j , const JednostkaAtakujacaInfo& a , const LadowniaInfo& l  )
	: ObiektInfo(o), JednostkaLatajacaInfo(j), JednostkaAtakujacaInfo(a), LadowniaInfo(l)
{
}

StatekInfo::StatekInfo( ticpp::Node* n )
	: ObiektInfo(XmlBO::InterateChildren(n,ObiektInfo::LogObiektInfo::className())),
	JednostkaLatajacaInfo(XmlBO::InterateChildren(n,JednostkaLatajacaInfo::LogJednostkaLatajacaInfo::className())),
	JednostkaAtakujacaInfo(XmlBO::InterateChildren(n,JednostkaAtakujacaInfo::LogJednostkaAtakujacaInfo::className())),
	LadowniaInfo(XmlBO::InterateChildren(n,LadowniaInfo::LogLadowniaInfo::className()))
{
}

StatekInfo::~StatekInfo(){
}

const IdType& StatekInfo::getId() const{
	return ObiektInfo::getId();
}

Statek* StatekInfo::TworzEgzemplarz( const Ilosc& i ) const{
	return new Statek(i,*this);
}

string StatekInfo::toString() const{
	Logger str(LogStatekInfo::className());
	str.addClass(ObiektInfo::toString());
	str.addClass(JednostkaLatajacaInfo::toString());
	str.addClass(JednostkaAtakujacaInfo::toString());
	str.addClass(LadowniaInfo::toString());
	return str.toString();
}