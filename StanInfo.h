#pragma once
#include "stdafx.h"
#include "Logger\LoggerInterface.h"
#include "parser\ticpp.h"
#include "lua.hpp"
#include "Identyfikator.h"
#include "ZdarzenieInfo.h"

class StanInfo :
	virtual public LoggerInterface
{
public:
	enum Akcja{
		AkcjaWejsciowa,
		AkcjaWyjsciowa,
		AkcjaWewnetrzna
	};

	StanInfo( TiXmlElement* );
	virtual ~StanInfo(void);

	bool wykonaj( Akcja );

	const Identyfikator& pobierzIdentyfikator() const;

	std::shared_ptr<ZdarzenieInfo> pobierzZdarzenie( const Identyfikator& ) const;

	std::string napis() const override;

private:
	lua_State *L;
	std::string luaFuncIn_;
	std::string luaFuncOut_;
	std::string luaFuncInside_;
	std::string luaFile_;
	Identyfikator id_;
	std::map < Identyfikator , std::shared_ptr<ZdarzenieInfo> > zdarzenia_;
};

