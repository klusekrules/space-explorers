#pragma once
#include "Logger\LoggerInterface.h"
#include "Skrypt.h"
#include "ZdarzenieInfo.h"
#include <map>

namespace SpEx{

	/**
	* \brief Klasa opisowa stanu
	*
	* Klasa zawiera opisowe informacje o stanie.
	* \author Daniel Wojdak
	* \version 2
	* \date 05-08-2014
	*/
	class StanInfo :
		virtual public SLog::LoggerInterface
	{
	public:
		/**
		* \brief Typy akcji stanu.
		*
		* Typy akcji jakie wystêpuj¹ w stanie.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		enum Akcja{
			AkcjaWejsciowa,
			AkcjaWyjsciowa,
			AkcjaWewnetrzna
		};

		/**
		* \brief Konstruktor.
		*
		* Konstruktor tworzy obiekt na podstawie przekazanego wêz³a.
		* \param[in] wezel - Wêze³ z opisem obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		StanInfo(XmlBO::ElementWezla wezel);
		
		/**
		* \brief Domyœlny destruktor. 
		*
		* Domyœ³ny destrutkor.
		*/
		virtual ~StanInfo(void) = default;

		/**
		* \brief Metoda wykonuj¹ca skrypt.
		*
		* Metoda wykonuje skrypt dla podanej akcji.
		* \param[in] typ - Typ akcji.
		* \return Zwracana jest wartoœæ true, je¿eli operacja zakoñczy siê powodzeniem. Zwracana jest wartoœæ false w przewinym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool wykonaj(Akcja typ);

		/**
		* \brief Metoda pobieraj¹ca identyfikator stanu.
		*
		* Metoda pobieraj¹ca identyfikator stanu.
		* \return Identyfikator stanu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda pobieraj¹ca zdarzenie.
		*
		* Metoda pobiera zdarzenie opodanym identyfikatorze skojarzone ze stanem.
		* \param[in] identyfikator Identyfikator zdarzenia.
		* \return WskaŸnik na zdarzenie lub nullptr, je¿eli nie istnieje skojarzone zdarzenie o podanym identyfikatorze.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<ZdarzenieInfo> pobierzZdarzenie(const STyp::Identyfikator& identyfikator) const;

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
		std::shared_ptr<Skrypt> skrypt_ = nullptr; /// Skrypt stanu.
		std::string luaFuncIn_; /// Nazwa metody wykonanej przy wejœciu do stanu.
		std::string luaFuncOut_; /// Nazwa metody wykonanej przy wyjœciu ze stanu.
		std::string luaFuncInside_; /// Nazwa metody wykonanej w momencie pomownego wejœcia do tego samego stanu ( pomijane s¹ metody wejœcia i wyjœcia ).
		STyp::Identyfikator id_; /// Identyfikator stanu.
		std::map < STyp::Identyfikator, std::shared_ptr<ZdarzenieInfo> > zdarzenia_; /// Zbiór skojarzonych zdarzeñ.
	};
};
