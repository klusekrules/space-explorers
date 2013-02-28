#include "Base.h"
#include "Logger.h"

Base::Base()
	: IdType(-1)
{
}

Base::Base( const IdType& itID )
	: IdType(itID)
{
}

Base::~Base(){
}

string Base::toString() const{
	Logger str(LogBase::className());
	str.addClass(Logger::reMakeSimpleClassString(IdType::className(),IdType::toString()));
	return str.toString();
}
