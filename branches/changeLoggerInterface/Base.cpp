#include "Base.h"
#include "Logger.h"

Base::Base( const IdType& itID )throw()
	: id(itID)
{
}

Base::Base( ticpp::Node* n ) throw(WyjatekParseraXML){
	if(n){
		try{
			id.setId( stoi(n->ToElement()->GetAttribute("id"),nullptr,0) );
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
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
