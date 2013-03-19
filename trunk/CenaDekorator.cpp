#include "CenaDekorator.h"
#include "Cena.h"
#include "CenaLiniowyDekorator.h"
#include "Logger.h"

CenaDekorator::CenaDekorator( ticpp::Node* n ){
	if(n!=nullptr){
		auto a = n->IterateChildren(Cena::LogCena::className(),nullptr);
		if(a!=nullptr){
			dekorator = new Cena(a);
		}else{
			a = n->IterateChildren(CenaDekorator::LogCenaDekorator::className(),nullptr);
			if(a!=nullptr){
				dekorator = TworzDekorator(n);
			}else{
				dekorator = nullptr;
			}
		}
	}
}

CenaDekorator* CenaDekorator::TworzDekorator( ticpp::Node* n ){
	if(n==nullptr)
		return nullptr;
	try{
		switch(stoi(n->ToElement()->GetAttribute("id"),nullptr,0)){
		case 1:
			return new CenaLiniowyDekorator(n);
		}
	}catch(exception& e){
		throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
	}
	return nullptr;
}

CenaDekorator::CenaDekorator( CenaInterfejs* d )
	: dekorator(d)
{
}

CenaDekorator::~CenaDekorator()
{
	if(dekorator)
		delete dekorator;
}

CenaDekorator::CenaDekorator( const CenaDekorator& a )
	: dekorator( a.Kopia() )
{
}

CenaDekorator& CenaDekorator::operator=( const CenaDekorator& a ){
	if(dekorator)
		delete dekorator;
	dekorator = a.Kopia();
	return *this;
}

CenaDekorator* CenaDekorator::Kopia() const{
	return new CenaDekorator(*this);
}

CenaDekorator::Item CenaDekorator::PobierzKoszty( ) const {
	if(dekorator)
		return dekorator->PobierzKoszty();
	else
		throw NiezainicjalizowanaKlasa( EXCEPTION_PLACE , Tekst(__FUNCTION__) );
}

bool CenaDekorator::czySpelniaWymagania( const Ilosc& i, const IdType& idPlanety ) const {
	if(dekorator)
		return dekorator->czySpelniaWymagania(i,idPlanety);
	else
		throw NiezainicjalizowanaKlasa( EXCEPTION_PLACE , Tekst(__FUNCTION__) );
}
string CenaDekorator::toString() const{
	Logger str(LogCenaDekorator::className());
	if(dekorator)
		str.addClass(dekorator->toString());
	return str.toString();
}