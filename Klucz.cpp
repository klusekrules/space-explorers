#include "Klucz.h"
#include "Logger.h"

ostream& operator<< (ostream& out, const Klucz::type_name& base){
	out << base.first.toString() << " " << base.second.toString() ;
	return out;
}

Klucz::Klucz()
	: values( make_pair< IdType , Poziom >( IdType() , Poziom() ) ) 
{
}

Klucz::Klucz( const IdType& id , const Poziom& poziom )
	: values( make_pair<IdType,Poziom>( IdType(id) , Poziom(poziom) ) )
{
}

Klucz::Klucz( const type_name& pair )
	: values( pair )
{
}

Klucz::Klucz( const Klucz& klucz )
	: values( klucz.values )
{
}

Klucz::Klucz( ticpp::Node* n ){
	if(n!=nullptr){
		try{
			ticpp::Element* e = n->ToElement();
			values = make_pair<IdType,Poziom>( IdType(stoi(e->GetAttribute("id"))) , Poziom(stoi(e->GetAttribute("poziom"))) );
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
	
}

Klucz::~Klucz(){
}

bool Klucz::operator==( const Klucz& a )const{
	return values == a.values;
}

bool Klucz::operator!=( const Klucz& a )const{
	return values != a.values;
}

Klucz::type_name Klucz::getKlucz()const{
	return values;
}

void Klucz::setKlucz( const type_name& pair ){
	values = pair;
}

Klucz::type_name Klucz::value()const{
	return getKlucz();
}

string Klucz::toString()const{
	return Logger::field(className(),values.first,values.second);
}