#pragma once
#include "TypyEksportowane.h"

/** @defgroup group1 Funkcje eksportowane
* \brief Funkcje eksportowane
* \details Lista wszystkich funkcji oraz struktur jakie s¹ udostêpnione w celu zaprogramowania zachowañ gry.
* Mo¿na u¿ywaæ tych obiektów w skryptach lua jak i w plikach dll pod³¹czonych jako skrypty.
*  @{
*/

extern "C"{

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
	SPACE_EXPLORERS_API void __cdecl wyswietlWiadomoscWGUI(unsigned int typ, const char * komunikat);

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
	SPACE_EXPLORERS_API bool __cdecl wstawEkranNaStos(int id);

	/**
	* \brief Funkcja zdejmuje ekran z wierzchu stosu.
	*
	* Funkcja zdejmuje ekran z wierzchnu stosu.
	* \return Je¿eli uda siê zdj¹æ ekran zwracana jest wartoœæ true. Je¿eli stos jest pusty zwracana jest wartoœæ false.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API bool __cdecl zdejmijEkranZeStosu();

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
	SPACE_EXPLORERS_API bool __cdecl pobierzZdarzenie(struct Zdarzenie_t& z);

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
	SPACE_EXPLORERS_API bool __cdecl pobierzPoprzedniStan(struct Stan_t& s);

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
	SPACE_EXPLORERS_API bool __cdecl pobierzAktualnyStan(struct Stan_t& s);

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
	SPACE_EXPLORERS_API bool __cdecl pobierzNastepnyStan(struct Stan_t& s);

	/**
	* \brief Funkcja dodaje zdarzenie na koniec kolejki.
	*
	* Funkcja wstawia zdarzenie na koniec kolejki zdarzeñ w maszynie stanów.
	* \param[in] s - Zmienna przechowuj¹ca informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl kolejkujZdarzenie(struct Zdarzenie_t& s);

	/**
	* \brief Funkcja dodaje zdarzenie na pocz¹tek kolejki.
	*
	* Funkcja wstawia zdarzenie na pocz¹tek kolejki zdarzeñ w maszynie stanów.
	* \param[in] s - Zmienna przechowuj¹ca informacje o zdarzeniu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl wstawZdarzenie(struct Zdarzenie_t& s);

	/**
	* \brief Funkcja ustawia nowy stan nastêpny.
	*
	* Funkcja ustawia nowy stan nastepny. Metoda dzia³a tylko w akcji zdarzenia.
	* \param[in] id - Identyfikator stanu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl ustawNowyStanNastepny(int id);

	/**
	* \brief Funkcja ustawia nowy numer dodatkowy dla stanu nastêpnego.
	*
	* Funkcja ustawia numer dodatkowy dla stanu nastêpnego. Metoda dzia³a tylko w akcji zdarzenia.
	* \param[in] numer - Numer dodatkowy.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl ustawNowyNumerNastepny(int numer);

	/**
	* \brief Funkcja czyœci stos ekranów.
	*
	* Funkcja usuwa wszystkie ekrany z aktualnego stosu ekranów.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl wyczyscListeEkranow();

	/**
	* \brief Funkcja uruchamiaj¹ca testy jednostkowe.
	*
	* Funkcja wykonuje testy jednostkowe aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	* \deprecated Funkcjonalnoœæ zostanie usuniêta w wersji Release.
	*/
	SPACE_EXPLORERS_API void __cdecl testyJednostkowe();

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
	*/
	SPACE_EXPLORERS_API void __cdecl zlecZadanie(const char *plik, const char *funkcja);

	/**
	* \brief Funkcja inicjuj¹ca zamykanie aplikacji.
	*
	* Funkcja rozpoczyna sekwencjê kroków prowadz¹c¹ do zamkniêcia aplikacji. Po wykonaniu tej metody nie ma mo¿liwoœci przerwania operacji zamykania.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl zamknijAplikacje();

	/**
	* \brief Funkcja wysy³a komunikat do logu.
	*
	* Funkcja wysy³a komunikat do logów aplikacji.
	* \param[in] komunikat - Treœæ komunikatu.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API void __cdecl loguj(const char *komunikat);

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
	SPACE_EXPLORERS_API bool __cdecl zaladujGre(const char *plik);

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
	SPACE_EXPLORERS_API void __cdecl przeladujEkran(int id);

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
	SPACE_EXPLORERS_API bool __cdecl zaloguj(const char *kontrolkaNazwy, const char *kontrolkaHasla);

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
	SPACE_EXPLORERS_API bool __cdecl nowyGracz(const char *kontrolkaNazwy, const char *kontrolkaHasla);

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
	SPACE_EXPLORERS_API bool __cdecl usunGracza(const char *kontrolkaNazwy, const char *kontrolkaHasla);

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
	*/
	SPACE_EXPLORERS_API void __cdecl zlecZadanieGraficzne(const char *plik, const char *funkcja);

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
	SPACE_EXPLORERS_API bool __cdecl ustawWlasciwosc(int ekran, const char *kontrolka, const char *nazwaWlasciwosci, const char *nowaWartosc);

	/**
	* \brief Funkcja pobieraj¹ca nazwê aktualnie zalogowanego u¿ytkownika.
	*
	* Funkcja pobiera nazwê uzytkownika, który jest aktualnie zalogowany do aplikacji.
	* \return Zwracana jest nazwa u¿ytkownika, je¿eli jest zalogowany. Zwracany jest nullptr, je¿eli nie ma zalogowanego u¿ytkownika.
	* \author Daniel Wojdak
	* \version 1
	* \date 17-07-2014
	*/
	SPACE_EXPLORERS_API const char * __cdecl pobierzNazweAktualnegoGracza();

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
	SPACE_EXPLORERS_API bool __cdecl wybudujObiekt(int id, int ilosc);

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
	SPACE_EXPLORERS_API void __cdecl aktualizujDaneListyObiektow(int idEkranu, const char *nazwaKontrolki);

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
	SPACE_EXPLORERS_API void __cdecl aktualizujDaneListySurowcow(int idEkranu, const char *nazwaKontrolki);


	SPACE_EXPLORERS_API void __cdecl logujPoleceniaKonsoli();

	SPACE_EXPLORERS_API TrybAplikacji __cdecl trybAplikacji();
}

/** @} */