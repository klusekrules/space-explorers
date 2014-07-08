#pragma once
#include "Zlecenie.h"
#include "PodstawoweParametry.h"
#include <functional>
namespace SpEx{

	/**
	* \brief Klasa zlecenia ustawiaj�ca dla obiektu identyfikator planety.
	*
	* Klasa implamantuj�ca interfejs zlecenia. Umo�liwia ustawianie identyfikatora planety dla  podanego obiektu z mo�liwo�ci� cofni�cia operacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 02-07-2014
	*/
	class ZlecenieUstawIdentyfikatorPlanety :
		public Zlecenie < STyp::Identyfikator, std::shared_ptr< SpEx::PodstawoweParametry > >,
		virtual public SLog::LoggerInterface
	{
	private:
		STyp::Identyfikator staryIdentyfikator_; /// Stary identyfikator planety.

		/**
		* \brief Metoda wykonuj�ca operacje ustawienia identyfikatora planety.
		*
		* Metoda wykonuje operacje ustawienia identyfikatora planety dla obiektu podanego w parametrze.
		* \param[in] id - Nowy identyfikator planety.
		* \param[in] obiekt - Obiekt na rzecz kt�rego jest ustawiany stary identyfikator planety.
		* \return Zwracana jest warto�� true, je�eli operacja si� powiedzie. Zwracana jest warto�c false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-07-2014
		*/
		bool ustawIdentyfikator(STyp::Identyfikator& id, std::shared_ptr< SpEx::PodstawoweParametry >& obiekt){
			staryIdentyfikator_ = obiekt->pobierzIdentyfikatorPlanety();
			obiekt->ustawIdentyfikatorPlanety(id);
			return true;
		}

		/**
		* \brief Metoda cofaj�ca operacje ustawienia identyfikatora planety.
		*
		* Metoda cofa wykonan� operacje ustawienia identyfikatora planety dla obiektu podanego w parametrze.
		* \param[in] id - Parametr nieu�ywany.
		* \param[in] obiekt - Obiekt na rzecz kt�rego jest ustawiany stary identyfikator planety.
		* \return Zwracana jest warto�� true, je�eli operacja si� powiedzie. Zwracana jest warto�c false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-07-2014
		*/
		bool cofnijUstawIdentyfikator(STyp::Identyfikator& id, std::shared_ptr< SpEx::PodstawoweParametry >& obiekt){
			obiekt->ustawIdentyfikatorPlanety(staryIdentyfikator_);
			return true;
		}
	public:

		/**
		* \brief Konstruktor.
		*
		* Konstruktor obiektu. Ustawiany jest obiekt, dla kt�rego b�dzie zmieniony identyfikator planety. 
		* Opr�cz tego pobierany jest identyfikator jaki ma zosta� ustawiony. 
		* \param[in] identyfikator - Nowy identyfikator planety.
		* \param[in] obiekt - Obiekt na rzecz kt�rego jest ustawiany stary identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-07-2014
		*/
		ZlecenieUstawIdentyfikatorPlanety(STyp::Identyfikator& identyfikator, std::shared_ptr< SpEx::PodstawoweParametry >& obiekt)
			: Zlecenie(identyfikator, obiekt, bind(&ZlecenieUstawIdentyfikatorPlanety::ustawIdentyfikator, this, std::placeholders::_1, std::placeholders::_2),
			bind(&ZlecenieUstawIdentyfikatorPlanety::cofnijUstawIdentyfikator, this, std::placeholders::_1, std::placeholders::_2))
		{}

		/**
		* \brief Destruktor.
		*
		* Domy�lny destruktor obiektu.
		*/
		virtual ~ZlecenieUstawIdentyfikatorPlanety() = default;

		/**
		* \brief Metoda tworz�ca opis tekstowy obiektu.
		*
		* Metoda s�u��ca do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-07-2014
		*/
		std::string napis() const override{
			SLog::Logger str(NAZWAKLASY(ZlecenieUstawIdentyfikatorPlanety));
			str.dodajKlase(Zlecenie::napis());
			str.dodajPole(NAZWAPOLA(staryIdentyfikator_), staryIdentyfikator_);
			return str.napis();
		}
	};
};
