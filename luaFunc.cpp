#include "MaszynaStanow.h"
#include "TestyJednostkowe.h"
#include "Aplikacja.h"
#include "LuaSkrypt.h"
#include "ListaObiektowGui.h"
#include "ListaSurowcowGui.h"
#include "LogListGui.h"
#include "Parser\ParserDokumentXml.h"
#include "UtilsGui.h"
#include "Planeta.h"

/** @defgroup group1 Funkcje eksportowane
* \brief Funkcje eksportowane
* \details Lista wszystkich funkcji oraz struktur jakie s� udost�pnione w celu zaprogramowania zachowa� gry.
* Mo�na u�ywa� tych obiekt�w w skryptach lua jak i w plikach dll pod��czonych jako skrypty.
*  @{
*/

extern "C"{

	/**
	* \brief Funkcja od��czaj�ca okno komunikat�w.
	*
	* Funkcja od��cza okno komunikat�w od okna g��wnego.
	* Powoduje to, �e okno nie dostanie kolejnego komunikatu logu dopuki nie zostanie ponownie pod��czone.
	* \author Daniel Wojdak
	* \version 1
	* \date 16-07-2014
	* \deprecated Funkcjonalno�� zostanie zautomatyzowana.
	*/
	__declspec(dllexport) void __cdecl odlaczOknoKomunikatow()
	{
		SpEx::UtilsGui::odlaczOknoKomunikatow();
	}

	/**
	* \brief Funkcja pod��cza okno komunikat�w.
	*
	* Funkcja pod��cza okno komunikat�w do okna g��wnego.
	* Powoduje to, �e okno dostaje kolejnego komunikaty log�w dopuki nie zostanie od�aczone.
	* Je�eli nie uda si� pod��czy� okna log�w, wtedy ustawiane jest puste okno.
	* \param[in] idOkna - Identyfikator ekranu, na kt�rym znajduje si� kontrolka.
	* \param[in] widzet - Nazwa identyfikuj�ca kontrolk�.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \deprecated Funkcjonalno�� zostanie zautomatyzowana.
	*/
	__declspec(dllexport) void __cdecl podlaczOknoKomunikatow( int idOkna, const char * widzet )
	{
		SpEx::UtilsGui::ustawOknoKomunikatow(idOkna,widzet);
	}

	/**
	* \brief Funkcja wysy�a komunikat do kontrolki wy�wietlaj�cej logi.
	*
	* Funkcja wysy�a komunikat, przekazany w parametrze, do kontrolki przystosowanej do wy�wietlania log�w. 
	* Kontrolka musi by� pod��czona za pomoc� metody podlaczOknoKomunikatow.
	* Je�eli nie ma �adnej pod��czonej kontrolki funkcja nie wykonuje �adnej akcji.
	* \param[in] typ - Typ wysy�anego komunikatu.
	* \param[in] komunikat - Tre�� wysy�anego komunikatu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl logujWOknieKomunikatow(unsigned int typ, const char * komunikat)
	{
		SpEx::UtilsGui::logToGUI(typ,komunikat);
	}

	/**
	* \brief Funkcja dodaje ekran do stosu.
	*
	* Funkcja dodaje ekran, o podanym id, na wierzch stosu wy�wietlanych ekran�w.
	* \param[in] id - Identyfikator ekranu.
	* \return Je�eli uda si� doda� ekran zwracana jest warto�� true. Je�eli ekran nie zostanie znaleziony zwracana jest warto�c false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl ustawOkno(int id)
	{
		return SpEx::MaszynaStanow::pobierzInstancje().kolejkujOkno(id);
	}

	/**
	* \brief Funkcja zdejmuje ekran z wierzchu stosu.
	*
	* Funkcja zdejmuje ekran z wierzchnu stosu.
	* \return Je�eli uda si� zdj�� ekran zwracana jest warto�� true. Je�eli stos jest pusty zwracana jest warto�� false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl zdejmijOkno()
	{
		return SpEx::MaszynaStanow::pobierzInstancje().zdejmijOkno();
	}

	/**
	* \brief Funkcja pobiera zdarzenie.
	*
	* Funkcja pobiera zdarzenie, dla kt�rego jest wykonywana aktualna akcja.
	* Poprawne zdarzenie zostanie pobrane, je�eli akcja jaka jest aktualnie wykonywana jest akcj� zdarzenia. 
	* Schemat kiedy wywo�ywana jest akcja zdarzenia znajduje si� w doc\Schemat\MaszynaStanow\Projekt\AkcjeWStanie.vsd w repozytorium.
	* \param[out] z - Zmienna do kt�rej zostan� zapisane dane zdarzenia. Zmienna pozostaje niezmieniona, je�eli funkcja zwr�ci warto�� false.
	* \return Je�eli uda si� pobra� zdarzenie zwracana jest warto�� true. Je�eli zdarzenie jest niepoprawne zwracana jest warto�� false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl pobierzZdarzenie(struct Zdarzenie_t& z)
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzZdarzenie(z);
	}

	/**
	* \brief Funkcja pobiera poprzedni stan.
	*
	* Funkcja pobiera poprzedni stan z maszyny stan�w. Stan zostanie poprawnie pobrany, je�eli metoda zostanie wykonana w odpowiedniej akcji.
	* \param[out] s - Zmienna do kt�rej zostan� zapisane dane stanu. Zmienna pozostaje niezmieniona, je�eli funkcja zwr�ci warto�� false.
	* \return Je�eli uda si� pobra� stan poprzedni zwracana jest warto�� true. Je�eli stan poprzedni jest niepoprawny zwracana jest warto�� false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl pobierzPoprzedniStan(struct Stan_t& s)
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzPoprzedniStan(s);
	}

	/**
	* \brief Funkcja pobiera aktualny stan.
	*
	* Funkcja pobiera aktualny stan z maszyny stan�w. Stan zostanie poprawnie pobrany, je�eli metoda zostanie wykonana w odpowiedniej akcji.
	* \param[out] s - Zmienna do kt�rej zostan� zapisane dane stanu. Zmienna pozostaje niezmieniona, je�eli funkcja zwr�ci warto�� false.
	* \return Je�eli uda si� pobra� stan aktualny zwracana jest warto�� true. Je�eli stan aktualny jest niepoprawny zwracana jest warto�� false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl pobierzAktualnyStan(struct Stan_t& s)
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzAktualnyStan(s);
	}

	/**
	* \brief Funkcja pobiera nast�pny stan.
	*
	* Funkcja pobiera nast�pny stan z maszyny stan�w. Stan zostanie poprawnie pobrany, je�eli metoda zostanie wykonana w odpowiedniej akcji.
	* \param[out] s - Zmienna do kt�rej zostan� zapisane dane stanu. Zmienna pozostaje niezmieniona, je�eli funkcja zwr�ci warto�� false.
	* \return Je�eli uda si� pobra� stan nast�pny zwracana jest warto�� true. Je�eli stan nast�pny jest niepoprawny zwracana jest warto�� false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl pobierzNastepnyStan(struct Stan_t& s)
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzNastepnyStan(s);
	}

	/**
	* \brief Funkcja dodaje zdarzenie na koniec kolejki.
	*
	* Funkcja wstawia zdarzenie na koniec kolejki zdarze� w maszynie stan�w.
	* \param[in] s - Zmienna przechowuj�ca informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl kolejkujZdarzenie(struct Zdarzenie_t& s)
	{
		SpEx::Zdarzenie z;
		z.idStanu_(s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_(s.idZdarzenia_);
		SpEx::MaszynaStanow::pobierzInstancje().kolejkujZdarzenie(z);
	}

	/**
	* \brief Funkcja dodaje zdarzenie na pocz�tek kolejki.
	*
	* Funkcja wstawia zdarzenie na pocz�tek kolejki zdarze� w maszynie stan�w.
	* \param[in] s - Zmienna przechowuj�ca informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl wstawZdarzenie(struct Zdarzenie_t& s)
	{
		SpEx::Zdarzenie z;
		z.idStanu_(s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_(s.idZdarzenia_);
		SpEx::MaszynaStanow::pobierzInstancje().wstawZdarzenie(z);
	}

	/**
	* \brief Funkcja ustawia nowy stan nast�pny.
	*
	* Funkcja ustawia nowy stan nastepny. Metoda dzia�a tylko w akcji zdarzenia.
	* \param[in] id - Identyfikator stanu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl ustawNowyStanNastepny(int id){
		SpEx::MaszynaStanow::pobierzInstancje().luaStan_.ustawNowyStanNastepny(id);
	}

	/**
	* \brief Funkcja ustawia nowy numer dodatkowy dla stanu nast�pnego.
	*
	* Funkcja ustawia numer dodatkowy dla stanu nast�pnego. Metoda dzia�a tylko w akcji zdarzenia.
	* \param[in] numer - Numer dodatkowy.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl ustawNowyNumerNastepny(int numer){
		SpEx::MaszynaStanow::pobierzInstancje().luaStan_.ustawNowyNumerNastepny(numer);
	}

	/**
	* \brief Funkcja czy�ci stos ekran�w.
	*
	* Funkcja usuwa wszystkie ekrany z aktualnego stosu ekran�w.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl wyczyscListeOkien()
	{
		SpEx::MaszynaStanow::pobierzInstancje().wyczyscKolejkeOkien();
	}

	/**
	* \brief Funkcja uruchamiaj�ca testy jednostkowe.
	*
	* Funkcja wykonuje testy jednostkowe aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \deprecated Funkcjonalno�� zostanie usuni�ta w wersji Release.
	*/
	__declspec(dllexport) void __cdecl testyJednostkowe()
	{
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
	}

	/**
	* \brief Funkcja dodaj�ca zadanie do wykonania.
	*
	* Funkcja zleca wykonanie zadania jednemu z w�tk�w w puli przeznaczonych do wykonywania zada� wymagaj�cych obliczoniowo lub oczekuj�cych na akcje z zewn�trz.
	* Funkcja nieblokuj�ca. Dodaje zadanie do listy i kontynuuje wykonywanie. Zadanie wykonuje si� r�wnolegle.
	* \param[in] plik - Plik ze skryptem lua.
	* \param[in] funkcja - Nazwa funkcji jaka ma zosta� wywo�ana. Je�eli ma zosta� wykonany ca�y plik nale�y poda� warto�� nullptr.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcjonalno�� zostanie poprawiona. Zostanie rozci�gni�ta na wszysktie typy skrypt�w. Aktualnie u�ywa jest tylko dla skrytp�w lua.
	* \todo Rozsze�y� na wiele typ�w skrypt�w.
	*/
	__declspec(dllexport) void __cdecl zlecZadanie(const char *plik, const char *funkcja)
	{
		std::string sPlik, sFunkcja;
		auto& maszynaStanow = SpEx::MaszynaStanow::pobierzInstancje();

		if (plik){
			sPlik.append(plik);
		}

		if (funkcja){
			sFunkcja.append(funkcja);
		}
		std::function<void()> lambda = [sPlik, sFunkcja](void)->void{
			std::shared_ptr<SpEx::Skrypt> luaSkrypt = 
				SpEx::Aplikacja::pobierzInstancje().fabrykator_.TworzSkrypt(sPlik);
			if (luaSkrypt){
				luaSkrypt->wykonaj();
				luaSkrypt->wykonaj(sFunkcja);
			}
			return;
		};
		SpEx::Zadanie zadanie(lambda);
		maszynaStanow.dodajZadanie(zadanie);
	}

	/**
	* \brief Funkcja inicjuj�ca zamykanie aplikacji.
	*
	* Funkcja rozpoczyna sekwencj� krok�w prowadz�c� do zamkni�cia aplikacji. Po wykonaniu tej metody nie ma mo�liwo�ci przerwania operacji zamykania.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl zamknijAplikacje()
	{
		SpEx::MaszynaStanow::pobierzInstancje().inicjujZamykanie();
	}

	/**
	* \brief Funkcja wysy�a komunikat do logu.
	*
	* Funkcja wysy�a komunikat do log�w aplikacji.
	* \param[in] komunikat - Tre�� komunikatu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl loguj(const char *komunikat)
	{
		if (komunikat)
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, komunikat);
	}

	/**
	* \brief Funkcja wczytuj�ca dane opisowe obiekt�w gry oraz obiekty lokacji.
	*
	* Funkcja wczytuje lokacje oraz obiekty opisowe gry.
	* \param[in] plik - Nazwa pliku z danymi.
	* \return Zwracana jest warto�� true, je�eli uda si� wczyta�. Zwracana jest warto�� false, je�eli wyst�pi� b��d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl zaladujGre(const char *plik){
		if (plik){
			SPar::ParserDokumentXml dokument;
			if (dokument.odczytaj(plik)){
				auto root = dokument.pobierzElement(WEZEL_XML_ROOT);
				if (root){
					return SpEx::Aplikacja::pobierzInstancje().wczytajGre(root);
				}
			}
		}
		return true;
	}

	/**
	* \brief Funkcja wczytuj�ca ponownie ekran.
	*
	* Funkcja zleca zadanie dla w�tku graficznego, aby ponownie wczyta� ekran o podanym id.
	* \param[in] id - Identyfikator ekranu.
	* \warning Funckja dodaje zadanie do w�tku graficznego!
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl przeladujOkno(int id){
		SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().dodajZadanie(SpEx::Zadanie(
			std::function<void()>(
				std::bind(
					&SpEx::OknoGry::przeladujEkran,
					&SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry(),
					STyp::Identyfikator(id))
				))
			);
	}

	/**
	* \brief Funkcja logowania.
	*
	* Funkcja loguje u�ytkownika do aplikacji.
	* \param[in] kontrolkaNazwy - Nazwa kontrolki zawieraj�cej nazw� u�ytkownika.
	* \param[in] kontrolkaHasla - Nazwa kontrolki zawieraj�cej has�o u�ytkownika.
	* \return Zwracana jest warto�� true, je�eli uda si� zalogowa�. Zwracana jest warto�� false, je�eli wyst�pi� b��d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcja wysy�a komunikaty loguj�ce do GUI. 
	*/
	__declspec(dllexport) bool __cdecl zaloguj(const char *kontrolkaNazwy, const char *kontrolkaHasla){
		if (kontrolkaNazwy && kontrolkaHasla){
			auto nazwa = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaNazwy);
			auto haslo = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaHasla);
			if (nazwa != nullptr && haslo != nullptr){
				std::string hash(haslo->getText());
				if (!(nazwa->getText().isEmpty() || hash.empty())){
					SpEx::Utils::sha3(hash);
					if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().logowanie(nazwa->getText(), hash)){
						return true;
					}
					else{
						SpEx::UtilsGui::logToGUI(0, "Nie uda�o si� zalogowa�!");
					}
				}
				else{
					SpEx::UtilsGui::logToGUI(0, "Brak has�a lub loginu!");
				}
			}
			else{
				SpEx::UtilsGui::logToGUI(0, "Brak widzetu has�a lub loginu!");
			}
		}
		else{
			SpEx::UtilsGui::logToGUI(0, "Brak nazwy widzetu has�a lub loginu!");
		}
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Nie uda�o si� zalogowa�!");
		return false;
	}

	/**
	* \brief Funkcja tworzenia nowego u�ytkownika.
	*
	* Funkcja tworzy nowego u�ytkownika i loguje go do aplikacji.
	* \param[in] kontrolkaNazwy - Nazwa kontrolki zawieraj�cej nazw� u�ytkownika.
	* \param[in] kontrolkaHasla - Nazwa kontrolki zawieraj�cej has�o u�ytkownika.
	* \return Zwracana jest warto�� true, je�eli uda si� stworzy� u�ytkownika i zalogowa�. Zwracana jest warto�� false, je�eli wyst�pi� b��d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcja wysy�a komunikaty loguj�ce do GUI.
	*/
	__declspec(dllexport) bool __cdecl nowyGracz(const char *kontrolkaNazwy, const char *kontrolkaHasla){
		if (kontrolkaNazwy && kontrolkaHasla ){
			auto nazwa = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaNazwy);
			auto haslo = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaHasla);
			SpEx::UtilsGui::logToGUI(1, "Inicjowanie tworzenia gracza.");
			if (nazwa != nullptr && haslo != nullptr){
				std::string hash(haslo->getText());
				if (nazwa->getText().isEmpty() || hash.empty()){
					SpEx::UtilsGui::logToGUI(0, "Brak has�a lub nazwy gracza.");
					return false;
				}

				SpEx::Utils::sha3(hash);
				if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzIloscGalaktyk() <= 0){
					SpEx::UtilsGui::logToGUI(1, "Generowanie galaktyki.");
					if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().generujNowaGalaktyke()){
						SpEx::UtilsGui::logToGUI(0, "B��d generowania galaktyki.");
						return false;
					}
				}
				SpEx::UtilsGui::logToGUI(1, "Tworzenie nowego gracza.");
				if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().nowyGracz(nazwa->getText(), hash)){
					SpEx::UtilsGui::logToGUI(0, "B��d tworzenia gracza.");
					return false;
				}

				SpEx::UtilsGui::logToGUI(1, "Logowanie do gry.");
				if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().logowanie(nazwa->getText(), hash)){
					SpEx::UtilsGui::logToGUI(0, "B��d logowania do gry.");
					return false;
				}
				
				SpEx::UtilsGui::logToGUI(1, "Ustawianie podstawowych danych.");
				if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika()){
					SpEx::UtilsGui::logToGUI(1, "Generowanie galaktyki.");
					if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().generujNowaGalaktyke()){
						SpEx::UtilsGui::logToGUI(0, "B��d generowania galaktyki.");
						return false;
					}

					SpEx::UtilsGui::logToGUI(1, "Ustawianie podstawowych danych.");
					if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika()){
						SpEx::UtilsGui::logToGUI(0, "B��d przypisywania planety do u�ytkownika.");
						return false;
					}
				}

				SpEx::UtilsGui::logToGUI(1, "Zapisywanie wprowadzonych danych.");
				if (SpEx::Aplikacja::pobierzInstancje().zapiszGre(nazwa->getText(), hash)){

					SpEx::UtilsGui::logToGUI(1, "Uko�czono.");
					return true;
				}
			}
			else{
				SpEx::UtilsGui::logToGUI(0, "Brak kontrolki has�a lub nazwy gracza.");
			}

		}

		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Nie uda�o si� stworzy� nowego gracza!");
		SpEx::UtilsGui::logToGUI(0, "Nie uda�o si� stworzy� nowego gracza!");
		return false;
	}

	/**
	* \brief Funkcja usuwaj�ca u�ytkownika.
	*
	* Funkcja usuwa wszelkie informacje o u�ytkowniku z aplikacji.
	* \param[in] kontrolkaNazwy - Nazwa kontrolki zawieraj�cej nazw� u�ytkownika.
	* \param[in] kontrolkaHasla - Nazwa kontrolki zawieraj�cej has�o u�ytkownika.
	* \return Zwracana jest warto�� true, je�eli uda si� usun��. Zwracana jest warto�� false, je�eli wyst�pi� b��d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl usunGracza(const char *kontrolkaNazwy, const char *kontrolkaHasla){
		if (kontrolkaNazwy && kontrolkaHasla){
			auto nazwa = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaNazwy);
			auto haslo = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaHasla);
			if (nazwa != nullptr && haslo != nullptr){
				std::string hash(haslo->getText());
				SpEx::Utils::sha3(hash);
				if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().usunGracza(nazwa->getText(), hash)){
					return true;
				}
			}
		}
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Nie uda�o si� usun�� gracza!");
		return false;
	}

	/**
	* \brief Funkcja dodaj�ca zadanie do wykonania w w�tku graficznym.
	*
	* Funkcja zleca wykonanie zadania w w�tku graficznym.
	* Funkcja nieblokuj�ca. Dodaje zadanie do listy i kontynuuje wykonywanie.
	* \warning Funckja dodaje zadanie do w�tku graficznego!
	* \warning Zadanie wymagaj�ce obliczeniowo mo�e powodowa� zamro�enie okna aplikacji. Nale�y u�ywa� tej funkcjonalno�ci tylko w sytuacjach koniecznych.
	* \param[in] plik - Plik ze skryptem lua.
	* \param[in] funkcja - Nazwa funkcji jaka ma zosta� wywo�ana. Je�eli ma zosta� wykonany ca�y plik nale�y poda� warto�� nullptr.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcjonalno�� zostanie poprawiona. Zostanie rozci�gni�ta na wszysktie typy skrypt�w. Aktualnie u�ywa jest tylko dla skrytp�w lua.
	* \todo Rozsze�y� na wiele typ�w skrypt�w.
	*/
	__declspec(dllexport) void __cdecl zlecZadanieGraficzne(const char *plik, const char *funkcja)
	{
		std::string sPlik, sFunkcja;
		auto & maszynaStanow = SpEx::MaszynaStanow::pobierzInstancje();

		if (plik){
			sPlik.append(plik);
		}

		if (funkcja){
			sFunkcja.append(funkcja);
		}

		std::function<void()> lambda = [sPlik, sFunkcja]()->void{
			std::shared_ptr<SpEx::Skrypt> luaSkrypt = SpEx::Aplikacja::pobierzInstancje().fabrykator_.TworzSkrypt(sPlik);
			if (luaSkrypt){
				luaSkrypt->wykonaj();
				luaSkrypt->wykonaj(sFunkcja);
			}
		};
		SpEx::Zadanie zadanie(lambda);
		maszynaStanow.pobierzOknoGry().dodajZadanie(zadanie);
	}

	/**
	* \brief Funkcja ustawiaj�ca w�a�ciwo�� kontrolki.
	*
	* Funkcja ustawia w�a�ciwo�� kontrolki. Lista w�a�ciwo�ci b�dzie dodana wraz z rozbudow� dokumentacji.
	* \param[in] ekran - Identyfikator ekranu, na kt�rym znajduje si� kontrolka.
	* \param[in] kontrolka - Nazwa kontrolki.
	* \param[in] nazwaWlasciwosci - Nazwa w�a�ciwo�ci.
	* \param[in] nowaWartosc - Nowa warto�� w�a�ciwo�ci.
	* \return Zwracana jest warto�� true, je�eli uda si� ustawi� w�a�ciwo��. Zwracana jest warto�� false, je�eli wyst�pi� b��d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl ustawWlasciwosc(int ekran, const char *kontrolka, const char *nazwaWlasciwosci, const char *nowaWartosc){
		if (!kontrolka && !nazwaWlasciwosci)
			return false;
		SpEx::OknoGry::EkranPtr ekranPtr;
		if ( ekran < 0 )
			ekranPtr = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().pobierzStosEkranow().back();
		else
			ekranPtr = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().pobierzEkran(ekran);

		if (!ekranPtr)
			return false;
		
		std::string value;
		if (nowaWartosc)
			value.append(nowaWartosc);
		auto widget = ekranPtr->pobierzGUI().get<tgui::Widget>(kontrolka);
		if (!widget)
			return false;
		return widget->setProperty(nazwaWlasciwosci,value);
	}

	/**
	* \brief Funkcja pobieraj�ca nazw� aktualnie zalogowanego u�ytkownika.
	*
	* Funkcja pobiera nazw� uzytkownika, kt�ry jest aktualnie zalogowany do aplikacji.
	* \return Zwracana jest nazwa u�ytkownika, je�eli jest zalogowany. Zwracany jest nullptr, je�eli nie ma zalogowanego u�ytkownika.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) const char * __cdecl pobierzNazweAktualnegoGracza(){
		if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().czyZalogowano())
			return SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzNazweUzytkownika()().c_str();
		else
			return nullptr;
	}

	/**
	* \brief Funkcja buduj�ca obiekt na planecie.
	*
	* Funkcja buduje obiekt na aktualnie aktywnej planecie.
	* \param[in] id - identyfikator obiektu.
	* \param[in] ilosc - parametr nieu�ywany.
	* \return Zwracana jest warto�� true, je�eli uda si� wybudowa� obiekt. Zwracana jest warto�� false, je�eli wyst�pi� b��d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl wybudujObiekt(int id, int ilosc){
		try{
			auto &gra = SpEx::Aplikacja::pobierzInstancje().pobierzGre();
			if (gra.czyZalogowano()){
				auto &planeta = gra.pobierzUzytkownika().pobierzPlanete();
				planeta.wybuduj(id, SpEx::PodstawoweParametry::wartoscJednostkowaParametru(gra.pobierzObiekt(id).pobierzTypAtrybutu()));
			}
		}
		catch (STyp::Wyjatek& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
		}
		catch (std::exception& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
		}
		return false;
	}
	
	/**
	* \brief Funkcja aktualizuj�ca dane listy obiekt�w.
	*
	* Funkcja aktualizuje dane listy obiekt�w w przeznaczonej do tego specjalnej kontrolce.
	* \param[in] idEkranu - identyfikator ekranu, kt�ry zawiera kontrolk�.
	* \param[in] nazwaKontrolki - nazwa kontrolki.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl aktualizujDaneListyObiektow(int idEkranu, const char *nazwaKontrolki)
	{
		try{
			auto &gra = SpEx::Aplikacja::pobierzInstancje().pobierzGre();
			if (nazwaKontrolki && gra.czyZalogowano()){
				auto &planeta = gra.pobierzUzytkownika().pobierzPlanete();
				auto ekran = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().pobierzEkran(idEkranu);
				if (ekran){
					auto kontrolka = ekran->pobierzGUI().get<tgui::ListaObiektowGui>(nazwaKontrolki);
					if (kontrolka != nullptr){
						kontrolka->aktualizacjaDanych(planeta);
					}
				}
			}
		}
		catch (STyp::Wyjatek& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
		}
		catch (std::exception& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
		}
	}

	/**
	* \brief Funkcja aktualizuj�ca dane listy surowc�w.
	*
	* Funkcja aktualizuje dane listy surowc�w w przeznaczonej do tego specjalnej kontrolce.
	* \param[in] idEkranu - identyfikator ekranu, kt�ry zawiera kontrolk�.
	* \param[in] nazwaKontrolki - nazwa kontrolki.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl aktualizujDaneListySurowcow(int idEkranu, const char *nazwaKontrolki)
	{
		try{
			auto &gra = SpEx::Aplikacja::pobierzInstancje().pobierzGre();
			if (nazwaKontrolki && gra.czyZalogowano()){
				auto &planeta = gra.pobierzUzytkownika().pobierzPlanete();
				auto ekran = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().pobierzEkran(idEkranu);
				if (ekran){
					auto kontrolka = ekran->pobierzGUI().get<tgui::ListaSurowcowGui>(nazwaKontrolki);
					if (kontrolka != nullptr){
						kontrolka->ustawDane(planeta);
					}
				}
			}
		}
		catch (STyp::Wyjatek& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
		}
		catch (std::exception& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
		}
	}
}

/** @} */