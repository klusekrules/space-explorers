#pragma once
#include "Fabrykator.h"

namespace SpEx{
	class EchoRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:

		static bool RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger);
		static std::unique_ptr<MetodaRPC> TworzObiekt(const Json::Value &, Klient&);

		EchoRPC(const PolaczenieTCP&);
		virtual ~EchoRPC() = default;

		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool inicjalizacjaParametrow() override;

		bool obslugaOdpowiedzi(const Json::Value &) override;
		std::string napis() const override;

	};
}
