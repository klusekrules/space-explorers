#pragma once
#include "Obiekt.h"
#include "NiezgodnyTypSurowca.h"
#include "PodstawoweParametry.h"
#include "Logger\LoggerInterface.h"

namespace SpEx{
	class SurowceInfo;
	class Ladownia;

	/**
	* \brief Klasa reprezentuj¹ca surowiec.
	*
	* Klasa reprezentuj¹ca surowiec.
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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Surowce() = default;

		/**
		* \brief Operator przypisania.
		*
		* Operator przypisania obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt jaki ma byæ przypisany do klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce& operator=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator równoœci.
		*
		* Operator sprawdzania równoœci obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator==(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator nierównoœci.
		*
		* Operator sprawdzania nierównoœci obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator!=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator s³abej wiêkszoœci.
		*
		* Operator sprawdzania s³abej wiêkszoœci obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator>(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator s³abej mniejszoœci
		*
		* Operator sprawdzania s³abej mniejszoœci obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator<(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator wiêkszoœci.
		*
		* Operator sprawdzania wiêkszoœci obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator>=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator mniejszoœci.
		*
		* Operator sprwadzania mniejszoœci obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt z jakim ma byc porównana klasa.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool operator<=(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator sumy.
		*
		* Operator sumy obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt dodany do aktualnej wartoœci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce operator+(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator przypisania i sumy.
		*
		* Operator przypisania i sumy obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt dodany do aktualnej wartoœci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce& operator+=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator ró¿nicy.
		*
		* Operator ró¿nicy obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt odjêty od aktualnej wartoœci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce operator-(const Surowce& obiekt) const throw (NiezgodnyTypSurowca);

		/**
		* \brief Operator przypisania i ró¿nicy.
		*
		* Operator przypisania i ró¿nicy obiektu surowca. Je¿eli typ surowca jest ró¿ny wyrzucany jest wyj¹tek.
		* \param[in] obiekt - Obiekt odjêty od aktualnej wartoœci.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce& operator-=(const Surowce& obiekt) throw (NiezgodnyTypSurowca);

		/**
		* \brief Metoda dodaje obiekt surowca.
		*
		* Metoda dodaj¹ca obiekt surowca. Metoda nie wyrzuca wyj¹tku.
		* \param[in] obiekt - obiekt dodany do aktualnego.
		* \return true je¿eli mo¿na dodaæ obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool Dodaj(const Surowce& obiekt);

		/**
		* \brief Metoda odejmuj¹ca obiekt surowca.
		*
		* Metoda odejmuj¹ca obiekt surowca. Metoda nie wyrzuca wyj¹tku.
		* \param[in] obiekt - obiekt odjêty do aktualnego.
		* \return true je¿eli mo¿na odj¹æ obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool Usun(const Surowce& obiekt);

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy.
		*
		* Metoda pobieraj¹ca obiekt opisowy.
		* \return Obiekt opisowy surowca.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		const SurowceInfo& pobierzSurowceInfo() const;

		/**
		* \brief Metoda informuj¹ca czy obiekt jest typu przyrostowego.
		*
		* Metoda sprawdzaj¹ca czy surowiec jest typu przyrostowego.
		* \return true je¿eli surowiec jest typu przyrostowego, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool czyTypPrzyrostowy()const;

		/**
		* \brief Metoda wyliczaj¹ca czas budowy.
		*
		* Metoda wylicza czas budowy dla takiej obecnej iloœci surowców.
		* \return Czas budowy dla podanej iloœci u¿ytych surowców.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		STyp::Czas pobierzCzasRozbudowy() const override;

		/**
		* \brief Metoda kopiuj¹ca obiekt.
		*
		* Metoda kopiuj¹ca obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na kopie obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce* kopia() const override;

		/**
		* \brief Metoda dziel¹ca obiekt.
		*
		* Metoda dziel¹ca klasê wzdlêdem iloœci podanej przez argument.
		* Zwrócony obiekt ma iloœæ równ¹ podan¹ przez parametr.
		* Obiekt bazowy ma iloœæ zmniejszon¹ o podan¹ przez parametr wartoœæ.
		* \param[in] ilosc - Iloœæ obiektów wzglêdem, którego jest podzielony obiekt.
		* \warning Metoda allokuje pamiêæ dla nowego obiektu, który musi zostaæ zwolniony wywo³aniem delete.
		* \return Wskazanie na podzielony obiekt. Je¿eli nie mo¿na by³o podzieliæ obiektu, zostaje zwrócony nullptr.
		* \remark Metoda jest tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce* podziel(const STyp::Ilosc& ilosc) override;

		/**
		* \brief Metoda ³¹cz¹ca obiekty.
		*
		* Metoda ³¹czy obiekt bazowy z obiektem przekazanym przez parametr.
		* \param[in] obiekt - Obiekt do po³¹czenia.
		* \warning Metoda nie zwalnia pamiêci przekazanego obiektu.
		* \return Kiedy obiekty zostan¹ po³¹czone, zwracana wartoœæ to true, w przeciwnym wypadku zwrócona wartoœæ to false.
		* \remark Metoda jest tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		bool polacz(const Obiekt& obiekt) override;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
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
		* \date 25-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda wyliczaj¹ca objêtoœæ surowca.
		*
		* Metoda wylicza objêtoœæ dla danego obiektu.
		* \return Objêtoœæ.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Objetosc pobierzObjetosc()const;

		/**
		* \brief Metoda wyliczaj¹ca objêtoœæ jednostkow¹ surowca.
		*
		* Metoda wylicza objêtoœæ jednostkow¹ dla danego obiektu.
		* \return Objêtoœæ.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-07-2014
		*/
		STyp::Objetosc pobierzObjetoscJednostkowa()const;

		/**
		* \brief Metoda wyliczaj¹ca masê surowca.
		*
		* Metoda wylicza masê dla danego obiektu.
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
		* \param[in] ilosc - Iloœæ tworzonego obiektu.
		* \param[in] obiekt - Obiekt na bazie którego jest tworzona aktualna instancja.
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
		* \param[in] surowceInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2013
		*/
		Surowce(const PodstawoweParametry& parametryPodstawowe, const SurowceInfo& surowceInfo);

		const SurowceInfo& surowceInfo_; /// Referencja do obiektu opisowego.
	};
}
