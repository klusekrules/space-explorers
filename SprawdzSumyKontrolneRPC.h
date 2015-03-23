#pragma once
#include "MetodaRPC.h"

namespace SpEx{
	class SprawdzSumyKontrolneRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		static const std::string NazwaTypu_;
		friend class std::_Ref_count_obj<SprawdzSumyKontrolneRPC>;

		virtual ~SprawdzSumyKontrolneRPC() = default;
		
		std::string napis() const override;

	private:
		using MetodaRPC::MetodaRPC;
		
		bool inicjuj() override;
		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool obslugaOdpowiedzi(const Json::Value &) override;
	};
};
