#include "BudynekInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Gra.h"

BudynekInfo::BudynekInfo( TiXmlElement* n )
	: ObiektInfo(XmlBO::IterateChildren<THROW>(n,CLASSNAME(ObiektInfo)))
{
	auto z = XmlBO::IterateChildren<NOTHROW>(n,"Zapotrzebowanie");
	if(z){
		auto e = z->FirstChildElement();
		while(e){
			if(e->Value() == CLASSNAME(Cena))
				zapotrzebowanie.push_back(shared_ptr<Cena>(new Cena(e)));
			e = e->NextSiblingElement();
		}
	}

	auto p = XmlBO::IterateChildren<NOTHROW>(n,"Produkcja");
	if(p){
		auto e = p->FirstChildElement();
		while(e){
			if(e->Value() == CLASSNAME(Cena))
				produkcja.push_back(shared_ptr<Cena>(new Cena(e)));
			e = e->NextSiblingElement();
		}
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

string BudynekInfo::toString()const{
	Logger str(CLASSNAME(BudynekInfo));
	str.addClass(ObiektInfo::toString());
	for(auto i : zapotrzebowanie)
		if(i)
			str.addField("ElementZapotrzebowania",*i);
	for(auto i : produkcja)
		if(i)
			str.addField("ElementProdukcji",*i);
	return str.toString();
}