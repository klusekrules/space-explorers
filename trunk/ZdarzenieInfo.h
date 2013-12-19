#pragma once
#include "stdafx.h"
#include "Logger\LoggerInterface.h"
#include "tinyxml2.h"
#include "LuaSkrypt.h"
#include "Identyfikator.h"

class ZdarzenieInfo :
	virtual public LoggerInterface
{
public:
	ZdarzenieInfo( tinyxml2::XMLElement* wezel );
	virtual ~ZdarzenieInfo(void);

	bool wykonaj();

	const Identyfikator& pobierzIdentyfikator() const;
	
	std::shared_ptr< Identyfikator > pobierzStan() const;
	std::shared_ptr< int > pobierzNumer() const;
	
	std::string napis() const override;

private:
	LuaSkrypt skrypt_;
	std::string luaFuncInside_;
	std::string luaFile_;
	Identyfikator id_;
	std::shared_ptr < Identyfikator > nastepnyStan_;
	std::shared_ptr < int > nastepnyNumer_;

};

