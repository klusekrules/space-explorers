#pragma once
#include "Logger\LoggerInterface.h"
#include "Utils\Serializacja.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa zawieraj�ca podstawowe parametry.
	*
	* Przechowywane przez t� klas� atrybuty, s� podstawowymi parametrami
	* potrzebnymi do wyliczenia warto�ci atrybut�w obiekt�w pochodnych.
	* \author Daniel Wojdak
	* \version 1
	* \date 22-07-2013
	*/
	class Kryterium :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		/**
		* \brief Typy atrybut�w kryterium.
		*
		* Dopuszczalne typy atrybut�w kryterium.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		enum TypAtrybutu
		{
			POZIOM,
			ILOSC
		};

		/**
		* \brief Typ atrybutu kryterium
		*
		* Typ atrybutu kryterium.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		typedef union AtrybutKryterium
		{
			STyp::Poziom::nazwa_typu poziom;
			STyp::Ilosc::nazwa_typu ilosc;
		};
		
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Kryterium() = default;

		/**
		* \brief Domy�lny konstruktor kopiuj�cy.
		*
		* Domy�lny konstruktor kopiuj�cy.
		*/
		Kryterium(const Kryterium&) = default;

		/**
		* \brief Domy�lny operator kopiuj�cy.
		*
		* Domy�lny operator kopiuj�cy.
		*/
		Kryterium& operator=(const Kryterium&) = default;
		
		/**
		* \brief Konstruktor przenosz�cy.
		*
		* Konstruktor przenosz�cy.
		* \param[inout] obiekt - Obiekt �r�d�owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		Kryterium(Kryterium&& obiekt);
		
		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia poziom i identyfikator planety, do kt�rej przypisany jest dany obiekt.
		* \param[in] atrybut - Atrybut obiektu.
		* \param[in] typ - typ atrybutu
		* \param[in] identyfikator - Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		Kryterium(const AtrybutKryterium& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikator);

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		explicit Kryterium(XmlBO::ElementWezla wezel);

		/**
		* \brief Operator przenosz�cy.
		*
		* Operator przenosz�cy.
		* \param[inout] obiekt - Obiekt �r�d�owy.
		* \return Referencja do aktualnego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		Kryterium& operator=(Kryterium&& obiekt);

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
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
		* \date 22-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca atrybut obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const AtrybutKryterium& pobierzAtrybut() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] atrybut - Nowa warto�� atrybutu obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawAtrybut(const AtrybutKryterium& atrybut);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] identyfikator - Nowa warto�� identyfikatora planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawIdentyfikator(const STyp::Identyfikator& identyfikator);
		
		/**
		* \brief Metoda pobieraj�ca typ atrybutu podstawowego.
		*
		* Metoda pobiera typ atrybutu podstawowego przechowywwanego przez klas�.
		* \return Typ atrybutu podstawowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		TypAtrybutu typAtrybutu()const;

		/**
		* \brief Metoda pobieraj�ca poziom.
		*
		* Metoda pobiera poziom.
		* \return Poziom obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		STyp::Poziom pobierzPoziom()const;

		/**
		* \brief Metoda pobieraj�ca ilo��.
		*
		* Metoda pobiera ilo��.
		* \return Ilo�� obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		STyp::Ilosc pobierzIlosc()const;
						
	private:				
		TypAtrybutu typAtrybutu_; /// Typ atrybutu podstawowego.
		AtrybutKryterium atrybutPodstawowy_;/// Atrybut poziomu obiektu.
		STyp::Identyfikator identyfikator_;/// Atrybut identyfikatora obiektu.
	};
}