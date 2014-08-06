#pragma once
#include "Obiekt.h"
#include "NiezgodnyTypSurowca.h"
#include "PodstawoweParametry.h"
#include "Logger\LoggerInterface.h"

namespace SpEx{
	class SurowceInfo;
	class Ladownia;

	/**
	* \brief Klasa reprezentuj�ca surowiec.
	*
	* Klasa reprezentuj�ca surowiec.
	* \author Daniel Wojdak
	* \version 1
	* \date 25-07-2013
	*/
	class Surowce :
		public Obiekt,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class SurowceInfo;
	public:

		/**
		* \brief Destruktor.
		*/
		virtual ~Surowce() = default;

		/**
		* \brief Operator przypisania.
		*
		* \param[in] obiekt -  Obiekt jaki ma by� przypisany do klasy.
		*/
		Surowce& operator=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator r�wno�ci.
		*
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		*/
		bool operator==(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator nier�wno�ci.
		*
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		*/
		bool operator!=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator s�abej wi�kszo�ci.
		*
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		*/
		bool operator>(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator s�abej mniejszo�ci
		*
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		*/
		bool operator<(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator wi�kszo�ci.
		*
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		*/
		bool operator>=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator mniejszo�ci.
		*
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		*/
		bool operator<=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator sumy.
		*
		* \param[in] obiekt - Obiekt dodany do aktualnej warto�ci.
		*/
		Surowce operator+(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator przypisania i sumy.
		*
		* \param[in] obiekt - Obiekt dodany do aktualnej warto�ci.
		*/
		Surowce& operator+=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator r�nicy.
		*
		* \param[in] obiekt - Obiekt odj�ty od aktualnej warto�ci.
		*/
		Surowce operator-(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator przypisania i r�nicy.
		*
		* \param[in] obiekt - Obiekt odj�ty od aktualnej warto�ci.
		*/
		Surowce& operator-=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Metoda dodaje obiekt surowca.
		*
		* \param[in] obiekt - obiekt dodany do aktualnego.
		* \return true je�eli mo�na doda� obiekt, false w przeciwnym wypadku.
		*/
		bool Dodaj(const Surowce& obiekt);

		/**
		* \brief Metoda odejmuj�ca obiekt surowca.
		*
		* \param[in] obiekt - obiekt odj�ty do aktualnego.
		* \return true je�eli mo�na odj�� obiekt, false w przeciwnym wypadku.
		*/
		bool Usun(const Surowce& obiekt);

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy.
		*
		* \return Obiekt opisowy surowca.
		*/
		const SurowceInfo& pobierzSurowceInfo() const;

		/**
		* \brief Metoda informuj�ca czy obiekt jest typu przyrostowego.
		*
		* \return true je�eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
		*/
		bool czyTypPrzyrostowy()const;

		/**
		* \brief Metoda wyliczaj�ca czas budowy.
		*
		* Metoda wylicza czas budowy dla takiej obecnej ilo�ci surowc�w.
		* \return Czas budowy dla podanej ilo�ci u�ytych surowc�w.
		*/
		STyp::Czas pobierzCzas()const;

		/**
		* Metoda kopiuj�ca obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na kopie obiektu.
		*/
		Surowce* kopia() const override;

		/**
		* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
		* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
		* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
		* \param[in] ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na podzielony obiekt. Je�eli nie mo�na by�o podzieli� obiektu, zostaje zwr�cony nullptr.
		* \remark Metoda jest tranzakcyjna.
		*/
		Surowce* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiektbazowy - Obiekt do po��czenia.
		* \warning Metoda nie zwalnia pami�ci przekazanego obiektu.
		* \return Kiedy obiekty zostan� po��czone, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
		* \remark Metoda jest tranzakcyjna.
		*/
		bool polacz(const Obiekt& obiekt) override;

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

		STyp::Objetosc pobierzObjetosc(const PodstawoweParametry& parametryPodstawowe)const;
		STyp::Objetosc pobierzObjetosc()const;

		STyp::Objetosc pobierzObjetoscJednostkowa()const;

		STyp::Masa pobierzMase(const PodstawoweParametry& parametryPodstawowe)const;
		STyp::Masa pobierzMase()const;

	private:
		/**
		* \brief Konstruktor.
		*
		* \param[in] ilosc - Ilo�� tworzonego obiektu.
		* \param[in] obiekt - Obiekt na bazie kt�rego jest tworzona aktualna instancja.
		*/
		Surowce(const STyp::Ilosc& ilosc, const Surowce& obiekt);

		/**
		* \brief Konstruktor.
		*
		* \param[in] ilosc - Ilo�� tworzonego obiektu.
		* \param[in] parametryPodstawowe - Podstawowe parametry.
		* \param[in] surowceInfo - Referencja do obiektu opisuj�cego.
		*/
		Surowce(const PodstawoweParametry& parametryPodstawowe, const SurowceInfo& surowceInfo);

		const SurowceInfo& surowceInfo_; /// Referencja do obiektu opisowego.
	};
}