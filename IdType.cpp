#include "IdType.h"
#include "Logger.h"

IdType::IdType()
	: id(idDomyslny)
{
}

IdType::IdType( const type_name& ID )
	: id(ID)
{
}

IdType::IdType( const IdType& a )
	: id(a.id)
{
}

IdType::~IdType(){
}


bool IdType::operator==( const IdType& a )const{
	return id==a.id;
}

bool IdType::operator!=( const IdType& a )const{
	return id!=a.id;
}

IdType::type_name IdType::getId()const{
	return id;
}

void IdType::setId( const type_name & ID ){
	id=ID;
}

IdType::type_name IdType::value()const{
	return getId();
}


string IdType::toString()const{
	return Logger::field(className(),id);
}
