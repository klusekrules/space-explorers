#include "Info.h"
#include "Logger.h"

Info::Info( const Tekst& tNazwa , const Tekst& tOpis, const IdType& id )
	: Base(id), nazwa( tNazwa ), opis( tOpis )
{
}

Info::~Info(){
}

const Tekst& Info::getNazwa() const{
	return nazwa;
}

void Info::setNazwa( const Tekst& tNazwa ){
	nazwa = tNazwa;
}

const Tekst& Info::getOpis() const{
	return opis;
}

void Info::setOpis( const Tekst& tOpis ){
	opis = tOpis;
}

string Info::toString() const{
	Logger str(LogInfo::className());
	str.addField("Nazwa",nazwa);
	str.addField("Opis",opis);
	return str.toString();
}