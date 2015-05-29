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

		void ustawListePlikow( const std::vector<std::string>& lista);

		virtual ~SprawdzSumyKontrolneRPC() = default;
		
		std::string napis() const override;

	private:
		using MetodaRPC::MetodaRPC;

		const std::vector<std::string> * lista_ = nullptr;
		
		bool przygotowanieDoWyslania() override;
		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool obslugaOdpowiedzi(const Json::Value &) override;
	};
};
