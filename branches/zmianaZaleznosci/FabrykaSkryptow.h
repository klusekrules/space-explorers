#pragma once
#include "NonCopyable.h"
#include "Skrypt.h"
#include "Parser\XmlBO.h"
#include "Logger\Log.h"
#include <map>

#define XML_ATRYBUT_TYP_SKRYPTU "typSkryptu"

namespace SpEx{
	class FabrykaSkryptow
		: public se::NonCopyable
	{
	public:
		typedef STyp::Tekst Identyfikator;
		typedef std::shared_ptr<Skrypt>(*KreatorSkryptu)(XmlBO::ElementWezla wezel);

		typedef bool(*RejestrujSkrypt)(FabrykaSkryptow& fabryka, SLog::Log& logger);

		std::shared_ptr<Skrypt> Tworz(XmlBO::ElementWezla wezel) const;

		std::shared_ptr<Skrypt> Tworz(const Identyfikator& identyfikator, XmlBO::ElementWezla wezel) const;

		bool rejestracjaSkryptu(const Identyfikator& identyfikator, KreatorSkryptu funkcja);

		FabrykaSkryptow() = default;

		virtual ~FabrykaSkryptow() = default;
	private:

		typedef std::map<Identyfikator, KreatorSkryptu> Callbacks;

		Callbacks callbacks_;

	};
}
