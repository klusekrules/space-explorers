#pragma once
#include "TypyEksportowane.h"

/** @defgroup group1 Funkcje eksportowane
* \brief Funkcje eksportowane
* \details Lista wszystkich funkcji oraz struktur jakie s� udost�pnione w celu zaprogramowania zachowa� gry.
* Mo�na u�ywa� tych obiekt�w w skryptach lua jak i w plikach dll pod��czonych jako skrypty.
*  @{
*/

extern "C"{

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
	SPACE_EXPLORERS_API void __cdecl wyswietlWiadomoscWGUI(unsigned int typ, const char * komunikat);

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
	SPACE_EXPLORERS_API bool __cdecl wstawEkranNaStos(int id);

	/**
	* \brief Funkcja zdejmuje ekran z wierzchu stosu.
	*
	* Funkcja zdejmuje ekran z wierzchnu stosu.
	* \return Je�eli uda si� zdj�� ekran zwracana jest warto�� true. Je�eli stos jest pusty zwracana jest warto�� false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API bool __cdecl zdejmijEkranZeStosu();

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
	SPACE_EXPLORERS_API bool __cdecl pobierzZdarzenie(struct Zdarzenie_t& z);

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
	SPACE_EXPLORERS_API bool __cdecl pobierzPoprzedniStan(struct Stan_t& s);

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
	SPACE_EXPLORERS_API bool __cdecl pobierzAktualnyStan(struct Stan_t& s);

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
	SPACE_EXPLORERS_API bool __cdecl pobierzNastepnyStan(struct Stan_t& s);

	/**
	* \brief Funkcja dodaje zdarzenie na koniec kolejki.
	*
	* Funkcja wstawia zdarzenie na koniec kolejki zdarze� w maszynie stan�w.
	* \param[in] s - Zmienna przechowuj�ca informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl kolejkujZdarzenie(struct Zdarzenie_t& s);

	/**
	* \brief Funkcja dodaje zdarzenie na pocz�tek kolejki.
	*
	* Funkcja wstawia zdarzenie na pocz�tek kolejki zdarze� w maszynie stan�w.
	* \param[in] s - Zmienna przechowuj�ca informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl wstawZdarzenie(struct Zdarzenie_t& s);

	/**
	* \brief Funkcja ustawia nowy stan nast�pny.
	*
	* Funkcja ustawia nowy stan nastepny. Metoda dzia�a tylko w akcji zdarzenia.
	* \param[in] id - Identyfikator stanu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl ustawNowyStanNastepny(int id);

	/**
	* \brief Funkcja ustawia nowy numer dodatkowy dla stanu nast�pnego.
	*
	* Funkcja ustawia numer dodatkowy dla stanu nast�pnego. Metoda dzia�a tylko w akcji zdarzenia.
	* \param[in] numer - Numer dodatkowy.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl ustawNowyNumerNastepny(int numer);

	/**
	* \brief Funkcja czy�ci stos ekran�w.
	*
	* Funkcja usuwa wszystkie ekrany z aktualnego stosu ekran�w.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl wyczyscListeEkranow();

	/**
	* \brief Funkcja uruchamiaj�ca testy jednostkowe.
	*
	* Funkcja wykonuje testy jednostkowe aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \deprecated Funkcjonalno�� zostanie usuni�ta w wersji Release.
	*/
	SPACE_EXPLORERS_API void __cdecl testyJednostkowe();

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
	*/
	SPACE_EXPLORERS_API void __cdecl zlecZadanie(const char *plik, const char *funkcja);

	/**
	* \brief Funkcja inicjuj�ca zamykanie aplikacji.
	*
	* Funkcja rozpoczyna sekwencj� krok�w prowadz�c� do zamkni�cia aplikacji. Po wykonaniu tej metody nie ma mo�liwo�ci przerwania operacji zamykania.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl zamknijAplikacje();

	/**
	* \brief Funkcja wysy�a komunikat do logu.
	*
	* Funkcja wysy�a komunikat do log�w aplikacji.
	* \param[in] komunikat - Tre�� komunikatu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl loguj(const char *komunikat);

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
	SPACE_EXPLORERS_API bool __cdecl zaladujGre(const char *plik);

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
	SPACE_EXPLORERS_API void __cdecl przeladujEkran(int id);

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
	SPACE_EXPLORERS_API bool __cdecl zaloguj(const char *kontrolkaNazwy, const char *kontrolkaHasla);

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
	SPACE_EXPLORERS_API bool __cdecl nowyGracz(const char *kontrolkaNazwy, const char *kontrolkaHasla);

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
	SPACE_EXPLORERS_API bool __cdecl usunGracza(const char *kontrolkaNazwy, const char *kontrolkaHasla);

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
	*/
	SPACE_EXPLORERS_API void __cdecl zlecZadanieGraficzne(const char *plik, const char *funkcja);

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
	SPACE_EXPLORERS_API bool __cdecl ustawWlasciwosc(int ekran, const char *kontrolka, const char *nazwaWlasciwosci, const char *nowaWartosc);

	/**
	* \brief Funkcja pobieraj�ca nazw� aktualnie zalogowanego u�ytkownika.
	*
	* Funkcja pobiera nazw� uzytkownika, kt�ry jest aktualnie zalogowany do aplikacji.
	* \return Zwracana jest nazwa u�ytkownika, je�eli jest zalogowany. Zwracany jest nullptr, je�eli nie ma zalogowanego u�ytkownika.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API const char * __cdecl pobierzNazweAktualnegoGracza();

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
	SPACE_EXPLORERS_API bool __cdecl wybudujObiekt(int id, int ilosc);

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
	SPACE_EXPLORERS_API void __cdecl aktualizujDaneListyObiektow(int idEkranu, const char *nazwaKontrolki);

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
	SPACE_EXPLORERS_API void __cdecl aktualizujDaneListySurowcow(int idEkranu, const char *nazwaKontrolki);


	SPACE_EXPLORERS_API void __cdecl logujPoleceniaKonsoli();

	SPACE_EXPLORERS_API TrybAplikacji __cdecl trybAplikacji();
}

/** @} */