#include "HangarInfo.h"
#include "XmlBO.h"
#include "Logger\Logger.h"
#include "Statek.h"

HangarInfo::HangarInfo( const Objetosc& maksymalnaObjetosc, const Info& info ) throw()
	: Info(info), pojemnoscMaksymalna_(maksymalnaObjetosc), przyrostPojemnosciMaksymalnej_(nullptr)
{
}

HangarInfo::HangarInfo( const HangarInfo& obiekt )
	:Info(obiekt), pojemnoscMaksymalna_(obiekt.pojemnoscMaksymalna_) , przyrostPojemnosciMaksymalnej_(nullptr)
{
	if(obiekt.przyrostPojemnosciMaksymalnej_)
		przyrostPojemnosciMaksymalnej_ = shared_ptr<ZmianaInterfejs>(obiekt.przyrostPojemnosciMaksymalnej_->Kopia());
}

HangarInfo::HangarInfo(  TiXmlElement* wezel )
	: Info(wezel), przyrostPojemnosciMaksymalnej_(nullptr)
{
	if(wezel){
		try{
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_POJEMNOSC_MAKSYMALNA,pojemnoscMaksymalna_);
			przyrostPojemnosciMaksymalnej_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_POJEMNOSC_MAKSYMALNA));
		}catch(exception& wyjatek){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

HangarInfo::~HangarInfo()
{
}

Objetosc HangarInfo::pobierzMaksymalnaIloscPrzewozonychStatkow( const PodstawoweParametry& parametry ) const{
	if(przyrostPojemnosciMaksymalnej_)
		return Objetosc(przyrostPojemnosciMaksymalnej_->policzWartosc(pojemnoscMaksymalna_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
	else
		return pojemnoscMaksymalna_;
}
		
string HangarInfo::napis() const{
	Logger str(NAZWAKLASY(HangarInfo));
	str.dodajKlase(Info::napis());
	str.dodajPole("MaksymalnaPojemnosc",pojemnoscMaksymalna_);
	if(przyrostPojemnosciMaksymalnej_)
		str.dodajPole("ZmianaMaksymalnaPojemnosc",*przyrostPojemnosciMaksymalnej_);
	return str.napis();
}
