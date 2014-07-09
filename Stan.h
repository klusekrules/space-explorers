#pragma once
#include "StanInfo.h"
#include "Zdarzenie.h"
#include <chrono>

namespace SpEx{

	/**
	* \brief Klasa stanu
	*
	* Klasa zawiera informacje o stanie.
	* \author Daniel Wojdak
	* \version 1
	* \date 09-07-2014
	*/
	class Stan
	{
	public:
		typedef std::chrono::duration<long double, std::milli> KrokCzasu; /// Typ czasu.
		
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] info - Obiekt opisuj¹cy.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan(std::shared_ptr<StanInfo> info);

		/**
		* \brief Konstruktor kopiuj¹cy.
		*
		* Konstruktor kopuj¹cy ze zmian¹ obiektu opisowego.
		* \param[in] obiekt - Obiekt Ÿród³owy.
		* \param[in] info - Obiekt opisuj¹cy.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan(const Stan& obiekt, std::shared_ptr<StanInfo> info);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		~Stan() = default;

		/**
		* \brief Metoda wejœcia.
		*
		* Metoda wykonywana w momencie wejœcia do stanu.
		* \return Zwracana jest wartoœæ true, je¿eli wykonanie sie powiedzie. Zwracana jest wartoœæ false w przypadku wyst¹pienia b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool akcjaWejscia();

		/**
		* \brief Metoda wewnêtrzna.
		*
		* Metoda wykonywana w momencie ponownego wejœcia do tego samego stanu.
		* \return Zwracana jest wartoœæ true, je¿eli wykonanie sie powiedzie. Zwracana jest wartoœæ false w przypadku wyst¹pienia b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool akcjaWewnetrzna();

		/**
		* \brief Metoda wyjœcia.
		*
		* Metoda wykonywana w momencie wyjœcia ze stanu.
		* \return Zwracana jest wartoœæ true, je¿eli wykonanie sie powiedzie. Zwracana jest wartoœæ false w przypadku wyst¹pienia b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool akcjaWyjscia();

		STyp::Identyfikator id_; /// Identyfikator stanu.
		int numer_; /// Numer dodatkowy.
		KrokCzasu dt_; /// Krok czasu. U¿ywany w w¹tku graficznym.
		std::vector< STyp::Identyfikator > listaEkranow_; /// Lista ekranów. U¿ywana w w¹tku graficznym.

		/**
		* \brief Operator porównania.
		*
		* Operator porównania.
		* \param[in] stan - Stan do porównania.
		* \return Zwracana jest wartoœæ true, je¿eli obiektu s¹ równowa¿ne. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool operator==(const Stan& stan)const;

		/**
		* \brief Operator porównania.
		*
		* Operator porównania.
		* \param[in] zdarzenie - Zdarzenie do porównania.
		* \return Zwracana jest wartoœæ true, je¿eli obiektu s¹ równowa¿ne. Zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool operator==(const Zdarzenie & zdarzenie)const;

		/**
		* \brief Metoda pobieraj¹ca opis stanu.
		*
		* Metoda pobieraj¹ca obiekt opisuj¹cy stan.
		* \return Zwracany jest wskaŸnik na aktualny obiekt opisuj¹cy stan.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<StanInfo> opisStanu() const;
	private:
		std::shared_ptr<StanInfo> info_; /// Obiekt opisuj¹cy stan.
	};
};

