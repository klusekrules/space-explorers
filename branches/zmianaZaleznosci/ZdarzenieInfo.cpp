#include "ZdarzenieInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

ZdarzenieInfo::ZdarzenieInfo( tinyxml2::XMLElement* wezel )
	: nastepnyStan_(nullptr), nastepnyNumer_(nullptr)
{
	if(wezel){
		XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,id_);		
		luaFuncInside_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_INSIDE,std::string());
		luaFile_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_FILE,std::string());
		if( luaFile_.empty() && !luaFuncInside_.empty() ) 
			throw OgolnyWyjatek(EXCEPTION_PLACE);

		Identyfikator stan;
		if(XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_STAN_NASTEPNY,stan)){
			nastepnyStan_ = std::make_shared<Identyfikator>(stan);
		}

		if(XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NUMER_NASTEPNY,stan)){
			nastepnyNumer_ = std::make_shared<int>(stan());
		}
		if(!luaFile_.empty()){
			skrypt_.zaladuj(luaFile_);
			skrypt_.wykonaj();
		}
	}	
}

ZdarzenieInfo::~ZdarzenieInfo(void)
{
}

bool ZdarzenieInfo::wykonaj(){
	if(luaFuncInside_.empty())
		return true;
	return skrypt_.wykonaj(luaFuncInside_);
}

const Identyfikator& ZdarzenieInfo::pobierzIdentyfikator() const{
	return id_;
}

std::shared_ptr< Identyfikator > ZdarzenieInfo::pobierzStan() const{
	return nastepnyStan_;
}

std::shared_ptr< int > ZdarzenieInfo::pobierzNumer() const{
	return nastepnyNumer_;
}
	

std::string ZdarzenieInfo::napis() const{
	Logger log(NAZWAKLASY(ZdarzenieInfo));
	log.dodajPole("Identyfikator",id_);
	log.dodajPole("luaFuncInside",luaFuncInside_);
	log.dodajPole("luaFile",luaFile_);
	log.dodajPole("nastepnyStan",nastepnyStan_);
	if(nastepnyNumer_)
		log.dodajPole("nastepnyNumer",Identyfikator(*nastepnyNumer_));
	return log.napis();
}
