#pragma once
#include "NarzedziaSymbol.h"
namespace SpEx{
	/**
	* \brief Klasa zliczaj¹ca iloœæ fps.
	*
	* Klasa s³u¿¹ca do zliczania iloœæi fps.
	* \author Daniel Wojdak
	* \version 1
	* \date 03-07-2014
	*/
	class NARZEDZIA_API FPSCounter
	{
	private:
		unsigned long long Frames = 0; /// Iloœæ zmierzonych ramek, od ostatniego pobrania wyniku
		double time; /// Chwilowy punkt czasu.
		double fpsTime = 0; /// Czas pomiaru, który min¹³ od ostatniego pobrania wyniku
		long double fps_ = 0; /// Iloœæ fps.
	public:
		/**
		* \brief Konstruktor.
		*
		* Bezparametrowy konstruktor obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		FPSCounter();

		/**
		* \brief Metoda zlicza nastêpn¹ ramkê.
		*
		* Metoda oblicza czas pomiêdzy ramkami oraz zwiêksza licznik ramek.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		void nextFrame();

		/**
		* \brief Metoda zwraca iloœæ fps.
		*
		* Metoda zwraca aktualn¹ œredni¹ iloœæ fps.
		* \return Iloœæ fps.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		long double FPS();
		
		/**
		* \brief Metoda informuje o poprawnoœci wyniku metody FPS.
		*
		* Metoda informuje czy wynik metody FPS bêdzie wzgl¹dnie poprawny, tzn. czy okres w którym zosta³y zbierane próbki jest wystarczaj¹co d³ugi.
		* \return Zwraca wartoœæ true, je¿eli wynik bêdzie poprawny. Wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-07-2014
		*/
		bool ready() const;

		/**
		* \brief Destruktor.
		*
		* Domyœlny destruktor obiektu.
		*/
		~FPSCounter() = default;
	};
};
