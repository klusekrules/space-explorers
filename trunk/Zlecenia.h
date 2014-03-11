#pragma once
#include "Zlecenie.h"
#include "PodstawoweParametry.h"
#include <functional>
namespace SpEx{
	class ZlecenieUstawIdentyfikatorPlanety :
		public Zlecenie < STyp::Identyfikator, std::shared_ptr< SpEx::PodstawoweParametry > >,
		virtual public SLog::LoggerInterface
	{
	private:
		STyp::Identyfikator staryIdentyfikator_;

		bool ustawIdentyfikator(STyp::Identyfikator& id, std::shared_ptr< SpEx::PodstawoweParametry >& obiekt){
			staryIdentyfikator_ = obiekt->pobierzIdentyfikatorPlanety();
			obiekt->ustawIdentyfikatorPlanety(id);
			return true;
		}

		bool cofnijUstawIdentyfikator(STyp::Identyfikator& id, std::shared_ptr< SpEx::PodstawoweParametry >& obiekt){
			obiekt->ustawIdentyfikatorPlanety(staryIdentyfikator_);
			return true;
		}
	public:
		ZlecenieUstawIdentyfikatorPlanety(STyp::Identyfikator& identyfikator, std::shared_ptr< SpEx::PodstawoweParametry >& obiekt)
			: Zlecenie(identyfikator, obiekt, bind(&ZlecenieUstawIdentyfikatorPlanety::ustawIdentyfikator, this, std::placeholders::_1, std::placeholders::_2),
			bind(&ZlecenieUstawIdentyfikatorPlanety::cofnijUstawIdentyfikator, this, std::placeholders::_1, std::placeholders::_2))
		{}

		virtual ~ZlecenieUstawIdentyfikatorPlanety() = default;

		std::string napis() const override{
			SLog::Logger str(NAZWAKLASY(ZlecenieUstawIdentyfikatorPlanety));
			str.dodajKlase(Zlecenie::napis());
			str.dodajPole(NAZWAPOLA(staryIdentyfikator_), staryIdentyfikator_);
			return str.napis();
		}
	};
};
