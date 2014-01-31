#pragma once
#include "TypyProste\TypyProste.h"
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"

namespace SpEx{
	/**
	* \brief Klasa reprezentuj�ca licznik.
	*
	* Klasa s�u��ca do generowania unikalnych identyfikator�w dla planet, flot itp.
	* \author Daniel Wojdak
	* \version 1
	* \date 22-07-2013
	*/
	class Licznik : //TODO: Dodanie atrybutu identyfikatora.
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworzy obiekt na podstawie identyfikatora i warto�ci licznika.
		* \param[in] wartoscPoczatkowa - Warto�� pocz�tkowa licznika.
		*/
		Licznik(const STyp::Identyfikator& identyfikator, const STyp::Ilosc& wartoscPoczatkowa);

		/**
		* \brief Konstruktor domy�lny.
		*/
		Licznik() = default;

		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda pobieraj�ca warto��.
		*
		* Metoda pobiera warto�� licznika a nast�pnie inkrementuje licznik.
		* \return Warto�� licznika z przed inkrementacji.
		*/
		STyp::Ilosc operator()();

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca warto�� licznika.
		*/
		STyp::Ilosc pobierzWartosc()const;

		/**
		* \brief Metoda resetuj�ca obiekt.
		*
		* Metoda ustawia warto�� domy�ln� atrybutu obiektu.
		* \warning Warto�� domy�lana atrybutu jest r�wna 0.
		*/
		void resetujWartosc();

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] wartosc - Nowa warto�� licznika.
		*/
		void ustawWartosc(const STyp::Ilosc& wartosc);

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj�ca.
		*
		* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
		* \warning Metoda nie modyfikuje w�z�a.
		* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

	private:
		STyp::Identyfikator identyfikator_;///
		STyp::Ilosc wartoscLicznika_ = 0;/// Warto�� licznika.
	};
}