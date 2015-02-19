#pragma once
#include "MetodaRPC.h"
namespace SpEx{
	class InicjujLogowanieRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		InicjujLogowanieRPC(Klient&);
		virtual ~InicjujLogowanieRPC() = default;

		static bool RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger);
		static std::shared_ptr<MetodaRPC> TworzObiekt(const Json::Value &, Klient&);

		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool inicjalizacjaParametrow() override;

		bool obslugaOdpowiedzi(const Json::Value &) override;
		std::string napis() const override;

		std::string login_;
	};
}
