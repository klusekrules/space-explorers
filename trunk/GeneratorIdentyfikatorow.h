#pragma once
#include <string>
#include <unordered_map>
#include "TypyProste\TypyProste.h"

namespace SpEx{
	/**
	* \brief Klasa pomocnicza mapuj�ca identyfikatory.
	*
	* Klasa mapuje identyfikatory znakowe na kolejne identyfikatory liczbowe.
	* \author Daniel Wojdak
	* \version 2
	* \date 05-08-2014
	*/
	class GeneratorIdentyfikatorow
	{
	public:
		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		GeneratorIdentyfikatorow() = default;

		/**
		* \brief Domy�lny destruktor.
		* 
		* Domylny destruktor.
		*/
		~GeneratorIdentyfikatorow() = default;

		/**
		* \brief Metoda mapuj�ca identyfikator.
		*
		* Metoda mapuje identyfikator tekstowy na identyfikator liczbowy. Je�eli identyfikator zosta� wczesniej zmapowany to jest zwracany numer mu przypisany.
		* \param[in] napis - Tekstowy identyfikator.
		* \param[out] id - Numer odpowiadaj�cy tekstowemu identyfikatorowi.
		* \return Zwracana jest warto�c true, je�eli pierwszy raz odwo�ano si� do identyfikatora. Zwracana jest warto�c false, je�eli jest to klejne odwo�anie do identyfikatora.
		* \throw Je�eli napis jest pusty wyrzucany jest wyj�tek.
		* \author Daniel Wojdak
		* \version 2
		* \date 05-08-2014
		*/
		bool pobierzIdentyfikator(const std::string& napis, STyp::Identyfikator& id);

		/**
		* \brief Metoda pobieraj�ca identyfikator tekstowy.
		*
		* Metoda pobiera identyfikator tekstowy odpowiadaj�cy zmapowanej warto�ci liczbowej.
		* \param[in] identyfikator - Liczbowy identyfikator.
		* \return Je�eli istnieje odpowiednie powi�zanie identyfikator�w swracany jest identyfikator tekstowy. Je�eli nie zwracany jest pusty napis.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::string pobierzNapis(const STyp::Identyfikator& identyfikator) const;

	private:
		typedef std::vector<std::string> Kontener; /// Typ kontenera mapuj�cego identyfikatory.
		Kontener mapa_; /// Kontener przechowuj�cy mapowanie.

	};
};
