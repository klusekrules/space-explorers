#pragma once
#include "stdafx.h"
#include "Logger\LoggerInterface.h"
#include "LuaSkrypt.h"
#include "Parser\XmlBO.h"

class ZdarzenieInfo :
	virtual public SLog::LoggerInterface
{
public:
	ZdarzenieInfo( XmlBO::ElementWezla wezel );
	virtual ~ZdarzenieInfo(void) = default;

	bool wykonaj();

	const STyp::Identyfikator& pobierzIdentyfikator() const;
	
	std::shared_ptr< STyp::Identyfikator > pobierzStan() const;
	std::shared_ptr< int > pobierzNumer() const;
	
	std::string napis() const override;

private:
	LuaSkrypt skrypt_;
	std::string luaFuncInside_;
	std::string luaFile_;
	STyp::Identyfikator id_;
	std::shared_ptr < STyp::Identyfikator > nastepnyStan_;
	std::shared_ptr < int > nastepnyNumer_;

};

