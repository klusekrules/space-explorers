#pragma once
#include <memory>
#include "TypyProste\TypyProste.h"

namespace SpEx{
	class Zasob
	{
	public:
		typedef std::shared_ptr<Zasob> SharedPtr;
		typedef std::weak_ptr<Zasob> WeakPtr;

		Zasob( const STyp::Identyfikator& id );
		virtual ~Zasob();

		const STyp::Identyfikator& pobierzIdentyfikator() const;

		virtual bool inicjalizuj() = 0;

	private:
		STyp::Identyfikator identyfikator_;
	};
};
