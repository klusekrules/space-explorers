#pragma once
#include "MetodaRPC.h"

namespace SpEx{
	class InicjujLogowanieRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		static const std::string NazwaTypu_;
		friend class std::_Ref_count_obj<InicjujLogowanieRPC>;

		virtual ~InicjujLogowanieRPC() = default;		
		std::string napis() const override;

	private:
		using MetodaRPC::MetodaRPC;

		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool przygotowanieDoWyslania() override;
		bool obslugaOdpowiedzi(const Json::Value &) override;
	};
}
