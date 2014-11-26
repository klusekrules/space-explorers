#pragma once
#include "stdafx.h"
#include "StanInfo.h"
#include "Zdarzenie.h"
namespace SpEx{
	class Stan
	{
	public:
		typedef std::chrono::duration<long double, std::milli> KrokCzasu;

		Stan(std::shared_ptr<StanInfo>);
		~Stan() = default;

		bool akcjaWejscia();
		bool akcjaWewnetrzna();
		bool akcjaWyjscia();

		STyp::Identyfikator id_;
		int numer_;
		KrokCzasu dt_;
		std::vector< STyp::Identyfikator > listaEkranow_;
		bool operator==(const Stan&)const;
		bool operator==(const Zdarzenie &)const;
		std::shared_ptr<StanInfo> opisStanu() const;
	private:
		std::shared_ptr<StanInfo> info_;
	};
};
