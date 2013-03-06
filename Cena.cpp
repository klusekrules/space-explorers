#include "Cena.h"
#include "Logger.h"

Cena::Cena()
	: obiekty()
{
}

Cena::Cena( const Zbiornik & zsKoszty )
	: obiekty(zsKoszty)
{
}

Cena::Cena( const Cena& a )
	: obiekty(a.obiekty)
{
}

Cena::~Cena(){
}

Cena::Zbiornik Cena::PobierzKoszty() const{
	return obiekty;
}

const Cena::Zbiornik& Cena::getKoszty() const{
	return obiekty;
}

Cena& Cena::operator=(const Cena& a){
	this->obiekty=a.obiekty;
	return *this;
}

Cena* Cena::Kopia() const{
	return new Cena(*this);
}

bool Cena::czySpelniaWymagania( const Zbiornik& z ) const{
	for(auto a : obiekty){
		try{
			Surowce& o = z.get(a.second->ID());
			if(a.second->getIlosc() > o.getIlosc() )
				return false;
		}catch( const NieznalezionoObiektu& ){
			return false;
		}
	}
	return true;
}

void Cena::setKoszty( const Zbiornik& zsKoszty ){
	obiekty = zsKoszty;
}

string Cena::toString() const{
	Logger str(LogCena::className());
	str.addField("ZbiornikSurowcow",obiekty);
	return str.toString();
}