#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	/**
	* Klasa bazowa nadbudowuj¹ca wyj¹tki z biblioteki stl.
	*/
	class WyjatekSTL :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idWyjatekSTL;

		WyjatekSTL(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const std::exception&, const STyp::Tekst& = STyp::Tekst());
		WyjatekSTL(const WyjatekSTL&);
		virtual ~WyjatekSTL() = default;

		const STyp::Tekst& getPowod() const;
		void setPowod(const STyp::Tekst&);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst powod;

		static const STyp::Tekst tytulWyjatekSTL;
		static const STyp::Tekst trescWyjatekSTL;
	};
}
