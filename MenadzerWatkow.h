#pragma once
#include "WatekZarzadzany.h"
namespace SpEx{

	/**
	* \brief Klasa menad¿era w¹tków.
	*
	* Klasa zarz¹dza list¹ w¹tków do wykonywania zleconych zadañ.
	* \author Daniel Wojdak
	* \version 1
	* \date 10-07-2014
	*/
	class MenadzerWatkow
		: se::NonCopyable, se::NonMoveable
	{
	private:

		/**
		* \brief Klasa pomocnicza.
		*
		* Klasa u³atwia przechowanie zarz¹dzanie pojedyñczym w¹tkiem.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		class ElementListy
			: se::NonCopyable
		{
		public:

			/**
			* \brief Konstruktor.
			*
			* Konstruktor.
			* \author Daniel Wojdak
			* \version 1
			* \date 10-07-2014
			*/
			ElementListy();

			/**
			* \brief Destruktor.
			*
			* Destruktor.
			* \author Daniel Wojdak
			* \version 1
			* \date 10-07-2014
			*/
			~ElementListy();

			/**
			* \brief Konstruktor przenosz¹cy.
			*
			* Konstruktor przenosz¹cy.
			* \param[inout] obiekt - Obiekt ¿ród³owy.
			* \author Daniel Wojdak
			* \version 1
			* \date 10-07-2014
			*/
			ElementListy(ElementListy&& obiekt);

			/**
			* \brief Metoda dodaj¹ca zadanie.
			*
			* Metoda dodaje nowe zadanie do kolejki zadañ w w¹tku.
			* \param[inout] zadanie - Zlecone zadanie.
			* \author Daniel Wojdak
			* \version 1
			* \date 10-07-2014
			*/
			void dodajZadanie(Zadanie& zadanie);

		private:
			std::shared_ptr<WatekZarzadzany> watek_; /// W¹tek wykonuj¹cy zadania.
			std::promise<bool> sygnal_; /// Sygna³ informuj¹cy o przyjœciu nowego zadania.
		};

		std::mutex mutaxPuliWatkow_; /// Mutex puli w¹tków.
		std::vector<ElementListy> pulaWatkow_; /// Lista dostepnych w¹tków.
		char numerWatku_ = 0; /// Numer w¹tku do u¿ycia.
	public:

		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		MenadzerWatkow() = default;

		/**
		* \brief Metoda ustawiaj¹ca iloœæ w¹tków.
		*
		* Metoda usuwa aktualne w¹tki i tworzy nowe w iloœci podanej w atrybucie.
		* \param[in] ilosc - Nowa iloœæ w¹tków.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void ustawLiczbeWatkow(unsigned char ilosc);

		/**
		* \brief Metoda dodaj¹ca zadanie.
		*
		* Metoda przypisuje zadanie do wyznaczonego w¹tku.
		* \param[inout] zadanie - Zlecone zadanie.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void dodajZadanie(Zadanie& zadanie);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~MenadzerWatkow() = default;
	};
};

