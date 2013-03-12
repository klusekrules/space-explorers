#include "Base.h"
#include "Logger.h"

Base::Base( const IdType& itID )
	: id(itID)
{
}

Base::~Base(){
}

const IdType& Base::getId()const{
	return id;
}

void Base::setId( const IdType& id ){
	this->id = id;
}

string Base::toString() const{
	Logger str(LogBase::className());
	str.addField("ID",id);
	return str.toString();
}
