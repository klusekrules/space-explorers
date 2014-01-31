#pragma once
#include "stdafx.h"
#include "Logger\LoggerInterface.h"
#include "LuaSkrypt.h"
#include "ZdarzenieInfo.h"

class StanInfo :
	virtual public SLog::LoggerInterface
{
public:
	enum Akcja{
		AkcjaWejsciowa,
		AkcjaWyjsciowa,
		AkcjaWewnetrzna
	};

	StanInfo( XmlBO::ElementWezla );
	virtual ~StanInfo(void) = default;

	bool wykonaj( Akcja );

	const STyp::Identyfikator& pobierzIdentyfikator() const;

	std::shared_ptr<ZdarzenieInfo> pobierzZdarzenie(const STyp::Identyfikator&) const;

	std::string napis() const override;

private:
	LuaSkrypt skrypt_;
	std::string luaFuncIn_;
	std::string luaFuncOut_;
	std::string luaFuncInside_;
	std::string luaFile_;
	STyp::Identyfikator id_;
	std::map < STyp::Identyfikator, std::shared_ptr<ZdarzenieInfo> > zdarzenia_;
};

