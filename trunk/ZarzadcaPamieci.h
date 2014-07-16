#pragma once
#include <memory>
#include <unordered_map>
#include "Galaktyka.h"
#include "GeneratorUkladow.h"
#include "FabrykaSkryptow.h"
#include <vector>
#include "UstawieniaAplikacji.h"

namespace SpEx{
	/**
	* \brief Klasa zarzadzajaca lokacjami
	*
	* Klasa zarzadza wczytanymi lokacjami. Wczytuje na tylko uzywane planety i uklady.
	* Nie usuwa ich z czasem ¿ycia programu
	* \author Daniel Wojdak
	* \version 2
	* \date 01-07-2014
	* \todo Usuwanie nieuzywanych lokacji.
	*/
	class ZarzadcaPamieci :
		virtual public Serializacja
	{
	public:
		/**
		* \brief Struktura pomocnicza przechowujaca wczytan¹ planetê.
		*
		* Struktura przechowuje planetê, je¿eli zosta³a wczytana oraz identyfikator uk³adu rodzica.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjPlaneta{
			STyp::Identyfikator idUkladu_; /// Identyfikator uk³adu. U¿ywane do wczytania odpowiedniego uk³adu do za³adowania planety.
			std::shared_ptr< Planeta > planeta_; /// wskaŸnik na planetê.
			bool wolna_; /// Informacja o przynaleznosci planety do gracza.
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytany uk³ad.
		*
		* Struktura przechowuje uk³ad, je¿eli zosta³ wczytany, identyfikator galaktyki rodzica oraz przynale¿ne planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjUklad{
			STyp::Identyfikator idGalaktyki_; /// Identyfikator Galaktyki. Aktualnie nie u¿ywany.
			std::shared_ptr< UkladSloneczny > uklad_; /// wskaŸnik do uk³adu.
			std::vector< STyp::Identyfikator > planety_; /// Lista przynaleznych planet. U¿ywane przy zapisie informacji do pliku.
		};

		/**
		* \brief Struktura pomocnicza przechowujaca wczytan¹ galaktykê.
		*
		* Struktura przechowuje galaktykê, je¿eli zosta³a wczytana oraz przynale¿ne uk³ady.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-10-2013
		*/
		struct ObjGalakatyka{
			std::shared_ptr< Galaktyka > galaktyka_; /// wskaŸnika na galaktykê. Nieu¿ywany.
			std::vector< STyp::Identyfikator > uklady_; /// Lista uk³adów przynaleznych. Potrzebna do zapisu danych.
		};

		typedef std::unordered_map< STyp::Identyfikator, ObjGalakatyka, STyp::IdTypeHash > Galaktyki; /// Typ listy wszystkich galaktyk.
		typedef std::unordered_map< STyp::Identyfikator, ObjUklad, STyp::IdTypeHash > UkladySloneczne; /// Typ listy wszystkich ukladów.
		typedef std::unordered_map< STyp::Identyfikator, ObjPlaneta, STyp::IdTypeHash > Planety; /// Typ listy wszystkich Planet.

		/**
		* \brief Konstruktor.
		*
		* Bezparametrowy konstruktor obiektu.
		*/
		ZarzadcaPamieci();

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na planetê o wskazanym identyfikatorze.
		* Je¿eli planeta nie jest wczytana, metoda wczytuje ca³y uk³ad i zwraca planetê.
		* \param[in] identyfikator - Identyfikator planety.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::shared_ptr< Planeta > pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na planetê o wskazanym identyfikatorze. Planeta jest oznaczana jako zajêta.
		* Je¿eli planeta nie jest wczytana, metoda wczytuje ca³y uk³ad i zwraca planetê.
		* \param[in] identyfikator - Identyfikator planety.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::shared_ptr< Planeta > pobierzIZarezerwujPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na pierwsz¹ woln¹ planetê. Planeta jest oznaczana jako zajêta.
		* Je¿eli planeta nie jest wczytana, metoda wczytuje ca³y uk³ad i zwraca planetê.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		std::shared_ptr< Planeta > pobierzIZarezerwujPlanete();

		/**
		* \brief Metoda zmienia oznaczenie planety.
		*
		* Metoda zmienia oznaczenie planety jako woln¹.
		* \param[in] identyfikator - Identyfikator planety.
		* \author Daniel Wojdak
		* \version 1
		* \date 01-07-2014
		*/
		void anulujRezerwacjePlanety(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz¹dzancyh przez zarz¹dcê pamiêci.
		* \return Liczba galaktyk.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now¹ galaktykê.
		*
		* Metoda generuje now¹ galaktykê. Zapisuje dane uk³adów do pliku. Nie zapisuje struktury galaktyki,
		* oznacza to ¿e dopiero po zapisie stanu gry ca³oœæ informacji bêdzie zapisana do pliku.
		* \return true je¿eli siê powiedzie, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Metoda zwraca wezel z opisem stanów w maszynie stanu.
		*
		* Metoda zwraca wêze³ zawieraj¹cy opis stanów maszyny stanów.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla pobierzWezelKonfiguracyjnyMaszynyStanow()const;

		/**
		* \brief Metoda zwraca wezel z opisem okien gry.
		*
		* Metoda zwraca wêze³ a opisem okien gry.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla pobierzWezelKonfiguracyjnyOknaGry()const;
		
		/**
		* \brief Metoda tworzy wêze³ gry.
		*
		* Metoda tworzy wêze³ gry do zapisu listy planet, uk³adów i galaktyk.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla tworzWezelGry();

		/**
		* \brief Metoda zapisuje wêze³ gry.
		*
		* Metoda zapisuje wêze³ gry.
		* \return Zwracana jest wartoœæ true, je¿eli zapis siê powiedzie lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		bool zapiszWezelGry();

		/**
		* \brief Metoda otwiera wêze³ gry.
		*
		* Metoda otwiera wêze³ gry z list¹ planet, uk³adów i galaktyk.
		* \return Zwracany jest wêze³, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		XmlBO::ElementWezla otworzWezelGry();
		
		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych w wêŸle przez parametr.
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] identyfikator - Identyfikator typu skryptu.
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(const FabrykaSkryptow::Identyfikator& identyfikator, XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda otwieraj¹ca plik u¿ytkownika
		*
		* Metoda na podstawie nazwy i hashu has³a u¿ytkownika otwiera plik z danymi u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \param[out] nazwaPliku - Nazwa pliku u¿ytkownika.
		* \param[in] tworzPlik - informacje czy ma zostaæ utworzony plik je¿eli nie istnieje.
		* \return nullptr je¿eli hash sie nie zgadza, wska¿nik na dokument.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::shared_ptr<SPar::ParserDokument> plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik = true) const;

		/**
		* \brief Metoda inicjuj¹ca dane zarz¹dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz¹dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz¹ca œlad stosu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		void zaladujPliki(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos);

		/**
		* \brief Destruktor.
		*
		* Domyœlny destruktor obiektu.
		*/
		virtual ~ZarzadcaPamieci() = default;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
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
		* \version 2
		* \date 01-07-2014
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;
		
		/**
		* \brief Metoda czyœci dane zarz¹dcy.
		*
		* Metoda czyœci dane zarz¹dcy.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		void wyczyscDane();

	private:

		/**
		* \brief Metoda wczytuje uk³ad z pliku do pamiêci.
		*
		* Metoda wczytuje uk³ad o podanym identyfikatorze z pliku w formacie {identyfikator}.xml
		* \param[in] identyfikator - Numer identyfikuj¹cy uk³ad s³oneczny.
		* \return true je¿eli uda siê wczytaæ, false w przeciwnym wypaku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		bool wczytajUkladSloneczny(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda wczytuje zapisuje do pliku.
		*
		* Metoda zapisuje uk³ad do pliku w formacie {identyfikator}.xml
		* \param[in] uklad - wskaŸnik na uk³ad s³oneczny.
		* \return true je¿eli uda siê zapisaæ, false w przeciwnym wypaku.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		bool zapiszUkladSloneczny(std::shared_ptr<UkladSloneczny> uklad) const;

		/**
		* \brief Metoda generuje adres pliku uk³adu.
		*
		* Metoda generuje adres pliku do zapisu dok³adnych danych planet w uk³adzie o podanym w parametrze identyfikatorze.
		* \param[in] identyfikator - identyfikator uk³adu.
		* \author Daniel Wojdak
		* \version 2
		* \date 01-07-2014
		*/
		std::string generujNazwePlikuUkladuSlonecznego(const STyp::Identyfikator& identyfikator) const;

		GeneratorUkladow generator_; /// Obiekt generuj¹cy planety, uk³ady, galaktyki.
		FabrykaSkryptow fabrykaSkryptow_; /// Obiekt tworz¹cy instancje skryptów. Implementuje wzorzec fabryki.
		Galaktyki galaktyki_; /// Lista galaktyk.
		UkladySloneczne ukladySloneczne_; /// Lista uk³adów.
		Planety planety_; /// Lista planet.

		std::shared_ptr<SPar::ParserDokument> dokumentMaszynyStanow_; /// Dokument z opisem stanów.
		std::shared_ptr<SPar::ParserDokument> dokumentOknaGry_; /// Dokument z list¹ okien.
		std::shared_ptr<SPar::ParserDokument> dokumentGry_; /// Dokument z opisem obiektów gry.

		std::string folderPlikuUzytkownika_; /// Adres folderu z plikami u¿ytkownika.
		std::string folderPlikuUkladu_; /// Adres folderu z plikami opisuj¹cymi planety.
		std::string adresPlikuGry_; /// Adres pliku z opisem obiektów gry.		
	};
}
