#pragma once
#include "Logger\LoggerInterface.h"
#include "Planeta.h"

namespace SpEx{
	/**
	* \brief Klasa reprezentuj¹ca u¿ytkownika.
	*
	* Klasa u¿ytkownika przechowuje planety oraz wszystkie potrzebne dane
	* \author Daniel Wojdak
	* \version 2
	* \date 14-07-2014
	*/
	class Uzytkownik :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		typedef std::map<STyp::Identyfikator, std::shared_ptr<Planeta> > Planety;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] gra - instancja gry dla u¿ytkownika..
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		Uzytkownik(Gra& gra);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Uzytkownik() = default;

		/**
		* \brief Metoda zwracaj¹ca planetê nale¿¹c¹ do u¿ytkownika.
		*
		* Metoda pobiera planete nale¿¹c¹ do u¿ytkownika. Nie usuwa jej z listy jego planet.
		* \param[in] identyfikator - Numer identyfikuj¹cy planetê.
		* \return Referencja do planety u¿ytkownika.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		Planeta& pobierzPlanete(const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda zwracaj¹ca planetê nale¿¹c¹ do u¿ytkownika.
		*
		* Metoda pobiera planete nale¿¹c¹ do u¿ytkownika. Nie usuwa jej z listy jego planet.
		* \return Referencja do planety u¿ytkownika.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		Planeta& pobierzPlanete();

		/**
		* \brief Metoda pobieraj¹ca nazwê u¿ytkownika.
		*
		* Metoda pobiera nazwê u¿ytkownika.
		*\return Nazwa u¿ytkownika reprezentowanego przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		const STyp::Tekst& pobierzNazweUzytkownika()const;

		/**
		* \brief Metoda ustawiaj¹ca nazwê u¿ytkownika.
		*
		* Metoda ustawia nazwê u¿ytkownika.
		*\param[in] nazwa - Nowa nazwa u¿ytkownika reprezentowanego przez obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		void ustawNazweUzytkownika(const STyp::Tekst& nazwa);

		const STyp::Tekst& pobierzSkrotKlucza() const;

		/**
		* \brief Metoda dodaje palanetê do listy planet u¿ytkownika.
		*
		*  Metoda ustawia w³aœciciela planety na aktualnego u¿ytkownika.
		* \param[in] planeta - Sprytny wskaŸnika na obiekt planety.
		* \return true je¿eli uda siê dodaæ planetê, false je¿eli operacja siê nie powiedzie.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
		*/
		bool dodajPlanete(std::shared_ptr<Planeta> planeta);

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-07-2013
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
		* \date 26-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda odpina planety od w³aœciciela.
		*
		* Metoda odpina wszystkie planety od w³aœciciela czyszcz¹c ich zawartoœæ.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool odpinaniePlanet();

		/**
		* \brief Metoda odpina planetê od w³aœciciela.
		*
		* Metoda odpina planetê o podanym w parametrze identyfikatorze od w³aœciciela czyszcz¹c jej zawartoœæ.
		* \param[in] id - Identyfikator planety.
		* \return Zwracana jest wartoœæ true, je¿eli operacja zakoñczy siê powowdzeniem. Zwracana jest wartoœæ false, je¿eli planeta nie zostanie znaleziona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool odpinaniePlanet(const STyp::Identyfikator& id);

		/**
		* \brief Metoda ustawia now¹ aktywn¹ planetê.
		*
		* Metoda ustawia now¹ aktywn¹ planetê.
		* \param[in] id - Identyfikator planety.
		* \return Zwracana jest wartoœæ true, je¿eli operacja zakoñczy siê powowdzeniem. Zwracana jest wartoœæ false, je¿eli planeta nie zostanie znaleziona.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool ustawPlaneteAktywna(const STyp::Identyfikator& id);

	private:
		STyp::Tekst nazwaUzytkownika_; /// Nazwa u¿ytkownika. Cz³on nazwy pliku z danymi.
		Planety planety_; /// Lista planet u¿ytkownika.
		Gra& instancjaGry; /// Instancja gry do której nale¿y u¿ytkowni.
		STyp::Identyfikator aktywnaPlaneta_; /// Identyfikator aktywnej planety.
		STyp::Tekst skrotKlucza_;
	};
}
