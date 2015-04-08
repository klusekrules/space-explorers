#pragma once
#include "TypyProste\TypyProste.h"
#include "Logger\LoggerInterface.h"
#include "PodstawoweParametry.h"
#include "Wymagania.h"

namespace SpEx{
	class ObiektInfo;
	
	/**
	* \brief Klasa obiektu
	*
	* Klasa bazowa dla obiektów w grze. Poszerza interfejs o metody sprawdzaj¹ce powierzchniê, objêtoœæ i masê.
	* Rozsze¿a tak¿e interfejs o metodê sprawdzaj¹c¹ mo¿liwoœæ dodania obiektu do ³adowni.
	* \author Daniel Wojdak
	* \version 2
	* \date 14-07-2014
	*/
	class Obiekt :
		virtual public PodstawoweParametry,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		typedef std::shared_ptr<Obiekt> SharedPtr;
		typedef std::shared_ptr<const Obiekt> ConstSharedPtr;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] parametry - Parametry obiektu wymagane do poprawnego utworzenia instancji.
		* \param[in] obiektInfo - Referencja do obiektu opisuj¹cego.
		*/
		Obiekt(const PodstawoweParametry& parametry, const ObiektInfo& obiektInfo);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Obiekt() = default;

		Obiekt& operator=(const Obiekt&) = delete;

		/**
		* Metoda kopiuj¹ca obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na kopie obiektu.
		*/
		virtual Obiekt* kopia() const = 0;

		/**
		* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
		* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
		* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
		* \param[in] ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na podzielony obiekt. Je¿eli nie mo¿na by³o podzieliæ obiektu, zostaje zwrócony nullptr.
		*/
		virtual Obiekt* podziel(const STyp::Ilosc& ilosc) = 0;

		/**
		* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Obiekt do po³¹czenia.
		* \warning Metoda nie zwalnia pamiêci przekazanego obiektu.
		* \return Kiedy obiekty zostan¹ po³¹czone, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
		* \remark Metoda jest tranzakcyjna.
		*/
		virtual bool polacz(const Obiekt& obiekt) = 0;

		/**
		* Metoda sprawdzaj¹ca warunki po³¹czenia obiektów.
		* \param[in] obiekt - Obiekt dla którego maj¹ byæ sprawdzone warunki po³¹czenia.
		* \return Kiedy obiekt mo¿e byæ po³¹czony, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
		*/
		virtual bool czyMoznaPolaczyc(const Obiekt& obiekt) const;

		/**
		* Metoda sprawdzaj¹ca czy mo¿na podzieliæ obiekt wed³ug podanej iloœci.
		* \param[in] ilosc - Iloœæ w zglêdem, której s¹ sprawdzane warunki podzia³u.
		* \return Je¿eli mo¿na podzieliæ, zwracana jest wartoœæ true, w przeciwnym wypadku zwrócona wartoœæ to false.
		*/
		virtual bool czyMoznaPodzielic(const STyp::Ilosc& ilosc) const;

		/**
		* Metoda pobieraj¹ca przetworzone koszty dostêpnoœci obiektu
		* \return Koszty po przetworzeniu przez klasy zmieniaj¹ce
		*/
		Wymagania::PrzetworzoneWarunki pobierzKryteriaRozbudowy() const;

		/**
		* Metoda wyliczaj¹ca czas trwania rozbudowy jednego obiektu na kolejny poziom.
		* \return Czas trwania rozbudowy.
		*/
		virtual STyp::Czas pobierzCzasRozbudowy()const;

		/**
		* Metoda sprawdzaj¹ca wymagania obiektu.
		* \return Je¿eli obiekt spe³nia wymagania zwrócona jest wartoœæ true. Je¿eli nie spe³nia wymagañ zwrócona jest wartoœæ false.
		*/
		bool czyMoznaRozbudowac()const;

		/**
		* Metoda buduj¹ca obiekty o podanej iloœci.
		* \warning Metoda nie sprawdza czy obiekty moga byæ wybudowane.
		*/
		virtual bool wybuduj(const PodstawoweParametry& parametry);

		/**
		* Metoda zwracaj¹ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* Metoda ustawiaj¹ca identyfikator obiektu.
		* \param[in] identyfikator - Nowa wartoœæ identyfikatora obiektu.
		* \deprecated Metoda przeznaczona do usuniêcia.
		*/
		void ustawIdentyfikator(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
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
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy.
		*
		* Metoda pobiera referencjê do obiektu opisowego.
		* \return Referencja do obiektu opisowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const ObiektInfo& pobierzObiektInfo()const;

	protected:
		/**
		* \brief Domyœlny konstruktor kopiuj¹cy.
		*
		* Domyœlny konstruktor kopiuj¹cy.
		*/
		Obiekt(const Obiekt&) = default;

		const ObiektInfo& obiektInfo_; /// Referencja do obiektu opisowego.

	private:
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}
