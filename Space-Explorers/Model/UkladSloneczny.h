#pragma once
#include <memory>
#include "Planeta.h"
#include "Narzedzia\Serializacja.h"
#include <unordered_map>

namespace SpEx {

	/**
	* \brief Klasa reprezentuj¹ca uk³ad s³oneczny
	*
	* Klasa reprezentuj¹ca uk³ad s³oneczny.
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
		* \param[in] identyfikator - Numer identyfikuj¹cy uk³ad s³oneczny
		* \param[in] identyfikatorGalaktyki - Numer identyfikuj¹cy galaktykê w której znajduje sie uk³ad s³oneczny.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		UkladSloneczny(const STyp::Identyfikator& identyfikator, const STyp::Identyfikator& identyfikatorGalaktyki);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~UkladSloneczny() = default;

		/**
		* \brief Metoda pobieraj¹ca identyfikator.
		*
		* Metoda pobiera identyfikator obiektu.
		* \return Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda ustawiaj¹ca œrednicê gwiazdy.
		*
		* Metoda ustawia œrednicê gwiazdy na podan¹ w parametrze.
		* \param[in] srednica - nowa wartoœc srednicy gwiazdy uk³adu s³onecznego.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		void ustawSredniceGwiazdy(const STyp::Dystans& srednica);

		/**
		* \brief Metoda zwraca œrednicê gwiazdy uk³adu.
		*
		* Metoda zwraca œrednicê gwiazdy uk³adu w mln km.
		* \return Œrednica gwiady uk³adu.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		const STyp::Dystans& pobierzSredniceGwiazdy() const;

		/**
		* \brief Metoda ustawia œredni¹ temperaturê gwiazdy.
		*
		* Metoda ustawia œredni¹ temperaturê gwiazdy na podan¹ w parametrze.
		* \param[in] temperatura - nowa wartoœæ œredniej temperatury gwiazdy w kelwinach.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		void ustawSredniaTemperatureGwiazdy(const STyp::Temperatura& temperatura);

		/**
		* \brief Metoda zwraca œredni¹ temperatuê gwiazdy.
		*
		* Metoda zwraca œredni¹ temperaturê gwiazdy podan¹ w kelwinach.
		* \return Œrednia temperatura gwiazdy.
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
		* \brief Metoda dodaje planetê do listy planet nale¿¹cych do uk³adu.
		*
		* Metoda dodaj planetê do listy planet znajduj¹cych sie w uk³adzie.
		* \param[in] planeta - WskaŸnik na planetê dodawan¹ do listy.
		* \return true je¿eli uda siê dodaæ planetê, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool dodajPlanete(UkladSloneczny::Planeta planeta);

		/**
		* \brief Metoda zwracaj¹ca planetê z uk³adu.
		*
		* Metoda zwraca planetê o podanym id, która znajduje siê na liœcie planet uk³adu.
		* \param[in] identyfikator - Numer identyfikuj¹cy planetê.
		* \return WskaŸnik na planetê lub nullptr je¿eli planeta nie zostanie znaleziona.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		UkladSloneczny::Planeta pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczbê planet w uk³adzie.
		*
		* Metoda zwraca liczbê planet znajduj¹cych w uk³adzie s³onecznym.
		* \return liczba planet.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		int liczbaPlanet() const;

		/**
		* \brief Metoda zwracaj¹ca identyfikator galaktyki.
		*
		* Metoda zwraca identyfikator galaktyki w której le¿y uk³ad.
		* \return Identyfikator galaktyki.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		const STyp::Identyfikator& pobierzIdGalaktyki() const;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj¹ca.
		*
		* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		* \warning Metoda nie modyfikuje wêz³a.
		* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		*/
		std::string napis() const override;

	private:

		STyp::Identyfikator idGalaktyki_; /// Identyfikator galaktyki do której nale¿y uk³ad s³oneczny

		STyp::Dystans srednicaGwiazdy_; /// Œrednica gwiazdy
		STyp::Temperatura sredniaTemperaturaGwiazdy_; /// Œrednia temperatura  gwiazdy
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
		Planety planety_; /// Lista planet przynale¿nych  do uk³adu.
	};
}
