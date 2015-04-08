#pragma once
#include "Zadanie.h"
#include "Watek.h"
#include <future>
#include <list>

namespace SpEx{

	/**
	* \brief Klasa w�tku obs�uguj�cego zadania.
	*
	* Klasa w�tku do kt�rego mo�na wysy�a� zadania do zlecenia.
	* \author Daniel Wojdak
	* \version 1
	* \date 10-07-2014
	*/
	class WatekZarzadzany
		: public Watek
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] wykonuj - Sygna� uruchamiaj�cy w�tek.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		WatekZarzadzany(std::future<bool> wykonuj);

		/**
		* \brief Metoda dodaje zadanie do w�tku.
		*
		* Metoda dodaje zadanie do listy zada� w�tku.
		* \param[inout] zadanie - Zadanie do wykonania.
		* \param[in] noweZadanie - Sygna� rozpoczynaj�cy wykonywanie zadania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void dodajZadanie(Zadanie& zadanie, std::future<bool> noweZadanie);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~WatekZarzadzany() = default;

	protected:

		/**
		* \brief G��wna funkcja w�tku.
		*
		* G��wna funkcja w�tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void wykonuj() override;

	private:

		std::mutex mutexNastepneNoweZadanie_; /// Mutex dost�pu do sygna�u oczekiwania.
		std::future<bool> nastepneNoweZadanie_; /// Nast�pny sygna� oczekiwania.
		std::future<bool> noweZadanie_; /// Aktualny sygna� oczekiwania.

		std::mutex mutexZadanie_; /// Mutex dost�pu do listy zada�.
		std::list<Zadanie> zadania_; /// Lista z zadaniami do wykonania.

		/**
		* \brief Metoda pobiera zadanie.
		*
		* Metoda pobiera zadanie z listy zada� w�tku.
		* \param[out] zadanie - Zadanie do wykonania.
		* \return Zwracana jest warto�� true, je�eli pobrano zadanie. Zwracana jest warto�� false, je�eli nie ma oczekuj�cych zada� do wykonania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		bool pobierzZadanie(Zadanie& zadanie);

		/**
		* \brief Metoda ustawiaj�ca sygna� oczekiwania.
		*
		* Metoda pomocnicza ustawiaj�ca sygna� oczekiwania na przyj�cie kolejnego zadania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void ustawOczekiwanieNaNoweZadanie();
	};

};