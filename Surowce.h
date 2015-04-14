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
	* \version 2
	* \date 16-07-2014
	*/
	class Surowce :
		public Obiekt,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class SurowceInfo;
	public:

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Surowce() = default;

		/**
		* \brief Operator przypisania.
		*
		* Operator przypisania obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt jaki ma by� przypisany do klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce& operator=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator r�wno�ci.
		*
		* Operator sprawdzania r�wno�ci obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator==(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator nier�wno�ci.
		*
		* Operator sprawdzania nier�wno�ci obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator!=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator s�abej wi�kszo�ci.
		*
		* Operator sprawdzania s�abej wi�kszo�ci obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator>(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator s�abej mniejszo�ci
		*
		* Operator sprawdzania s�abej mniejszo�ci obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator<(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator wi�kszo�ci.
		*
		* Operator sprawdzania wi�kszo�ci obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator>=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator mniejszo�ci.
		*
		* Operator sprwadzania mniejszo�ci obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt z jakim ma byc por�wnana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator<=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator sumy.
		*
		* Operator sumy obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt dodany do aktualnej warto�ci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce operator+(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator przypisania i sumy.
		*
		* Operator przypisania i sumy obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt dodany do aktualnej warto�ci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce& operator+=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator r�nicy.
		*
		* Operator r�nicy obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt odj�ty od aktualnej warto�ci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce operator-(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator przypisania i r�nicy.
		*
		* Operator przypisania i r�nicy obiektu surowca. Je�eli typ surowca jest r�ny wyrzucany jest wyj�tek.
		* \param[in] obiekt - Obiekt odj�ty od aktualnej warto�ci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce& operator-=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Metoda dodaje obiekt surowca.
		*
		* Metoda dodaj�ca obiekt surowca. Metoda nie wyrzuca wyj�tku.
		* \param[in] obiekt - obiekt dodany do aktualnego.
		* \return true je�eli mo�na doda� obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool Dodaj(const Surowce& obiekt);

		/**
		* \brief Metoda odejmuj�ca obiekt surowca.
		*
		* Metoda odejmuj�ca obiekt surowca. Metoda nie wyrzuca wyj�tku.
		* \param[in] obiekt - obiekt odj�ty do aktualnego.
		* \return true je�eli mo�na odj�� obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool Usun(const Surowce& obiekt);

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy.
		*
		* Metoda pobieraj�ca obiekt opisowy.
		* \return Obiekt opisowy surowca.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		const SurowceInfo& pobierzSurowceInfo() const;

		/**
		* \brief Metoda informuj�ca czy obiekt jest typu przyrostowego.
		*
		* Metoda sprawdzaj�ca czy surowiec jest typu przyrostowego.
		* \return true je�eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool czyTypPrzyrostowy()const;

		/**
		* \brief Metoda wyliczaj�ca czas budowy.
		*
		* Metoda wylicza czas budowy dla takiej obecnej ilo�ci surowc�w.
		* \return Czas budowy dla podanej ilo�ci u�ytych surowc�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Czas pobierzCzasRozbudowy() const override;

		/**
		* \brief Metoda kopiuj�ca obiekt.
		*
		* Metoda kopiuj�ca obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na kopie obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce* kopia() const override;

		/**
		* \brief Metoda dziel�ca obiekt.
		*
		* Metoda dziel�ca klas� wzdl�dem ilo�ci podanej przez argument.
		* Zwr�cony obiekt ma ilo�� r�wn� podan� przez parametr.
		* Obiekt bazowy ma ilo�� zmniejszon� o podan� przez parametr warto��.
		* \param[in] ilosc - Ilo�� obiekt�w wzgl�dem, kt�rego jest podzielony obiekt.
		* \warning Metoda allokuje pami�� dla nowego obiektu, kt�ry musi zosta� zwolniony wywo�aniem delete.
		* \return Wskazanie na podzielony obiekt. Je�eli nie mo�na by�o podzieli� obiektu, zostaje zwr�cony nullptr.
		* \remark Metoda jest tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* \brief Metoda ��cz�ca obiekty.
		*
		* Metoda ��czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Obiekt do po��czenia.
		* \warning Metoda nie zwalnia pami�ci przekazanego obiektu.
		* \return Kiedy obiekty zostan� po��czone, zwracana warto�� to true, w przeciwnym wypadku zwr�cona warto�� to false.
		* \remark Metoda jest tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool polacz(const Obiekt& obiekt) override;

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
		std::string napis() const override;

		/**
		* \brief Metoda wyliczaj�ca obj�to�� surowca.
		*
		* Metoda wylicza obj�to�� dla danego obiektu.
		* \return Obj�to��.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Objetosc pobierzObjetosc()const;

		/**
		* \brief Metoda wyliczaj�ca obj�to�� jednostkow� surowca.
		*
		* Metoda wylicza obj�to�� jednostkow� dla danego obiektu.
		* \return Obj�to��.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Objetosc pobierzObjetoscJednostkowa()const;

		/**
		* \brief Metoda wyliczaj�ca mas� surowca.
		*
		* Metoda wylicza mas� dla danego obiektu.
		* \return Masa.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Masa pobierzMase()const;

	private:
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] ilosc - Ilo�� tworzonego obiektu.
		* \param[in] obiekt - Obiekt na bazie kt�rego jest tworzona aktualna instancja.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce(const STyp::Ilosc& ilosc, const Surowce& obiekt);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] parametryPodstawowe - Podstawowe parametry.
		* \param[in] surowceInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce(const PodstawoweParametry& parametryPodstawowe, const SurowceInfo& surowceInfo);

		const SurowceInfo& surowceInfo_; /// Referencja do obiektu opisowego.
	};
}
