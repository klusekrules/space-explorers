#pragma once
#include "Zadanie.h"
#include "Watek.h"
#include <future>
#include <list>

namespace SpEx{

	/**
	* \brief Klasa w¹tku obs³uguj¹cego zadania.
	*
	* Klasa w¹tku do którego mo¿na wysy³aæ zadania do zlecenia.
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
		* \param[in] wykonuj - Sygna³ uruchamiaj¹cy w¹tek.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		WatekZarzadzany(std::future<bool> wykonuj);

		/**
		* \brief Metoda dodaje zadanie do w¹tku.
		*
		* Metoda dodaje zadanie do listy zadañ w¹tku.
		* \param[inout] zadanie - Zadanie do wykonania.
		* \param[in] noweZadanie - Sygna³ rozpoczynaj¹cy wykonywanie zadania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void dodajZadanie(Zadanie& zadanie, std::future<bool> noweZadanie);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~WatekZarzadzany() = default;

	protected:

		/**
		* \brief G³ówna funkcja w¹tku.
		*
		* G³ówna funkcja w¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void wykonuj() override;

	private:

		std::mutex mutexNastepneNoweZadanie_; /// Mutex dostêpu do sygna³u oczekiwania.
		std::future<bool> nastepneNoweZadanie_; /// Nastêpny sygna³ oczekiwania.
		std::future<bool> noweZadanie_; /// Aktualny sygna³ oczekiwania.

		std::mutex mutexZadanie_; /// Mutex dostêpu do listy zadañ.
		std::list<Zadanie> zadania_; /// Lista z zadaniami do wykonania.

		/**
		* \brief Metoda pobiera zadanie.
		*
		* Metoda pobiera zadanie z listy zadañ w¹tku.
		* \param[out] zadanie - Zadanie do wykonania.
		* \return Zwracana jest wartoœæ true, je¿eli pobrano zadanie. Zwracana jest wartoœæ false, je¿eli nie ma oczekuj¹cych zadañ do wykonania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		bool pobierzZadanie(Zadanie& zadanie);

		/**
		* \brief Metoda ustawiaj¹ca sygna³ oczekiwania.
		*
		* Metoda pomocnicza ustawiaj¹ca sygna³ oczekiwania na przyjœcie kolejnego zadania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void ustawOczekiwanieNaNoweZadanie();
	};

};