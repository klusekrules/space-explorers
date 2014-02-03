#pragma once
#include "TypyProste\Wyjatek.h"
namespace SpEx{
	/**
	* Wyj¹tek informuje, ¿e klasa zosta³a niepoprawnie zainicjalizowana lub w ogóle nie zosta³a zainicjalizowana.
	*/
	class NiezainicjalizowanaKlasa :
		virtual public SLog::LoggerInterface,
		public STyp::Wyjatek
	{
	public:
		static const STyp::Identyfikator idNiezainicjalizowanaKlasa;

		NiezainicjalizowanaKlasa(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Tekst& tNazwa);
		virtual ~NiezainicjalizowanaKlasa(void) = default;

		const STyp::Tekst& getNazwaKlasy() const;
		void setNazwaKlasy(const STyp::Tekst&);

		STyp::Tekst generujKomunikat() const override;

		std::string napis() const override;

	private:
		STyp::Tekst nazwaKlasy;

		static const STyp::Tekst tytulNiezainicjalizowanaKlasa;
		static const STyp::Tekst trescNiezainicjalizowanaKlasa;
	};
}
