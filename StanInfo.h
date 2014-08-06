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
		* Typy akcji jakie wyst�puj� w stanie.
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
		* Konstruktor tworzy obiekt na podstawie przekazanego w�z�a.
		* \param[in] wezel - W�ze� z opisem obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		StanInfo(XmlBO::ElementWezla wezel);
		
		/**
		* \brief Domy�lny destruktor. 
		*
		* Domy��ny destrutkor.
		*/
		virtual ~StanInfo(void) = default;

		/**
		* \brief Metoda wykonuj�ca skrypt.
		*
		* Metoda wykonuje skrypt dla podanej akcji.
		* \param[in] typ - Typ akcji.
		* \return Zwracana jest warto�� true, je�eli operacja zako�czy si� powodzeniem. Zwracana jest warto�� false w przewinym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		bool wykonaj(Akcja typ);

		/**
		* \brief Metoda pobieraj�ca identyfikator stanu.
		*
		* Metoda pobieraj�ca identyfikator stanu.
		* \return Identyfikator stanu.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda pobieraj�ca zdarzenie.
		*
		* Metoda pobiera zdarzenie opodanym identyfikatorze skojarzone ze stanem.
		* \param[in] identyfikator Identyfikator zdarzenia.
		* \return Wska�nik na zdarzenie lub nullptr, je�eli nie istnieje skojarzone zdarzenie o podanym identyfikatorze.
		* \author Daniel Wojdak
		* \version 1
		* \date 09-07-2014
		*/
		std::shared_ptr<ZdarzenieInfo> pobierzZdarzenie(const STyp::Identyfikator& identyfikator) const;

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
		std::shared_ptr<Skrypt> skrypt_ = nullptr; /// Skrypt stanu.
		std::string luaFuncIn_; /// Nazwa metody wykonanej przy wej�ciu do stanu.
		std::string luaFuncOut_; /// Nazwa metody wykonanej przy wyj�ciu ze stanu.
		std::string luaFuncInside_; /// Nazwa metody wykonanej w momencie pomownego wej�cia do tego samego stanu ( pomijane s� metody wej�cia i wyj�cia ).
		STyp::Identyfikator id_; /// Identyfikator stanu.
		std::map < STyp::Identyfikator, std::shared_ptr<ZdarzenieInfo> > zdarzenia_; /// Zbi�r skojarzonych zdarze�.
	};
};
