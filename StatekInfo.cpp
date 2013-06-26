#include "StatekInfo.h"
#include "XmlBO.h"

StatekInfo::StatekInfo( const ObiektInfo& o , const JednostkaLatajacaInfo& j , const JednostkaAtakujacaInfo& a , const LadowniaInfo& l  ) throw()
	: ObiektInfo(o), JednostkaLatajacaInfo(j), JednostkaAtakujacaInfo(a), LadowniaInfo(l)
{
}

StatekInfo::StatekInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: ObiektInfo(XmlBO::IterateChildren<THROW>(n,CLASSNAME(ObiektInfo))),
	JednostkaLatajacaInfo(XmlBO::IterateChildren<THROW>(n,CLASSNAME(JednostkaLatajacaInfo))),
	JednostkaAtakujacaInfo(XmlBO::IterateChildren<THROW>(n,CLASSNAME(JednostkaAtakujacaInfo))),
	LadowniaInfo(XmlBO::IterateChildren<THROW>(n,CLASSNAME(LadowniaInfo)))
{
}

StatekInfo::~StatekInfo(){
}

const IdType& StatekInfo::getId() const{
	return ObiektInfo::getId();
}

Statek* StatekInfo::TworzEgzemplarz( const Ilosc& i ) const{
	return new Statek(i,getPoziom(),*this);
}

string StatekInfo::toString() const{
	Logger str(CLASSNAME(StatekInfo));
	str.addClass(ObiektInfo::toString());
	str.addClass(JednostkaLatajacaInfo::toString());
	str.addClass(JednostkaAtakujacaInfo::toString());
	str.addClass(LadowniaInfo::toString());
	return str.toString();
}