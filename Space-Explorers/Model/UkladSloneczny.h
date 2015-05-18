#pragma once
#include <memory>
#include "Planeta.h"
#include "Narzedzia\Serializacja.h"
#include <unordered_map>

namespace SpEx {

	/**
	* \brief Klasa reprezentuj�ca uk�ad s�oneczny
	*
	* Klasa reprezentuj�ca uk�ad s�oneczny.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-10-2013
	*/
	class UkladSloneczny :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class ZarzadcaLokacji;
	public:
		typedef std::shared_ptr<Planeta> Planeta;
		typedef std::unordered_map< STyp::Identyfikator, Planeta, STyp::IdTypeHash > Planety; /// Typ listy planet

		/**
		* \brief Konstruktor
		*
		* \param[in] identyfikator - Numer identyfikuj�cy uk�ad s�oneczny
		* \param[in] identyfikatorGalaktyki - Numer identyfikuj�cy galaktyk� w kt�rej znajduje sie uk�ad s�oneczny.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		UkladSloneczny(const STyp::Identyfikator& identyfikator, const STyp::Identyfikator& identyfikatorGalaktyki);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~UkladSloneczny() = default;

		/**
		* \brief Metoda pobieraj�ca identyfikator.
		*
		* Metoda pobiera identyfikator obiektu.
		* \return Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda ustawiaj�ca �rednic� gwiazdy.
		*
		* Metoda ustawia �rednic� gwiazdy na podan� w parametrze.
		* \param[in] srednica - nowa warto�c srednicy gwiazdy uk�adu s�onecznego.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		void ustawSredniceGwiazdy(const STyp::Dystans& srednica);

		/**
		* \brief Metoda zwraca �rednic� gwiazdy uk�adu.
		*
		* Metoda zwraca �rednic� gwiazdy uk�adu w mln km.
		* \return �rednica gwiady uk�adu.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		const STyp::Dystans& pobierzSredniceGwiazdy() const;

		/**
		* \brief Metoda ustawia �redni� temperatur� gwiazdy.
		*
		* Metoda ustawia �redni� temperatur� gwiazdy na podan� w parametrze.
		* \param[in] temperatura - nowa warto�� �redniej temperatury gwiazdy w kelwinach.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		void ustawSredniaTemperatureGwiazdy(const STyp::Temperatura& temperatura);

		/**
		* \brief Metoda zwraca �redni� temperatu� gwiazdy.
		*
		* Metoda zwraca �redni� temperatur� gwiazdy podan� w kelwinach.
		* \return �rednia temperatura gwiazdy.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		const STyp::Temperatura& pobierzSredniaTemperatureGwiazdy() const;

		/**
		* \brief Metoda zwraca moc gwiazdy.
		*
		* Metoda zwraca moc gwiazdy.
		* \return Moc gwiazdy.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		STyp::Moc pobierzMocGwiazdy() const;

		/**
		* \brief Metoda dodaje planet� do listy planet nale��cych do uk�adu.
		*
		* Metoda dodaj planet� do listy planet znajduj�cych sie w uk�adzie.
		* \param[in] planeta - Wska�nik na planet� dodawan� do listy.
		* \return true je�eli uda si� doda� planet�, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool dodajPlanete(UkladSloneczny::Planeta planeta);

		/**
		* \brief Metoda zwracaj�ca planet� z uk�adu.
		*
		* Metoda zwraca planet� o podanym id, kt�ra znajduje si� na li�cie planet uk�adu.
		* \param[in] identyfikator - Numer identyfikuj�cy planet�.
		* \return Wska�nik na planet� lub nullptr je�eli planeta nie zostanie znaleziona.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		UkladSloneczny::Planeta pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczb� planet w uk�adzie.
		*
		* Metoda zwraca liczb� planet znajduj�cych w uk�adzie s�onecznym.
		* \return liczba planet.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		int liczbaPlanet() const;

		/**
		* \brief Metoda zwracaj�ca identyfikator galaktyki.
		*
		* Metoda zwraca identyfikator galaktyki w kt�rej le�y uk�ad.
		* \return Identyfikator galaktyki.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		const STyp::Identyfikator& pobierzIdGalaktyki() const;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
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
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		*/
		std::string napis() const override;

	private:

		STyp::Identyfikator idGalaktyki_; /// Identyfikator galaktyki do kt�rej nale�y uk�ad s�oneczny

		STyp::Dystans srednicaGwiazdy_; /// �rednica gwiazdy
		STyp::Temperatura sredniaTemperaturaGwiazdy_; /// �rednia temperatura  gwiazdy
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
		Planety planety_; /// Lista planet przynale�nych  do uk�adu.
	};
}
