#include "LadowniaInfo.h"
#include "Logger.h"


LadowniaInfo::LadowniaInfo( const Objetosc& max, const Info& i )
	: Info(i),pojemnoscMax(max), przyrostPojemnoscMax(nullptr)
{
}

LadowniaInfo::~LadowniaInfo()
{
}

Objetosc LadowniaInfo::getPojemnoscMaksymalna() const{
	if(przyrostPojemnoscMax==nullptr)
		return pojemnoscMax;
	else
		return przyrostPojemnoscMax->value(pojemnoscMax);
}
		
string LadowniaInfo::toString() const{
	Logger str(LogLadowniaInfo::className());
	str.addField("MaksymalnaPojemnosc",pojemnoscMax);
	if(przyrostPojemnoscMax!=nullptr)
		str.addField("ZmianaMaksymalnaPojemnosc",*przyrostPojemnoscMax);
	return str.toString();
}