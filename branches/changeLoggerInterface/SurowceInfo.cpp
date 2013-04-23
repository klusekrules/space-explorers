
#include "SurowceInfo.h"
#include "Logger.h"
#include "XmlBO.h"

SurowceInfo::~SurowceInfo(){
}

SurowceInfo::SurowceInfo( const ObiektInfo& o , bool bCzyPrzyrostowy ) throw()
	: ObiektInfo(o) , czyPrzyrostowy(bCzyPrzyrostowy)
{
}

SurowceInfo::SurowceInfo( ticpp::Node* n ) throw(WyjatekParseraXML)
	: ObiektInfo(XmlBO::IterateChildren(n,ObiektInfo::LogObiektInfo::className())) , czyPrzyrostowy (false)
{
	if(n){
		auto s = n->ToElement()->GetAttribute("typ");
		auto i = stoi(s);
		switch(i){
		case 1 : czyPrzyrostowy = true;
			break;
		case 2 : czyPrzyrostowy = false;
			break;
		default: throw WyjatekParseraXML(EXCEPTION_PLACE,exception( (string("typ=") + s).c_str() ),WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

bool SurowceInfo::czyTypPrzyrostowy()const{
	return czyPrzyrostowy.value();
}

Surowce* SurowceInfo::TworzEgzemplarz( const Ilosc& ilosc ) const{
	return new Surowce( ilosc , *this );
}

string SurowceInfo::toString() const{
	Logger str(LogSurowceInfo::className());
	str.addClass(ObiektInfo::toString());
	str.addField("CzyPrzyrostowy",czyPrzyrostowy);
	return str.toString();
}