#include "BudynekInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"

BudynekInfo::BudynekInfo( TiXmlElement* n )
	: ObiektInfo(n)
{
	auto z = XmlBO::ZnajdzWezel<NOTHROW>(n,WEZEL_XML_ZAPOTRZEBOWANIE);
	while(z){
		zapotrzebowanie.push_back(shared_ptr<Cena>(new Cena(z)));
		z = z->NextSiblingElement();
	}

	auto p = XmlBO::ZnajdzWezel<NOTHROW>(n,WEZEL_XML_PRODUKCJA);
	while(p){
		produkcja.push_back(shared_ptr<Cena>(new Cena(p)));
		p = p->NextSiblingElement();
	}
}

bool BudynekInfo::Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return g.wybudujNaPlanecie(p,*this,i);
}

BudynekInfo::~BudynekInfo(void)
{
}

Budynek* BudynekInfo::TworzEgzemplarz( const Ilosc&, const IdType& idP ) const{
	return new Budynek(getPoziom(),idP,*this);
}

Cennik::ListaSurowcow BudynekInfo::PobierzZapotrzebowanie( const PodstawoweParametry& param )const{
	Cennik::ListaSurowcow list;
	for(auto z : zapotrzebowanie){
		list.push_back(z->PobierzKoszty(Ilosc(1),param));
	}
	return list;
}

Cennik::ListaSurowcow BudynekInfo::PobierzProdukcje( const PodstawoweParametry& param )const{
	Cennik::ListaSurowcow list;
	for(auto z : produkcja){
		list.push_back(z->PobierzKoszty(Ilosc(1),param));
	}
	return list;
}

string BudynekInfo::napis()const{
	Logger str(NAZWAKLASY(BudynekInfo));
	str.dodajKlase(ObiektInfo::napis());
	for(auto i : zapotrzebowanie)
		if(i)
			str.dodajPole("ElementZapotrzebowania",*i);
	for(auto i : produkcja)
		if(i)
			str.dodajPole("ElementProdukcji",*i);
	return str.napis();
}