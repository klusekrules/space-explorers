#pragma once
#include "MetodaRPC.h"

namespace SpEx{
	class PotwierdzLogowanieRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		friend class std::_Ref_count_obj<PotwierdzLogowanieRPC>;
		static bool RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger);
		static std::shared_ptr<MetodaRPC> TworzObiekt(const Json::Value &, Klient&);

		virtual ~PotwierdzLogowanieRPC() = default;
		std::string napis() const override;

	private:

		PotwierdzLogowanieRPC(Klient&);
		void obslugaZadania(const Json::Value &, Json::Value&) override;		
		bool obslugaOdpowiedzi(const Json::Value &) override;
		
	};
}
