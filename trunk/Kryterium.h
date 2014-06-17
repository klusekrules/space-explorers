#pragma once
#include "Logger\LoggerInterface.h"
#include "Serializacja.h"
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
		//--- Definicje typ�w lokalnych ---

		enum TypAtrybutu
		{
			POZIOM,
			ILOSC
		};

		typedef union AtrybutKryterium
		{
			STyp::Poziom::nazwa_typu poziom;
			STyp::Ilosc::nazwa_typu ilosc;
		};

		//--- Metody domy�lne ---

		virtual ~Kryterium() = default;

		Kryterium(const Kryterium&) = default;

		Kryterium& operator=(const Kryterium&) = default;

		//--- Metody usuni�te ---

		//--- Metody statyczne ---
		
		//--- Konstruktory ---
		
		Kryterium(Kryterium&&);
		
		/**
		* \brief Konstruktor
		*
		* Podstawowy konstruktor obiektu. Ustawia poziom i identyfikator planety, do kt�rej przypisany jest dany obiekt.
		* \param[in] atrybut - Atrybut obiektu.
		* \param[in] typ - typ atrybutu
		* \param[in] identyfikator - Identyfikator obiektu.
		*/
		Kryterium(const AtrybutKryterium& atrybut, TypAtrybutu typ, const STyp::Identyfikator& identyfikator);

		/**
		* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
		* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
		*/
		explicit Kryterium(XmlBO::ElementWezla wezel);

		//--- Destruktor ---

		//--- Operatory ---
		Kryterium& operator=(Kryterium&&);

		//--- Metody wirtualne ---

		//--- Metody przeci��one ---

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

		//--- Metody typu Get/Set ---

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca atrybut obiektu.
		*/
		const AtrybutKryterium& pobierzAtrybut() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] atrybut - Nowa warto�� atrybutu obiektu.
		*/
		void ustawAtrybut(const AtrybutKryterium& atrybut);

		/**
		* \brief Metoda pobieraj�ca atrybut.
		*
		* Metoda pobiera atrybut obiektu.
		* \return Metoda zwraca identyfiaktor planety rodzica obiektu.
		*/
		const STyp::Identyfikator& pobierzIdentyfikator() const;

		/**
		* \brief Metoda ustawiaj�ca atrybut.
		*
		* Metoda ustawiaj�ca atrybut obiektu.
		* \param[in] identyfikator - Nowa warto�� identyfikatora planety rodzica obiektu.
		*/
		void ustawIdentyfikator(const STyp::Identyfikator& identyfikator);
		
		/**
		* \brief Metoda pobieraj�ca typ atrybutu podstawowego.
		*
		* Metoda pobiera typ atrybutu podstawowego przechowywwanego przez klas�.
		* \return Typ atrybutu podstawowego.
		*/
		TypAtrybutu typAtrybutu()const;

		//--- Pozosta�e metody ---

		STyp::Poziom pobierzPoziom()const;

		STyp::Ilosc pobierzIlosc()const;

		
		
	private:

		//--- Atrybuty ---
		TypAtrybutu typAtrybutu_; /// Typ atrybutu podstawowego.
		AtrybutKryterium atrybutPodstawowy_;/// Atrybut poziomu obiektu.
		STyp::Identyfikator identyfikator_;/// Atrybut identyfikatora obiektu.
	};
}