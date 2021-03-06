#pragma once
#include "Obiekt.h"

namespace SpEx{

	class TechnologiaInfo;

	/**
	* \brief Klasa reprezentuj�ca technologie.
	*
	* Klasa reprezentuj�ca technologie.
	* \author Daniel Wojdak
	* \version 1
	* \date 25-07-2013
	*/
	class Technologia :
		public Obiekt,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		typedef TechnologiaInfo Info;
		typedef std::shared_ptr<Technologia> SharedPtr;
		typedef std::shared_ptr<const Technologia> ConstSharedPtr;
		
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
		* \param[in] technologiaInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Technologia(const PodstawoweParametry& podstawoweParametry, const TechnologiaInfo& technologiaInfo);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Technologia() = default;

		/**
		* \brief Metoda tworz�ca kopi� obiektu.
		*
		* Metoda kopiuj�ca obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na kopie obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Technologia* kopia() const override;

		/**
		* \brief Metoda dziel�ca obiekt.
		*
		* Metoda dziel�ca obiekt, nie jest wspierana dla budynku, zawsze zwraca nullptr.
		* \param[in] ilosc - Nieu�ywany.
		* \return  Metoda zawsze zwraca nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Technologia* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* \brief Metoda ��cz�ca obiekty.
		*
		* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Nieu�ywany.
		* \return Zawsze zwraca warto�� false.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool polacz(const Obiekt& obiekt) override;

		/**
		* \brief Metoda sprawdzaj�ca czy mo�na po��czy� obiekty.
		*
		* Metoda sprawdzaj�ca warunki po��czenia obiekt�w.
		* \param[in] obiekt - Nieu�ywany.
		* \return Zawsze zwraca warto�� false.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool czyMoznaPolaczyc(const Obiekt& obiekt) const override;

		/**
		* \brief Metoda sprawdzaj�ca czy mo�na podzieli� obiekt.
		*
		* Metoda sprawdzaj�ca czy mo�na podzieli� obiekt wed�ug podanej ilo�ci.
		* \param[in] ilosc - Nieu�ywany.
		* \return Zawsze zwraca warto�� false.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool czyMoznaPodzielic(const STyp::Ilosc& ilosc) const override;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
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
		* \date 25-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis()const override;

	protected:
		const TechnologiaInfo& technologiaInfo_; /// Referencja do obiektu opisuj�cego.
	};
}
