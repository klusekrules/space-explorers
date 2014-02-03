#pragma once
#include "TypyProste\Wyjatek.h"
#include <vector>

namespace SpEx{
	/**
	* Wyj¹tek informuje, ¿e parametry maj¹ nie poprawne wartoœci.
	*/
	class NiepoprawneParametryFunkcji :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idNiepoprawneParametryFunkcji;

		template< class... V >
		NiepoprawneParametryFunkcji(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const V&... tail)
			: Wyjatek(tPlik, iLinia, idNiepoprawneParametryFunkcji, tytulNiepoprawneParametryFunkcji, trescNiepoprawneParametryFunkcji)
		{
			std::vector< std::string > a;
			std::stringstream tmp;
			step(a, tail...);
			for (auto s : a){
				tmp << "Parametr - [ " << s << " ] \n";
			}
			parametry = tmp.str();
		}

		virtual ~NiepoprawneParametryFunkcji() = default;

		const STyp::Tekst& getParametry() const;
		void setParametry(const STyp::Tekst& wwTresc);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:

		template< class... V >
		static void step(std::vector< std::string >& v, const LoggerInterface &c, const V&... tail){
			v.push_back(c.napis());
			step(v, tail...);
		}

		static void step(std::vector< std::string >& v, const LoggerInterface &c){
			v.push_back(c.napis());
		}

		STyp::Tekst parametry;
		static const STyp::Tekst tytulNiepoprawneParametryFunkcji;
		static const STyp::Tekst trescNiepoprawneParametryFunkcji;
	};
}
