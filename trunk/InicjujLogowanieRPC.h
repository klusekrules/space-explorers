#pragma once
#include "MetodaRPC.h"

namespace SpEx{
	class InicjujLogowanieRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		friend class std::_Ref_count_obj<InicjujLogowanieRPC>;
		static bool RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger);
		static std::shared_ptr<MetodaRPC> TworzObiekt(const Json::Value &, Klient&);

		virtual ~InicjujLogowanieRPC() = default;		
		std::string napis() const override;

	private:
		InicjujLogowanieRPC(Klient&);

		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool przygotowanieDoWyslania() override;
		bool obslugaOdpowiedzi(const Json::Value &) override;
	};
}
