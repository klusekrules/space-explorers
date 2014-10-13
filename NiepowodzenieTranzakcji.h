#pragma once
#include "TypyProste\Wyjatek.h"

namespace SpEx{
	/**
	* \brief Wyj¹tek b³êdu krytycznego wykonywanej tranzakcji.
	*
	* Wyj¹tek zostaje wyrzucony kiedy w trakcie cofania tranzakcji wyst¹pi³ wyj¹tek, b¹dŸ funkcja siê nie powiod³a.
	*/
	class NiepowodzenieTranzakcji :
		public STyp::Wyjatek,
		virtual public SLog::LoggerInterface
	{
	public:
		static const STyp::Identyfikator domyslnyNiepowodzenieTranzakcjiID; /// Domyœlna wartoœæ id klasy.

		/**
		* \brief Konstruktor.
		*
		* \param[in] tPlik - Plik wyst¹pienia wyj¹tku.
		* \param[in] funkcja - Nazwa funkcji w której zosta³ wygenerowany wyj¹tek.
		* \param[in] iLinia - Linia wytapienia wyj¹tku.
		* \param[in] tranzakcja - Opis tranzakcji dla ktorej wyst¹pi³ wyj¹tek.
		*/
		NiepowodzenieTranzakcji(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia, const STyp::Tekst& debug, const STyp::Tekst& tranzakcja);

		/**
		* \brief Destruktor.
		*/
		virtual ~NiepowodzenieTranzakcji(void) = default;

		/**
		* \brief Metoda tworz¹ca komunikat opisuj¹cyh wyj¹tek.
		* \return Tekst opisuj¹cy wyj¹tek.
		*/
		STyp::Tekst generujKomunikat() const override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	protected:
		STyp::Tekst tranzakcja_; /// Opis tranzakcji

	private:
		static const STyp::Tekst domyslnyNiepowodzenieTranzakcjiTytul; /// Domyœlny tytu³ wyjatku
		static const STyp::Tekst domyslnyNiepowodzenieTranzakcjiTresc; /// Domyœlna treœæ wyj¹tku
	};
}
