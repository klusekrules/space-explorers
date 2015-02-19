#pragma once
#include "Fabrykator.h"

namespace SpEx{
	class ZalogujRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:

		ZalogujRPC(Klient&);
		virtual ~ZalogujRPC() = default;

		static bool RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger);
		static std::shared_ptr<MetodaRPC> TworzObiekt(const Json::Value &, Klient&);
		
		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool inicjalizacjaParametrow() override;

		bool obslugaOdpowiedzi(const Json::Value &) override;
		std::string napis() const override;
		
	};
}
