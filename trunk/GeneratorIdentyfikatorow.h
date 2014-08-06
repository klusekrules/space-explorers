#pragma once
#include <string>
#include <unordered_map>
#include "TypyProste\TypyProste.h"

namespace SpEx{
	/**
	* \brief Klasa pomocnicza mapuj¹ca identyfikatory.
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
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		GeneratorIdentyfikatorow() = default;

		/**
		* \brief Domyœlny destruktor.
		* 
		* Domylny destruktor.
		*/
		~GeneratorIdentyfikatorow() = default;

		/**
		* \brief Metoda mapuj¹ca identyfikator.
		*
		* Metoda mapuje identyfikator tekstowy na identyfikator liczbowy. Je¿eli identyfikator zosta³ wczesniej zmapowany to jest zwracany numer mu przypisany.
		* \param[in] napis - Tekstowy identyfikator.
		* \param[out] id - Numer odpowiadaj¹cy tekstowemu identyfikatorowi.
		* \return Zwracana jest wartoœc true, je¿eli pierwszy raz odwo³ano siê do identyfikatora. Zwracana jest wartoœc false, je¿eli jest to klejne odwo³anie do identyfikatora.
		* \throw Je¿eli napis jest pusty wyrzucany jest wyj¹tek.
		* \author Daniel Wojdak
		* \version 2
		* \date 05-08-2014
		*/
		bool pobierzIdentyfikator(const std::string& napis, STyp::Identyfikator& id);

		/**
		* \brief Metoda pobieraj¹ca identyfikator tekstowy.
		*
		* Metoda pobiera identyfikator tekstowy odpowiadaj¹cy zmapowanej wartoœci liczbowej.
		* \param[in] identyfikator - Liczbowy identyfikator.
		* \return Je¿eli istnieje odpowiednie powi¹zanie identyfikatorów swracany jest identyfikator tekstowy. Je¿eli nie zwracany jest pusty napis.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::string pobierzNapis(const STyp::Identyfikator& identyfikator) const;

	private:
		typedef std::vector<std::string> Kontener; /// Typ kontenera mapuj¹cego identyfikatory.
		Kontener mapa_; /// Kontener przechowuj¹cy mapowanie.

	};
};
