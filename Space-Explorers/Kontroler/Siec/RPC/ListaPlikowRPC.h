#pragma once
#include "MetodaRPC.h"

namespace SpEx{
	class ListaPlikowRPC :
		virtual public SLog::LoggerInterface,
		public MetodaRPC
	{
	public:
		static const std::string NazwaTypu_;
		friend class std::_Ref_count_obj<ListaPlikowRPC>;

		virtual ~ListaPlikowRPC() = default;

		const std::vector<std::string>& pobierzListePlikow() const;

		std::string napis() const override;
	private:

		using MetodaRPC::MetodaRPC;

		bool przygotowanieDoWyslania() override { wlaczAutoryzacje(); wlaczKompresje(); return true; }
		void obslugaZadania(const Json::Value &, Json::Value&) override;
		bool obslugaOdpowiedzi(const Json::Value &) override;

		std::vector<std::string> listaPlikow_;
	
	};
}