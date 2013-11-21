#include "ZdarzenieInfo.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

ZdarzenieInfo::ZdarzenieInfo( TiXmlElement* wezel )
	: L(luaL_newstate()), nastepnyStan_(nullptr), nastepnyNumer_(nullptr)
{
	if(wezel){
		int status;
		luaL_openlibs(L);
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

ZdarzenieInfo::~ZdarzenieInfo(void)
{
}

bool ZdarzenieInfo::wykonaj(){
	if(luaFuncInside_.empty())
		return true;
	
	lua_getglobal(L, luaFuncInside_.c_str());
		
    if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
		std::stringstream ss;
		ss << "Failed to run script:" << lua_tostring(L, -1) << std::endl;
		Log::pobierzInstancje().loguj(Log::Error,ss.str());
		return false;
    }
	return true;
}

const Identyfikator& ZdarzenieInfo::pobierzIdentyfikator() const{
	return id_;
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
