#include "StanInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

StanInfo::StanInfo( TiXmlElement* wezel )
	: L(luaL_newstate())
{
	if(wezel){
		int status;
		luaL_openlibs(L);
		XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,id_);		
		luaFile_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_FILE,std::string());
		luaFuncIn_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_IN,std::string());
		luaFuncOut_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_OUT,std::string());
		luaFuncInside_ = XmlBO::WczytajAtrybut<std::string>(wezel,ATRYBUT_XML_STAN_LUA_INSIDE,std::string());
		
		if( luaFile_.empty() && !( luaFuncInside_.empty() && luaFuncOut_.empty() && luaFuncIn_.empty() ) ) 
			throw OgolnyWyjatek(EXCEPTION_PLACE);
		for(TiXmlElement* element = wezel->FirstChildElement(WEZEL_XML_ZDARZENIE); element ; element = element->NextSiblingElement(WEZEL_XML_ZDARZENIE)){
			auto zdarzenie = std::make_shared<ZdarzenieInfo>(element);
			zdarzenia_.insert(std::make_pair(zdarzenie->pobierzIdentyfikator(), zdarzenie));
		}

		if( !luaFile_.empty() ){
			status = luaL_loadfile(L, luaFile_.c_str());
			if (status) {
				std::stringstream ss;
				ss << "Couldn't load file:" << lua_tostring(L, -1) << std::endl;
				Log::pobierzInstancje().loguj(Log::Error,ss.str());
				return;
			}

			status = lua_pcall(L, 0, LUA_MULTRET, 0);
			if (status) {
				std::stringstream ss;
				ss << "Failed to run script:" << lua_tostring(L, -1) << std::endl;
				Log::pobierzInstancje().loguj(Log::Error,ss.str());
				return;
			}
		}
	}
}

bool StanInfo::wykonaj( Akcja akcja ){
	switch (akcja)
	{
	case StanInfo::AkcjaWejsciowa:
		if(luaFuncIn_.empty())
			return true;
		lua_getglobal(L, luaFuncIn_.c_str());
		break;
	case StanInfo::AkcjaWyjsciowa:
		if(luaFuncOut_.empty())
			return true;
		lua_getglobal(L, luaFuncOut_.c_str());
		break;
	case StanInfo::AkcjaWewnetrzna:
		if(luaFuncInside_.empty())
			return true;
		lua_getglobal(L, luaFuncInside_.c_str());
		break;
	default:
		return false;
	}

    if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
		std::stringstream ss;
		ss << "Failed to run script:" << lua_tostring(L, -1) << std::endl;
		Log::pobierzInstancje().loguj(Log::Error,ss.str());
		return false;
    }
	return true;
}

StanInfo::~StanInfo(void)
{
	lua_close(L);
}


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