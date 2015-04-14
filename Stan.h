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
		* \param[in] info - Obiekt opisuj�cy.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan(std::shared_ptr<StanInfo> info);

		/**
		* \brief Konstruktor kopiuj�cy.
		*
		* Konstruktor kopuj�cy ze zmian� obiektu opisowego.
		* \param[in] obiekt - Obiekt �r�d�owy.
		* \param[in] info - Obiekt opisuj�cy.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		Stan(const Stan& obiekt, std::shared_ptr<StanInfo> info);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		~Stan() = default;

		/**
		* \brief Metoda wej�cia.
		*
		* Metoda wykonywana w momencie wej�cia do stanu.
		* \return Zwracana jest warto�� true, je�eli wykonanie sie powiedzie. Zwracana jest warto�� false w przypadku wyst�pienia b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool akcjaWejscia();

		/**
		* \brief Metoda wewn�trzna.
		*
		* Metoda wykonywana w momencie ponownego wej�cia do tego samego stanu.
		* \return Zwracana jest warto�� true, je�eli wykonanie sie powiedzie. Zwracana jest warto�� false w przypadku wyst�pienia b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool akcjaWewnetrzna();

		/**
		* \brief Metoda wyj�cia.
		*
		* Metoda wykonywana w momencie wyj�cia ze stanu.
		* \return Zwracana jest warto�� true, je�eli wykonanie sie powiedzie. Zwracana jest warto�� false w przypadku wyst�pienia b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool akcjaWyjscia();

		STyp::Identyfikator id_; /// Identyfikator stanu.
		int numer_; /// Numer dodatkowy.
		KrokCzasu dt_; /// Krok czasu. U�ywany w w�tku graficznym.
		std::vector< STyp::Identyfikator > listaEkranow_; /// Lista ekran�w. U�ywana w w�tku graficznym.

		/**
		* \brief Operator por�wnania.
		*
		* Operator por�wnania.
		* \param[in] stan - Stan do por�wnania.
		* \return Zwracana jest warto�� true, je�eli obiektu s� r�wnowa�ne. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool operator==(const Stan& stan)const;

		/**
		* \brief Operator por�wnania.
		*
		* Operator por�wnania.
		* \param[in] zdarzenie - Zdarzenie do por�wnania.
		* \return Zwracana jest warto�� true, je�eli obiektu s� r�wnowa�ne. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool operator==(const Zdarzenie & zdarzenie)const;

		/**
		* \brief Metoda pobieraj�ca opis stanu.
		*
		* Metoda pobieraj�ca obiekt opisuj�cy stan.
		* \return Zwracany jest wska�nik na aktualny obiekt opisuj�cy stan.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<StanInfo> opisStanu() const;
	private:
		std::shared_ptr<StanInfo> info_; /// Obiekt opisuj�cy stan.
	};
};

