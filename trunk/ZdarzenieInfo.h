#pragma once
#include "Logger\LoggerInterface.h"
#include "Skrypt.h"
#include "Parser\XmlBO.h"
namespace SpEx{

	/**
	* \brief Klasa opisowa zdarzenia
	*
	* Klasa zawiera opisowe informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 2
	* \date 06-08-2014
	*/
	class ZdarzenieInfo :
		virtual public SLog::LoggerInterface
	{
	public:

		/**
		* \brief Konstrutkor.
		*
		* Konstrutkor.
		* \param[in] wezel - W�ze� z opisem zdarznia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		ZdarzenieInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ZdarzenieInfo() = default;

		/**
		* \brief Metoda wykonuj�ca skrypt zdarzenia.
		*
		* Metoda wykonuje skrypt zdefiniowany dla zdarzenia.
		* \return Zwracana jest warto�� true, je�eli uda�o si� wykona� skrypt lub nie ma skryptu. Zwracana jest warto�c false w wypadku wyst�pienia b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool wykonaj();

		/**
		* \brief Metoda pobieraj�ca identyfikator zdarzenia.
		*
		* Metoda pobieraj�ca identyfikator zdarzenia.
		* \return Identyfikator zdarzenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda pobieraj�ca nast�pny stan.
		*
		* Metoda pobiera nast�pny domy�lny stan dla aktualnego zdarzenia.
		* \return Wska�nik na nast�pny stan lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr< STyp::Identyfikator > pobierzStan() const;

		/**
		* \brief Metoda pobieraj�ca nast�pny numer.
		*
		* Metoda pobiera nast�pny domy�lny numer dla aktualnego zdarzenia.
		* \return Wska�nik na nast�pny stan lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr< int > pobierzNumer() const;

		/**
		* \brief Metoda tworz�ca tekstowy opis obiektu.
		*
		* Metoda generuje czytelny tekstowy opis obiektu.
		* \return Opis obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::string napis() const override;

	private:
		std::shared_ptr<Skrypt> skrypt_ = nullptr; /// Skrypt wykonywany w momencie wyst�pienia zdarzenia.
		std::string luaFuncInside_; /// Nazwa metody.
		STyp::Identyfikator id_; /// Identyfikator zdarzenia.
		std::shared_ptr < STyp::Identyfikator > nastepnyStan_; /// Nast�pny domy�lny stan.
		std::shared_ptr < int > nastepnyNumer_; /// Nast�pny domy�lny numer.

	};
};
