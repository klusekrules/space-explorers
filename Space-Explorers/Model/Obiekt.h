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
	* Klasa bazowa dla obiekt�w w grze. Poszerza interfejs o metody sprawdzaj�ce powierzchni�, obj�to�� i mas�.
	* Rozsze�a tak�e interfejs o metod� sprawdzaj�c� mo�liwo�� dodania obiektu do �adowni.
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
		* \param[in] obiektInfo - Referencja do obiektu opisuj�cego.
		*/
		Obiekt(const PodstawoweParametry& parametry, const ObiektInfo& obiektInfo);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Obiekt() = default;

		Obiekt& operator=(const Obiekt&) = delete;

		/**
		* Metoda kopiuj�ca obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na kopie obiektu.
		*/
		virtual Obiekt* kopia() const = 0;

		/**
		* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
		* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
		* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
		* \param[in] ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na podzielony obiekt. Je�eli nie mo�na by�o podzieli� obiektu, zostaje zwr�cony nullptr.
		*/
		virtual Obiekt* podziel(const STyp::Ilosc& ilosc) = 0;

		/**
		* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Obiekt do po��czenia.
		* \warning Metoda nie zwalnia pami�ci przekazanego obiektu.
		* \return Kiedy obiekty zostan� po��czone, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
		* \remark Metoda jest tranzakcyjna.
		*/
		virtual bool polacz(const Obiekt& obiekt) = 0;

		/**
		* Metoda sprawdzaj�ca warunki po��czenia obiekt�w.
		* \param[in] obiekt - Obiekt dla kt�rego maj� by� sprawdzone warunki po��czenia.
		* \return Kiedy obiekt mo�e by� po��czony, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
		*/
		virtual bool czyMoznaPolaczyc(const Obiekt& obiekt) const;

		/**
		* Metoda sprawdzaj�ca czy mo�na podzieli� obiekt wed�ug podanej ilo�ci.
		* \param[in] ilosc - Ilo�� w zgl�dem, kt�rej s� sprawdzane warunki podzia�u.
		* \return Je�eli mo�na podzieli�, zwracana jest warto�� true, w przeciwnym wypadku zwr�cona warto�� to false.
		*/
		virtual bool czyMoznaPodzielic(const STyp::Ilosc& ilosc) const;

		/**
		* Metoda pobieraj�ca przetworzone koszty dost�pno�ci obiektu
		* \return Koszty po przetworzeniu przez klasy zmieniaj�ce
		*/
		Wymagania::PrzetworzoneWarunki pobierzKryteriaRozbudowy() const;

		/**
		* Metoda wyliczaj�ca czas trwania rozbudowy jednego obiektu na kolejny poziom.
		* \return Czas trwania rozbudowy.
		*/
		virtual STyp::Czas pobierzCzasRozbudowy()const;

		/**
		* Metoda sprawdzaj�ca wymagania obiektu.
		* \return Je�eli obiekt spe�nia wymagania zwr�cona jest warto�� true. Je�eli nie spe�nia wymaga� zwr�cona jest warto�� false.
		*/
		bool czyMoznaRozbudowac()const;

		/**
		* Metoda buduj�ca obiekty o podanej ilo�ci.
		* \warning Metoda nie sprawdza czy obiekty moga by� wybudowane.
		*/
		virtual bool wybuduj(const PodstawoweParametry& parametry);

		/**
		* Metoda zwracaj�ca Identyfikator obiektu.
		* \return Identyfikator obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* Metoda ustawiaj�ca identyfikator obiektu.
		* \param[in] identyfikator - Nowa warto�� identyfikatora obiektu.
		* \deprecated Metoda przeznaczona do usuni�cia.
		*/
		void ustawIdentyfikator(const STyp::Identyfikator& identyfikator);

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

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy.
		*
		* Metoda pobiera referencj� do obiektu opisowego.
		* \return Referencja do obiektu opisowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const ObiektInfo& pobierzObiektInfo()const;

	protected:
		/**
		* \brief Domy�lny konstruktor kopiuj�cy.
		*
		* Domy�lny konstruktor kopiuj�cy.
		*/
		Obiekt(const Obiekt&) = default;

		const ObiektInfo& obiektInfo_; /// Referencja do obiektu opisowego.

	private:
		STyp::Identyfikator identyfikator_; /// Identyfikator obiektu.
	};
}
