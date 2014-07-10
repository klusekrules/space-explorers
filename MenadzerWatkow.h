#pragma once
#include "WatekZarzadzany.h"
namespace SpEx{

	/**
	* \brief Klasa menad�era w�tk�w.
	*
	* Klasa zarz�dza list� w�tk�w do wykonywania zleconych zada�.
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
		* Klasa u�atwia przechowanie zarz�dzanie pojedy�czym w�tkiem.
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
			* \brief Konstruktor przenosz�cy.
			*
			* Konstruktor przenosz�cy.
			* \param[inout] obiekt - Obiekt �r�d�owy.
			* \author Daniel Wojdak
			* \version 1
			* \date 10-07-2014
			*/
			ElementListy(ElementListy&& obiekt);

			/**
			* \brief Metoda dodaj�ca zadanie.
			*
			* Metoda dodaje nowe zadanie do kolejki zada� w w�tku.
			* \param[inout] zadanie - Zlecone zadanie.
			* \author Daniel Wojdak
			* \version 1
			* \date 10-07-2014
			*/
			void dodajZadanie(Zadanie& zadanie);

		private:
			std::shared_ptr<WatekZarzadzany> watek_; /// W�tek wykonuj�cy zadania.
			std::promise<bool> sygnal_; /// Sygna� informuj�cy o przyj�ciu nowego zadania.
		};

		std::mutex mutaxPuliWatkow_; /// Mutex puli w�tk�w.
		std::vector<ElementListy> pulaWatkow_; /// Lista dostepnych w�tk�w.
		char numerWatku_ = 0; /// Numer w�tku do u�ycia.
	public:

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		MenadzerWatkow() = default;

		/**
		* \brief Metoda ustawiaj�ca ilo�� w�tk�w.
		*
		* Metoda usuwa aktualne w�tki i tworzy nowe w ilo�ci podanej w atrybucie.
		* \param[in] ilosc - Nowa ilo�� w�tk�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void ustawLiczbeWatkow(unsigned char ilosc);

		/**
		* \brief Metoda dodaj�ca zadanie.
		*
		* Metoda przypisuje zadanie do wyznaczonego w�tku.
		* \param[inout] zadanie - Zlecone zadanie.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void dodajZadanie(Zadanie& zadanie);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~MenadzerWatkow() = default;
	};
};

