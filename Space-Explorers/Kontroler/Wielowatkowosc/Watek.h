#pragma once
#include <thread>
#include <atomic>
#include <mutex>
#include "Utils\NonCopyable.h"
#include "Utils\NonMoveable.h"
#include "TypyProste\Wyjatek.h"

namespace SpEx{

	/**
	* \brief Klasa w¹tku.
	*
	* Klasa tworz¹ca nowy w¹tek aplikacji.
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
		* \param[in] wstrzymany - Informacje o stanie w¹tku po uruchomieniu.
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
		* \brief Metoda oczekuj¹ca na zkoñczenie w¹tku.
		*
		* Metoda zawiesza aktualny w¹tek i oczekuje na zakoñczenie w¹tku reprezentowanego przez obiekt.
		* \return Zwracana jest wartoœæ true, je¿eli w¹tek siê zakoñczy³. Zwracana jest wartoœc false, je¿eli nie mo¿na czekac na zakoñczenie w¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		bool czekajNaZakonczenie();

		/**
		* \brief Metoda odblokowuj¹ca w¹tek.
		*
		* Metoda odblokowuje w¹tek, je¿eli by³ on wstrzymany przy tworzeniu, przez podane infomacji do kontruktora.
		* \warning Metoda musibyæ wywo³ana w tym samym w¹tku co konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void odblokuj();

		/**
		* \brief Metoda ¿¹daj¹ca zakoñczenia w¹tku.
		*
		* Metoda pomocnicza przy rozsze¿aniu funkcjonalnoœci. Pomaga przekazaæ infomacje, ¿e w¹tek powinien zakoñczyæ swoje dzia³anie.
		* Akcja jaka zostanie podjêta, zale¿y od implementacji funkcji g³ównej w¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void zakoncz();

		/**
		* \brief Metoda informuj¹ca czy w¹tek zosta³ zakoñczony.
		*
		* Metoda informuje czy w¹tek zakoñczy³ dzia³anie.
		* Akcja jaka zostanie podjêta, zale¿y od implementacji funkcji g³ównej w¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const std::atomic<bool>& zakonczony() const;

		/**
		* \brief Metoda informuj¹ca czy wyst¹pi³ b³¹d.
		*
		* Metoda pomocnicza przy rozsze¿aniu funkcjonalnoœci. Pozwala na poinformowanie o wyst¹pieniu b³êdu podczas dzia³ania w¹tku i powodu jego zakoñczenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const std::atomic<bool>& blad() const;

		/**
		* \brief Metoda pobieraj¹ca informacje o wyj¹tku.
		*
		* Metoda pomocnicza przy rozsze¿aniu funkcjonalnoœci. Pozwala na pobranie informacji o wyj¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const STyp::Wyjatek& bladInfo() const;

	protected:
		std::atomic<bool> zakoncz_; /// ¯¹danie zakoñczenia wykonywania w¹tku.
		std::mutex wstrzymany_; /// Mutex wstrzymuj¹cy dzia³anie w¹tku tu¿ przed uruchomieniem funkcji g³ównej.
		std::atomic<bool> zakonczony_; /// Informacja czy zakoñczono dzia³anie w¹tku.

		std::atomic<bool> blad_; /// Informacja czy wyj¹tek zosta³ ustawiony.
		STyp::Wyjatek bladInfo_; /// Wyj¹tek jaki zosta³ ustawiony przez w¹tek.

		/**
		* \brief Metoda ustawiaj¹ca wyj¹tek.
		*
		* Metoda pomocnicza przy rozsze¿aniu funkcjonalnoœci. Metoda ustawia informacje o b³êdzie.
		* \param[in] info - Obiekt wyj¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void ustawBlad(const STyp::Wyjatek& info);

		/**
		* \brief G³ówna funkcja w¹tku.
		*
		* G³ówna funkcja w¹tku.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		virtual void wykonuj();

		/**
		* \brief Metoda informuj¹ca o ¿adaniu zakoñczenia w¹tku.
		*
		* Metoda pomocnicza przy rozsze¿aniu funkcjonalnoœci. Metoda pobiera informacje o ¿¹daniu zakoñczenia dzia³ania w¹tku.
		* \return Zwracana jest wartoœæ true, je¿eli wys³ano ¿¹danie. Zwracana jest wartoœæ false, je¿eli nie wys³ano ¿¹dania.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		const std::atomic<bool>& czyZakonczyc() const;
		std::thread* uchwyt_; /// WskaŸnik na obiekt w¹tku.

		/**
		* \brief Metoda techniczna wywo³uj¹ca g³ówn¹ funkcjê w¹tku.
		*
		* Metoda techniczna wywo³uj¹ca g³ówn¹ funkcjê w¹tku. Zapewnia poprawne zakoñczenie w¹tku oraz wstrzymanie przy starcie.
		* \author Daniel Wojdak
		* \version 1
		* \date 10-07-2014
		*/
		void funkcjaWatku();
	};
};

