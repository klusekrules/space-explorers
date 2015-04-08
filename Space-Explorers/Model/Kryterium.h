#pragma once
#include "Logger\LoggerInterface.h"
#include "Utils\Serializacja.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	/**
	* \brief Klasa zawieraj¹ca podstawowe parametry.
	*
	* Przechowywane przez tê klasê atrybuty, s¹ podstawowymi parametrami
	* potrzebnymi do wyliczenia wartoœci atrybutów obiektów pochodnych.
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
		* \brief Typy atrybutów kryterium.
		*
		* Dopuszczalne typy atrybutów kryterium.
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
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Kryterium() = default;

		/**
		* \brief Domyœlny konstruktor kopiuj¹cy.
		*
		* Domyœlny konstruktor kopiuj¹cy.
		*/
		Kryterium(const Kryterium&) = default;

		/**
		* \brief Domyœlny operator kopiuj¹cy.
		*
		* Domyœlny operator kopiuj¹cy.
		*/
		Kryterium& operator=(const Kryterium&) = default;
		
		/**
		* \brief Konstruktor przenosz¹cy.
		*
		* Konstruktor przenosz¹cy.
		* \param[inout] obiekt - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		Kryterium(Kryterium&& obiekt);
		
		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia poziom i identyfikator planety, do której przypisany jest dany obiekt.
		* \param[in] atrybut - Atrybut obiektu.
		* \param[in] typ - typ atrybutu
		* \param[in] identyfikator - Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		Kryterium(const AtrybutKryterium& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikator);

		/**
		* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
		* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		explicit Kryterium(XmlBO::ElementWezla wezel);

		/**
		* \brief Operator przenosz¹cy.
		*
		* Operator przenosz¹cy.
		* \param[inout] obiekt - Obiekt Ÿród³owy.
		* \return Referencja do aktualnego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		Kryterium& operator=(Kryterium&& obiekt);

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
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
		* \date 22-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca atrybut obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const AtrybutKryterium& pobierzAtrybut() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] atrybut - Nowa wartoœæ atrybutu obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawAtrybut(const AtrybutKryterium& atrybut);

		/**
		* \brief Metoda pobieraj¹ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda ustawiaj¹ca atrybut.
		*
		* Metoda ustawiaj¹ca atrybut obiektu.
		* \param[in] identyfikator - Nowa wartoœæ identyfikatora planety rodzica obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		void ustawIdentyfikator(const STyp::Identyfikator& identyfikator);
		
		/**
		* \brief Metoda pobieraj¹ca typ atrybutu podstawowego.
		*
		* Metoda pobiera typ atrybutu podstawowego przechowywwanego przez klasê.
		* \return Typ atrybutu podstawowego.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		TypAtrybutu typAtrybutu()const;

		/**
		* \brief Metoda pobieraj¹ca poziom.
		*
		* Metoda pobiera poziom.
		* \return Poziom obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 22-07-2013
		*/
		STyp::Poziom pobierzPoziom()const;

		/**
		* \brief Metoda pobieraj¹ca iloœæ.
		*
		* Metoda pobiera iloœæ.
		* \return Iloœæ obiektu.
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