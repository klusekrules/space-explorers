#pragma once
#include "Fabrykator.h"

namespace SpEx{
	class ZalogujRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		static bool RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger);
		static std::unique_ptr<MetodaRPC> TworzObiekt(const Json::Value &, Klient&);
		
		ZalogujRPC(const PolaczenieTCP&);
		virtual ~ZalogujRPC() = default;

		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool inicjalizacjaParametrow() override;

		bool obslugaOdpowiedzi(const Json::Value &) override;
		std::string napis() const override;
	};
}
