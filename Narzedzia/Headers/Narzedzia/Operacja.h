#pragma once
#include "NarzedziaSymbol.h"
#include "Logger\LoggerInterface.h"
namespace SpEx{
	/**
	* \brief Klasa bazowa zawieraj¹ca interfejs dla wykonywanych operacji.
	*/
	class NARZEDZIA_API Operacja :
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Konstruktor domyœlny.
		*/
		Operacja(void) = default;

		/**
		* \brief Destruktor.
		*/
		virtual ~Operacja(void) = default;

		/**
		* \brief Metoda wykonuj¹ca operacje tranzakcyjn¹.
		*
		* \return Metoda klasy bazowej zawsze zwraca false.
		*/
		virtual bool wykonaj();

		/**
		* \brief Metoda wykonuj¹ca operacje odwrotn¹ do tranzakcyjnej.
		*
		* \return Metoda klasy bazowej zawsze zwraca false.
		*/
		virtual bool cofnij();

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;
	};
};
