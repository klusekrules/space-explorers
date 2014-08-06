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
		* \param[in] wezel - Wêze³ z opisem zdarznia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		ZdarzenieInfo(XmlBO::ElementWezla wezel);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ZdarzenieInfo() = default;

		/**
		* \brief Metoda wykonuj¹ca skrypt zdarzenia.
		*
		* Metoda wykonuje skrypt zdefiniowany dla zdarzenia.
		* \return Zwracana jest wartoœæ true, je¿eli uda³o siê wykonaæ skrypt lub nie ma skryptu. Zwracana jest wartoœc false w wypadku wyst¹pienia b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool wykonaj();

		/**
		* \brief Metoda pobieraj¹ca identyfikator zdarzenia.
		*
		* Metoda pobieraj¹ca identyfikator zdarzenia.
		* \return Identyfikator zdarzenia.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda pobieraj¹ca nastêpny stan.
		*
		* Metoda pobiera nastêpny domyœlny stan dla aktualnego zdarzenia.
		* \return WskaŸnik na nastêpny stan lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr< STyp::Identyfikator > pobierzStan() const;

		/**
		* \brief Metoda pobieraj¹ca nastêpny numer.
		*
		* Metoda pobiera nastêpny domyœlny numer dla aktualnego zdarzenia.
		* \return WskaŸnik na nastêpny stan lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr< int > pobierzNumer() const;

		/**
		* \brief Metoda tworz¹ca tekstowy opis obiektu.
		*
		* Metoda generuje czytelny tekstowy opis obiektu.
		* \return Opis obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::string napis() const override;

	private:
		std::shared_ptr<Skrypt> skrypt_ = nullptr; /// Skrypt wykonywany w momencie wyst¹pienia zdarzenia.
		std::string luaFuncInside_; /// Nazwa metody.
		STyp::Identyfikator id_; /// Identyfikator zdarzenia.
		std::shared_ptr < STyp::Identyfikator > nastepnyStan_; /// Nastêpny domyœlny stan.
		std::shared_ptr < int > nastepnyNumer_; /// Nastêpny domyœlny numer.

	};
};
