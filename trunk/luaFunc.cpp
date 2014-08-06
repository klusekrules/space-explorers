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
* \details Lista wszystkich funkcji oraz struktur jakie s¹ udostêpnione w celu zaprogramowania zachowañ gry.
* Mo¿na u¿ywaæ tych obiektów w skryptach lua jak i w plikach dll pod³¹czonych jako skrypty.
*  @{
*/

extern "C"{

	/**
	* \brief Funkcja od³¹czaj¹ca okno komunikatów.
	*
	* Funkcja od³¹cza okno komunikatów od okna g³ównego.
	* Powoduje to, ¿e okno nie dostanie kolejnego komunikatu logu dopuki nie zostanie ponownie pod³¹czone.
	* \author Daniel Wojdak
	* \version 1
	* \date 16-07-2014
	* \deprecated Funkcjonalnoœæ zostanie zautomatyzowana.
	*/
	__declspec(dllexport) void __cdecl odlaczOknoKomunikatow()
	{
		SpEx::UtilsGui::odlaczOknoKomunikatow();
	}

	/**
	* \brief Funkcja pod³¹cza okno komunikatów.
	*
	* Funkcja pod³¹cza okno komunikatów do okna g³ównego.
	* Powoduje to, ¿e okno dostaje kolejnego komunikaty logów dopuki nie zostanie od³aczone.
	* Je¿eli nie uda siê pod³¹czyæ okna logów, wtedy ustawiane jest puste okno.
	* \param[in] idOkna - Identyfikator ekranu, na którym znajduje siê kontrolka.
	* \param[in] widzet - Nazwa identyfikuj¹ca kontrolkê.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \deprecated Funkcjonalnoœæ zostanie zautomatyzowana.
	*/
	__declspec(dllexport) void __cdecl podlaczOknoKomunikatow( int idOkna, const char * widzet )
	{
		SpEx::UtilsGui::ustawOknoKomunikatow(idOkna,widzet);
	}

	/**
	* \brief Funkcja wysy³a komunikat do kontrolki wyœwietlaj¹cej logi.
	*
	* Funkcja wysy³a komunikat, przekazany w parametrze, do kontrolki przystosowanej do wyœwietlania logów. 
	* Kontrolka musi byæ pod³¹czona za pomoc¹ metody podlaczOknoKomunikatow.
	* Je¿eli nie ma ¿adnej pod³¹czonej kontrolki funkcja nie wykonuje ¿adnej akcji.
	* \param[in] typ - Typ wysy³anego komunikatu.
	* \param[in] komunikat - Treœæ wysy³anego komunikatu.
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
	* Funkcja dodaje ekran, o podanym id, na wierzch stosu wyœwietlanych ekranów.
	* \param[in] id - Identyfikator ekranu.
	* \return Je¿eli uda siê dodaæ ekran zwracana jest wartoœæ true. Je¿eli ekran nie zostanie znaleziony zwracana jest wartoœc false.
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
	* \return Je¿eli uda siê zdj¹æ ekran zwracana jest wartoœæ true. Je¿eli stos jest pusty zwracana jest wartoœæ false.
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
	* Funkcja pobiera zdarzenie, dla którego jest wykonywana aktualna akcja.
	* Poprawne zdarzenie zostanie pobrane, je¿eli akcja jaka jest aktualnie wykonywana jest akcj¹ zdarzenia. 
	* Schemat kiedy wywo³ywana jest akcja zdarzenia znajduje siê w doc\Schemat\MaszynaStanow\Projekt\AkcjeWStanie.vsd w repozytorium.
	* \param[out] z - Zmienna do której zostan¹ zapisane dane zdarzenia. Zmienna pozostaje niezmieniona, je¿eli funkcja zwróci wartoœæ false.
	* \return Je¿eli uda siê pobraæ zdarzenie zwracana jest wartoœæ true. Je¿eli zdarzenie jest niepoprawne zwracana jest wartoœæ false.
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
	* Funkcja pobiera poprzedni stan z maszyny stanów. Stan zostanie poprawnie pobrany, je¿eli metoda zostanie wykonana w odpowiedniej akcji.
	* \param[out] s - Zmienna do której zostan¹ zapisane dane stanu. Zmienna pozostaje niezmieniona, je¿eli funkcja zwróci wartoœæ false.
	* \return Je¿eli uda siê pobraæ stan poprzedni zwracana jest wartoœæ true. Je¿eli stan poprzedni jest niepoprawny zwracana jest wartoœæ false.
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
	* Funkcja pobiera aktualny stan z maszyny stanów. Stan zostanie poprawnie pobrany, je¿eli metoda zostanie wykonana w odpowiedniej akcji.
	* \param[out] s - Zmienna do której zostan¹ zapisane dane stanu. Zmienna pozostaje niezmieniona, je¿eli funkcja zwróci wartoœæ false.
	* \return Je¿eli uda siê pobraæ stan aktualny zwracana jest wartoœæ true. Je¿eli stan aktualny jest niepoprawny zwracana jest wartoœæ false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) bool __cdecl pobierzAktualnyStan(struct Stan_t& s)
	{
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzAktualnyStan(s);
	}

	/**
	* \brief Funkcja pobiera nastêpny stan.
	*
	* Funkcja pobiera nastêpny stan z maszyny stanów. Stan zostanie poprawnie pobrany, je¿eli metoda zostanie wykonana w odpowiedniej akcji.
	* \param[out] s - Zmienna do której zostan¹ zapisane dane stanu. Zmienna pozostaje niezmieniona, je¿eli funkcja zwróci wartoœæ false.
	* \return Je¿eli uda siê pobraæ stan nastêpny zwracana jest wartoœæ true. Je¿eli stan nastêpny jest niepoprawny zwracana jest wartoœæ false.
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
	* Funkcja wstawia zdarzenie na koniec kolejki zdarzeñ w maszynie stanów.
	* \param[in] s - Zmienna przechowuj¹ca informacje o zdarzeniu.
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
	* \brief Funkcja dodaje zdarzenie na pocz¹tek kolejki.
	*
	* Funkcja wstawia zdarzenie na pocz¹tek kolejki zdarzeñ w maszynie stanów.
	* \param[in] s - Zmienna przechowuj¹ca informacje o zdarzeniu.
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
	* \brief Funkcja ustawia nowy stan nastêpny.
	*
	* Funkcja ustawia nowy stan nastepny. Metoda dzia³a tylko w akcji zdarzenia.
	* \param[in] id - Identyfikator stanu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl ustawNowyStanNastepny(int id){
		SpEx::MaszynaStanow::pobierzInstancje().luaStan_.ustawNowyStanNastepny(id);
	}

	/**
	* \brief Funkcja ustawia nowy numer dodatkowy dla stanu nastêpnego.
	*
	* Funkcja ustawia numer dodatkowy dla stanu nastêpnego. Metoda dzia³a tylko w akcji zdarzenia.
	* \param[in] numer - Numer dodatkowy.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl ustawNowyNumerNastepny(int numer){
		SpEx::MaszynaStanow::pobierzInstancje().luaStan_.ustawNowyNumerNastepny(numer);
	}

	/**
	* \brief Funkcja czyœci stos ekranów.
	*
	* Funkcja usuwa wszystkie ekrany z aktualnego stosu ekranów.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl wyczyscListeOkien()
	{
		SpEx::MaszynaStanow::pobierzInstancje().wyczyscKolejkeOkien();
	}

	/**
	* \brief Funkcja uruchamiaj¹ca testy jednostkowe.
	*
	* Funkcja wykonuje testy jednostkowe aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \deprecated Funkcjonalnoœæ zostanie usuniêta w wersji Release.
	*/
	__declspec(dllexport) void __cdecl testyJednostkowe()
	{
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
	}

	/**
	* \brief Funkcja dodaj¹ca zadanie do wykonania.
	*
	* Funkcja zleca wykonanie zadania jednemu z w¹tków w puli przeznaczonych do wykonywania zadañ wymagaj¹cych obliczoniowo lub oczekuj¹cych na akcje z zewn¹trz.
	* Funkcja nieblokuj¹ca. Dodaje zadanie do listy i kontynuuje wykonywanie. Zadanie wykonuje siê równolegle.
	* \param[in] plik - Plik ze skryptem lua.
	* \param[in] funkcja - Nazwa funkcji jaka ma zostaæ wywo³ana. Je¿eli ma zostaæ wykonany ca³y plik nale¿y podaæ wartoœæ nullptr.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcjonalnoœæ zostanie poprawiona. Zostanie rozci¹gniêta na wszysktie typy skryptów. Aktualnie u¿ywa jest tylko dla skrytpów lua.
	* \todo Rozsze¿yæ na wiele typów skryptów.
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
	* \brief Funkcja inicjuj¹ca zamykanie aplikacji.
	*
	* Funkcja rozpoczyna sekwencjê kroków prowadz¹c¹ do zamkniêcia aplikacji. Po wykonaniu tej metody nie ma mo¿liwoœci przerwania operacji zamykania.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	__declspec(dllexport) void __cdecl zamknijAplikacje()
	{
		SpEx::MaszynaStanow::pobierzInstancje().inicjujZamykanie();
	}

	/**
	* \brief Funkcja wysy³a komunikat do logu.
	*
	* Funkcja wysy³a komunikat do logów aplikacji.
	* \param[in] komunikat - Treœæ komunikatu.
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
	* \brief Funkcja wczytuj¹ca dane opisowe obiektów gry oraz obiekty lokacji.
	*
	* Funkcja wczytuje lokacje oraz obiekty opisowe gry.
	* \param[in] plik - Nazwa pliku z danymi.
	* \return Zwracana jest wartoœæ true, je¿eli uda siê wczytaæ. Zwracana jest wartoœæ false, je¿eli wyst¹pi³ b³¹d.
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
	* \brief Funkcja wczytuj¹ca ponownie ekran.
	*
	* Funkcja zleca zadanie dla w¹tku graficznego, aby ponownie wczyta³ ekran o podanym id.
	* \param[in] id - Identyfikator ekranu.
	* \warning Funckja dodaje zadanie do w¹tku graficznego!
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
	* Funkcja loguje u¿ytkownika do aplikacji.
	* \param[in] kontrolkaNazwy - Nazwa kontrolki zawieraj¹cej nazwê u¿ytkownika.
	* \param[in] kontrolkaHasla - Nazwa kontrolki zawieraj¹cej has³o u¿ytkownika.
	* \return Zwracana jest wartoœæ true, je¿eli uda siê zalogowaæ. Zwracana jest wartoœæ false, je¿eli wyst¹pi³ b³¹d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcja wysy³a komunikaty loguj¹ce do GUI. 
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
						SpEx::UtilsGui::logToGUI(0, "Nie uda³o siê zalogowaæ!");
					}
				}
				else{
					SpEx::UtilsGui::logToGUI(0, "Brak has³a lub loginu!");
				}
			}
			else{
				SpEx::UtilsGui::logToGUI(0, "Brak widzetu has³a lub loginu!");
			}
		}
		else{
			SpEx::UtilsGui::logToGUI(0, "Brak nazwy widzetu has³a lub loginu!");
		}
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Nie uda³o siê zalogowaæ!");
		return false;
	}

	/**
	* \brief Funkcja tworzenia nowego u¿ytkownika.
	*
	* Funkcja tworzy nowego u¿ytkownika i loguje go do aplikacji.
	* \param[in] kontrolkaNazwy - Nazwa kontrolki zawieraj¹cej nazwê u¿ytkownika.
	* \param[in] kontrolkaHasla - Nazwa kontrolki zawieraj¹cej has³o u¿ytkownika.
	* \return Zwracana jest wartoœæ true, je¿eli uda siê stworzyæ u¿ytkownika i zalogowaæ. Zwracana jest wartoœæ false, je¿eli wyst¹pi³ b³¹d.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcja wysy³a komunikaty loguj¹ce do GUI.
	*/
	__declspec(dllexport) bool __cdecl nowyGracz(const char *kontrolkaNazwy, const char *kontrolkaHasla){
		if (kontrolkaNazwy && kontrolkaHasla ){
			auto nazwa = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaNazwy);
			auto haslo = SpEx::UtilsGui::PobierzWidzetZAktywnegoEkranu<tgui::EditBox>(kontrolkaHasla);
			SpEx::UtilsGui::logToGUI(1, "Inicjowanie tworzenia gracza.");
			if (nazwa != nullptr && haslo != nullptr){
				std::string hash(haslo->getText());
				if (nazwa->getText().isEmpty() || hash.empty()){
					SpEx::UtilsGui::logToGUI(0, "Brak has³a lub nazwy gracza.");
					return false;
				}

				SpEx::Utils::sha3(hash);
				if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzIloscGalaktyk() <= 0){
					SpEx::UtilsGui::logToGUI(1, "Generowanie galaktyki.");
					if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().generujNowaGalaktyke()){
						SpEx::UtilsGui::logToGUI(0, "B³¹d generowania galaktyki.");
						return false;
					}
				}
				SpEx::UtilsGui::logToGUI(1, "Tworzenie nowego gracza.");
				if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().nowyGracz(nazwa->getText(), hash)){
					SpEx::UtilsGui::logToGUI(0, "B³¹d tworzenia gracza.");
					return false;
				}

				SpEx::UtilsGui::logToGUI(1, "Logowanie do gry.");
				if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().logowanie(nazwa->getText(), hash)){
					SpEx::UtilsGui::logToGUI(0, "B³¹d logowania do gry.");
					return false;
				}
				
				SpEx::UtilsGui::logToGUI(1, "Ustawianie podstawowych danych.");
				if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika()){
					SpEx::UtilsGui::logToGUI(1, "Generowanie galaktyki.");
					if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().generujNowaGalaktyke()){
						SpEx::UtilsGui::logToGUI(0, "B³¹d generowania galaktyki.");
						return false;
					}

					SpEx::UtilsGui::logToGUI(1, "Ustawianie podstawowych danych.");
					if (!SpEx::Aplikacja::pobierzInstancje().pobierzGre().przeniesPlaneteDoUzytkownika()){
						SpEx::UtilsGui::logToGUI(0, "B³¹d przypisywania planety do u¿ytkownika.");
						return false;
					}
				}

				SpEx::UtilsGui::logToGUI(1, "Zapisywanie wprowadzonych danych.");
				if (SpEx::Aplikacja::pobierzInstancje().zapiszGre(nazwa->getText(), hash)){

					SpEx::UtilsGui::logToGUI(1, "Ukoñczono.");
					return true;
				}
			}
			else{
				SpEx::UtilsGui::logToGUI(0, "Brak kontrolki has³a lub nazwy gracza.");
			}

		}

		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Nie uda³o siê stworzyæ nowego gracza!");
		SpEx::UtilsGui::logToGUI(0, "Nie uda³o siê stworzyæ nowego gracza!");
		return false;
	}

	/**
	* \brief Funkcja usuwaj¹ca u¿ytkownika.
	*
	* Funkcja usuwa wszelkie informacje o u¿ytkowniku z aplikacji.
	* \param[in] kontrolkaNazwy - Nazwa kontrolki zawieraj¹cej nazwê u¿ytkownika.
	* \param[in] kontrolkaHasla - Nazwa kontrolki zawieraj¹cej has³o u¿ytkownika.
	* \return Zwracana jest wartoœæ true, je¿eli uda siê usun¹æ. Zwracana jest wartoœæ false, je¿eli wyst¹pi³ b³¹d.
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
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Nie uda³o siê usun¹æ gracza!");
		return false;
	}

	/**
	* \brief Funkcja dodaj¹ca zadanie do wykonania w w¹tku graficznym.
	*
	* Funkcja zleca wykonanie zadania w w¹tku graficznym.
	* Funkcja nieblokuj¹ca. Dodaje zadanie do listy i kontynuuje wykonywanie.
	* \warning Funckja dodaje zadanie do w¹tku graficznego!
	* \warning Zadanie wymagaj¹ce obliczeniowo mo¿e powodowaæ zamro¿enie okna aplikacji. Nale¿y u¿ywaæ tej funkcjonalnoœci tylko w sytuacjach koniecznych.
	* \param[in] plik - Plik ze skryptem lua.
	* \param[in] funkcja - Nazwa funkcji jaka ma zostaæ wywo³ana. Je¿eli ma zostaæ wykonany ca³y plik nale¿y podaæ wartoœæ nullptr.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \note Funkcjonalnoœæ zostanie poprawiona. Zostanie rozci¹gniêta na wszysktie typy skryptów. Aktualnie u¿ywa jest tylko dla skrytpów lua.
	* \todo Rozsze¿yæ na wiele typów skryptów.
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
	* \brief Funkcja ustawiaj¹ca w³aœciwoœæ kontrolki.
	*
	* Funkcja ustawia w³aœciwoœæ kontrolki. Lista w³aœciwoœci bêdzie dodana wraz z rozbudow¹ dokumentacji.
	* \param[in] ekran - Identyfikator ekranu, na którym znajduje siê kontrolka.
	* \param[in] kontrolka - Nazwa kontrolki.
	* \param[in] nazwaWlasciwosci - Nazwa w³aœciwoœci.
	* \param[in] nowaWartosc - Nowa wartoœæ w³aœciwoœci.
	* \return Zwracana jest wartoœæ true, je¿eli uda siê ustawiæ w³aœciwoœæ. Zwracana jest wartoœæ false, je¿eli wyst¹pi³ b³¹d.
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
	* \brief Funkcja pobieraj¹ca nazwê aktualnie zalogowanego u¿ytkownika.
	*
	* Funkcja pobiera nazwê uzytkownika, który jest aktualnie zalogowany do aplikacji.
	* \return Zwracana jest nazwa u¿ytkownika, je¿eli jest zalogowany. Zwracany jest nullptr, je¿eli nie ma zalogowanego u¿ytkownika.
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
	* \brief Funkcja buduj¹ca obiekt na planecie.
	*
	* Funkcja buduje obiekt na aktualnie aktywnej planecie.
	* \param[in] id - identyfikator obiektu.
	* \param[in] ilosc - parametr nieu¿ywany.
	* \return Zwracana jest wartoœæ true, je¿eli uda siê wybudowaæ obiekt. Zwracana jest wartoœæ false, je¿eli wyst¹pi³ b³¹d.
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
	* \brief Funkcja aktualizuj¹ca dane listy obiektów.
	*
	* Funkcja aktualizuje dane listy obiektów w przeznaczonej do tego specjalnej kontrolce.
	* \param[in] idEkranu - identyfikator ekranu, który zawiera kontrolkê.
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
	* \brief Funkcja aktualizuj¹ca dane listy surowców.
	*
	* Funkcja aktualizuje dane listy surowców w przeznaczonej do tego specjalnej kontrolce.
	* \param[in] idEkranu - identyfikator ekranu, który zawiera kontrolkê.
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