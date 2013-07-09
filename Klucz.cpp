#include "Klucz.h"
#include "Logger.h"

ostream& operator<< (ostream& out, const Klucz::type_name& base){
	out << base.first.toString() << " " << base.second.toString() ;
	return out;
}

Klucz::Klucz()
	: BaseInterface( make_pair< IdType , Poziom >( IdType() , Poziom() ) ) 
{
}

Klucz::Klucz( const IdType& id , const Poziom& poziom )
	: BaseInterface( make_pair<IdType,Poziom>( IdType(id) , Poziom(poziom) ) )
{
}

Klucz::Klucz( const type_name& pair )
	: BaseInterface( pair )
{
}

Klucz::Klucz( const Klucz& klucz )
	: BaseInterface( klucz )
{
}

Klucz::Klucz( TiXmlElement* n )
	: BaseInterface( make_pair< IdType , Poziom >( IdType() , Poziom() ) ) 
{
	if(n!=nullptr){
		try{
			wartosc_ = make_pair<IdType,Poziom>( IdType(stoi(n->Attribute("id"),nullptr,0)) , Poziom(stoi(n->Attribute("poziom"))) );
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Klucz::~Klucz(){
}

bool Klucz::operator==( const Klucz& a )const{
	return wartosc_ == a.wartosc_;
}

bool Klucz::operator!=( const Klucz& a )const{
	return wartosc_ != a.wartosc_;
}

bool Klucz::operator<( const Klucz& a )const{
	return wartosc_.first < a.wartosc_.first ? true : wartosc_.second < a.wartosc_.second;
}

string Klucz::toString()const{
	return Logger::field(CLASSNAME(Klucz),wartosc_.first,wartosc_.second);
}
