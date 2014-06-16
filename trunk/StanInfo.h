#pragma once
#include "Logger\LoggerInterface.h"
#include "Skrypt.h"
#include "ZdarzenieInfo.h"
#include <map>

namespace SpEx{
	class StanInfo :
		virtual public SLog::LoggerInterface
	{
	public:
		enum Akcja{
			AkcjaWejsciowa,
			AkcjaWyjsciowa,
			AkcjaWewnetrzna
		};

		StanInfo(XmlBO::ElementWezla);
		virtual ~StanInfo(void) = default;

		bool wykonaj(Akcja);

		const STyp::Identyfikator& pobierzIdentyfikator() const;

		std::shared_ptr<ZdarzenieInfo> pobierzZdarzenie(const STyp::Identyfikator&) const;

		std::string napis() const override;

	private:
		std::shared_ptr<Skrypt> skrypt_ = nullptr;
		std::string luaFuncIn_;
		std::string luaFuncOut_;
		std::string luaFuncInside_;
		std::string luaFile_;
		STyp::Identyfikator id_;
		std::map < STyp::Identyfikator, std::shared_ptr<ZdarzenieInfo> > zdarzenia_;
	};
};
