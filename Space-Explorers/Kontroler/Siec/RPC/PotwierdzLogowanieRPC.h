#pragma once
#include "MetodaRPC.h"

namespace SpEx{
	class PotwierdzLogowanieRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		static const std::string NazwaTypu_;
		friend class std::_Ref_count_obj<PotwierdzLogowanieRPC>;

		virtual ~PotwierdzLogowanieRPC() = default;
		std::string napis() const override;

	private:
		using MetodaRPC::MetodaRPC;

		void obslugaZadania(const Json::Value &, Json::Value&) override;		
		bool obslugaOdpowiedzi(const Json::Value &) override;
		
	};
}
