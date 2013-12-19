#include "StanInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

StanInfo::StanInfo( tinyxml2::XMLElement* wezel )
{
	if(wezel){
		XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,id_);		
		luaFile_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_FILE,std::string());
		luaFuncIn_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_IN,std::string());
		luaFuncOut_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_OUT,std::string());
		luaFuncInside_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_INSIDE,std::string());
		
		if( luaFile_.empty() && !( luaFuncInside_.empty() && luaFuncOut_.empty() && luaFuncIn_.empty() ) ) 
			throw OgolnyWyjatek(EXCEPTION_PLACE);
		for(tinyxml2::XMLElement* element = wezel->FirstChildElement(WEZEL_XML_ZDARZENIE); element ; element = element->NextSiblingElement(WEZEL_XML_ZDARZENIE)){
			auto zdarzenie = std::make_shared<ZdarzenieInfo>(element);
			zdarzenia_.insert(std::make_pair(zdarzenie->pobierzIdentyfikator(), zdarzenie));
		}

		if( !luaFile_.empty() ){
			skrypt_.zaladuj(luaFile_);
			skrypt_.wykonaj();
		}
	}
}

bool StanInfo::wykonaj( Akcja akcja ){
	std::string funkcja, *ptr;
	ptr = &funkcja;
	switch (akcja)
	{
	case StanInfo::AkcjaWejsciowa:
		if(luaFuncIn_.empty())
			return true;
		ptr = &luaFuncIn_;
		break;
	case StanInfo::AkcjaWyjsciowa:
		if(luaFuncOut_.empty())
			return true;
		ptr = &luaFuncOut_;
		break;
	case StanInfo::AkcjaWewnetrzna:
		if(luaFuncInside_.empty())
			return true;
		ptr = &luaFuncInside_;
		break;
	default:
		return false;
	}
	return skrypt_.wykonaj(*ptr);
}

StanInfo::~StanInfo(void){}


const Identyfikator& StanInfo::pobierzIdentyfikator() const{
	return id_;
}

std::shared_ptr<ZdarzenieInfo> StanInfo::pobierzZdarzenie( const Identyfikator& id ) const{
	auto iter = zdarzenia_.find(id);
	if(iter == zdarzenia_.end() )
		return nullptr;
	return iter->second;
}

std::string StanInfo::napis()const{
	Logger log(NAZWAKLASY(StanInfo));
	log.dodajPole("Identyfikator",id_);
	log.dodajPole("luaFuncIn",luaFuncIn_);
	log.dodajPole("luaFuncOut",luaFuncOut_);
	log.dodajPole("luaFuncInside",luaFuncInside_);
	log.dodajPole("luaFile",luaFile_);
	return log.napis();
}