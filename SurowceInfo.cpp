#include "SurowceInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

SurowceInfo::~SurowceInfo(){
}

SurowceInfo::SurowceInfo( const ObiektInfo& o , bool bCzyPrzyrostowy ) throw()
	: ObiektInfo(o) , czyPrzyrostowy(bCzyPrzyrostowy), zmCzas(nullptr)
{
}

SurowceInfo::SurowceInfo( TiXmlElement* n ) throw(WyjatekParseraXML)
	: ObiektInfo(n) , czyPrzyrostowy (false), zmCzas(nullptr)
{
	if(n){
		zmCzas = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WEZEL_XML_CZAS));
		auto s = n->Attribute(ATRYBUT_XML_TYP);
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
	return czyPrzyrostowy();
}

bool SurowceInfo::Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return g.wybudujNaPlanecie(p,*this,i);
}

Czas SurowceInfo::pobierzCzas( const Ilosc& i ,const PodstawoweParametry& p )const{
	if(zmCzas)
		return Czas(zmCzas->policzWartosc(i(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()()));
	else
		return Czas(0.0l);
}

Surowce* SurowceInfo::TworzEgzemplarz( const Ilosc& ilosc, const IdType& idP ) const{
	return new Surowce( ilosc , getPoziom(),idP, *this );
}

string SurowceInfo::toString() const{
	Logger str(CLASSNAME(SurowceInfo));
	str.addClass(ObiektInfo::toString());
	str.addField("CzyPrzyrostowy",czyPrzyrostowy);
	return str.toString();
}