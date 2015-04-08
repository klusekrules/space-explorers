#pragma once
#include <thread>
#include <atomic>
#include <mutex>
#include "Utils\NonCopyable.h"
#include "Utils\NonMoveable.h"
#include "TypyProste\Wyjatek.h"

namespace SpEx{

	/**
	* \brief Klasa w�tku.
	*
	* Klasa tworz�ca nowy w�tek aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 10-07-2014
	*/
	class Watek
		: se::NonCopyable, se::NonMoveable
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] wstrzymany - Informacje o stanie w�tku po uruchomieniu.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		Watek(bool wstrzymany);

		/**
		* \brief Destruktor.
		*
		* Destruktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		virtual ~Watek(void);

		/**
		* \brief Metoda oczekuj�ca na zko�czenie w�tku.
		*
		* Metoda zawiesza aktualny w�tek i oczekuje na zako�czenie w�tku reprezentowanego przez obiekt.
		* \return Zwracana jest warto�� true, je�eli w�tek si� zako�czy�. Zwracana jest warto�c false, je�eli nie mo�na czekac na zako�czenie w�tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		bool czekajNaZakonczenie();

		/**
		* \brief Metoda odblokowuj�ca w�tek.
		*
		* Metoda odblokowuje w�tek, je�eli by� on wstrzymany przy tworzeniu, przez podane infomacji do kontruktora.
		* \warning Metoda musiby� wywo�ana w tym samym w�tku co konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void odblokuj();

		/**
		* \brief Metoda ��daj�ca zako�czenia w�tku.
		*
		* Metoda pomocnicza przy rozsze�aniu funkcjonalno�ci. Pomaga przekaza� infomacje, �e w�tek powinien zako�czy� swoje dzia�anie.
		* Akcja jaka zostanie podj�ta, zale�y od implementacji funkcji g��wnej w�tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void zakoncz();

		/**
		* \brief Metoda informuj�ca czy w�tek zosta� zako�czony.
		*
		* Metoda informuje czy w�tek zako�czy� dzia�anie.
		* Akcja jaka zostanie podj�ta, zale�y od implementacji funkcji g��wnej w�tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const std::atomic<bool>& zakonczony() const;

		/**
		* \brief Metoda informuj�ca czy wyst�pi� b��d.
		*
		* Metoda pomocnicza przy rozsze�aniu funkcjonalno�ci. Pozwala na poinformowanie o wyst�pieniu b��du podczas dzia�ania w�tku i powodu jego zako�czenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const std::atomic<bool>& blad() const;

		/**
		* \brief Metoda pobieraj�ca informacje o wyj�tku.
		*
		* Metoda pomocnicza przy rozsze�aniu funkcjonalno�ci. Pozwala na pobranie informacji o wyj�tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const STyp::Wyjatek& bladInfo() const;

	protected:
		std::atomic<bool> zakoncz_; /// ��danie zako�czenia wykonywania w�tku.
		std::mutex wstrzymany_; /// Mutex wstrzymuj�cy dzia�anie w�tku tu� przed uruchomieniem funkcji g��wnej.
		std::atomic<bool> zakonczony_; /// Informacja czy zako�czono dzia�anie w�tku.

		std::atomic<bool> blad_; /// Informacja czy wyj�tek zosta� ustawiony.
		STyp::Wyjatek bladInfo_; /// Wyj�tek jaki zosta� ustawiony przez w�tek.

		/**
		* \brief Metoda ustawiaj�ca wyj�tek.
		*
		* Metoda pomocnicza przy rozsze�aniu funkcjonalno�ci. Metoda ustawia informacje o b��dzie.
		* \param[in] info - Obiekt wyj�tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void ustawBlad(const STyp::Wyjatek& info);

		/**
		* \brief G��wna funkcja w�tku.
		*
		* G��wna funkcja w�tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		virtual void wykonuj();

		/**
		* \brief Metoda informuj�ca o �adaniu zako�czenia w�tku.
		*
		* Metoda pomocnicza przy rozsze�aniu funkcjonalno�ci. Metoda pobiera informacje o ��daniu zako�czenia dzia�ania w�tku.
		* \return Zwracana jest warto�� true, je�eli wys�ano ��danie. Zwracana jest warto�� false, je�eli nie wys�ano ��dania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const std::atomic<bool>& czyZakonczyc() const;
		std::thread* uchwyt_; /// Wska�nik na obiekt w�tku.

		/**
		* \brief Metoda techniczna wywo�uj�ca g��wn� funkcj� w�tku.
		*
		* Metoda techniczna wywo�uj�ca g��wn� funkcj� w�tku. Zapewnia poprawne zako�czenie w�tku oraz wstrzymanie przy starcie.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void funkcjaWatku();
	};
};

