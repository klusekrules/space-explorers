#include "CenaDekorator.h"


CenaDekorator::CenaDekorator( CenaInterfejs* d )
	: dekorator(d)
{
}

CenaDekorator::~CenaDekorator()
{
	delete dekorator;
}

CenaDekorator::CenaDekorator( const CenaDekorator& a )
	: dekorator( a.Kopia() )
{
}

CenaDekorator& CenaDekorator::operator=( const CenaDekorator& a ){
	delete dekorator;
	dekorator = a.Kopia();
	return *this;
}

CenaDekorator* CenaDekorator::Kopia() const{
	return new CenaDekorator(*this);
}

CenaDekorator::Zbiornik CenaDekorator::PobierzKoszty( ) const {
	return dekorator->PobierzKoszty();
}

bool CenaDekorator::czySpelniaWymagania( const Zbiornik& z ) const {
	return dekorator->czySpelniaWymagania(z);
}


string CenaDekorator::toString() const{
	Logger str(LogCenaDekorator::className());
	str.addClass(dekorator->toString());
	return str.toString();
}