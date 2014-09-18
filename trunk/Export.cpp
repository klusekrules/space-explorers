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
#include "Export.h"

extern "C"{

	SPACE_EXPLORERS_API void __cdecl logujWOknieKomunikatow(unsigned int typ, const char * komunikat){
		SpEx::UtilsGui::logToGUI(typ,komunikat);
	}

	SPACE_EXPLORERS_API bool __cdecl ustawOkno(int id){
		return SpEx::MaszynaStanow::pobierzInstancje().kolejkujOkno(id);
	}

	SPACE_EXPLORERS_API bool __cdecl zdejmijOkno(){
		return SpEx::MaszynaStanow::pobierzInstancje().zdejmijOkno();
	}

	SPACE_EXPLORERS_API bool __cdecl pobierzZdarzenie(struct Zdarzenie_t& z){
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzZdarzenie(z);
	}

	SPACE_EXPLORERS_API bool __cdecl pobierzPoprzedniStan(struct Stan_t& s){
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzPoprzedniStan(s);
	}

	SPACE_EXPLORERS_API bool __cdecl pobierzAktualnyStan(struct Stan_t& s){
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzAktualnyStan(s);
	}

	SPACE_EXPLORERS_API bool __cdecl pobierzNastepnyStan(struct Stan_t& s){
		return SpEx::MaszynaStanow::pobierzInstancje().luaStan_.pobierzNastepnyStan(s);
	}

	SPACE_EXPLORERS_API void __cdecl kolejkujZdarzenie(struct Zdarzenie_t& s){
		SpEx::Zdarzenie z;
		z.idStanu_(s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_(s.idZdarzenia_);
		SpEx::MaszynaStanow::pobierzInstancje().kolejkujZdarzenie(z);
	}

	SPACE_EXPLORERS_API void __cdecl wstawZdarzenie(struct Zdarzenie_t& s){
		SpEx::Zdarzenie z;
		z.idStanu_(s.idStanu_);
		z.numer_ = s.numer_;
		z.idZdarzenia_(s.idZdarzenia_);
		SpEx::MaszynaStanow::pobierzInstancje().wstawZdarzenie(z);
	}

	SPACE_EXPLORERS_API void __cdecl ustawNowyStanNastepny(int id){
		SpEx::MaszynaStanow::pobierzInstancje().luaStan_.ustawNowyStanNastepny(id);
	}

	SPACE_EXPLORERS_API void __cdecl ustawNowyNumerNastepny(int numer){
		SpEx::MaszynaStanow::pobierzInstancje().luaStan_.ustawNowyNumerNastepny(numer);
	}

	SPACE_EXPLORERS_API void __cdecl wyczyscListeOkien(){
		SpEx::MaszynaStanow::pobierzInstancje().wyczyscKolejkeOkien();
	}

	SPACE_EXPLORERS_API void __cdecl testyJednostkowe(){
		TestyJednostkowe::pobierzInstancje().wykonajTesty();
	}

	SPACE_EXPLORERS_API void __cdecl zlecZadanie(const char *plik, const char *funkcja){
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
				luaSkrypt->wykonaj(sFunkcja);
			}
			return;
		};
		SpEx::Zadanie zadanie(lambda);
		maszynaStanow.dodajZadanie(zadanie);
	}

	SPACE_EXPLORERS_API void __cdecl zamknijAplikacje(){
		SpEx::MaszynaStanow::pobierzInstancje().inicjujZamykanie();
	}

	SPACE_EXPLORERS_API void __cdecl loguj(const char *komunikat){
		if (komunikat)
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, komunikat);
	}

	SPACE_EXPLORERS_API bool __cdecl zaladujGre(const char *plik){
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

	SPACE_EXPLORERS_API void __cdecl przeladujOkno(int id){
		SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().dodajZadanie(SpEx::Zadanie(
			std::function<void()>(
				std::bind(
					&SpEx::OknoGry::przeladujEkran,
					&SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry(),
					STyp::Identyfikator(id))
				))
			);
	}

	SPACE_EXPLORERS_API bool __cdecl zaloguj(const char *kontrolkaNazwy, const char *kontrolkaHasla){
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

	SPACE_EXPLORERS_API bool __cdecl nowyGracz(const char *kontrolkaNazwy, const char *kontrolkaHasla){
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

	SPACE_EXPLORERS_API bool __cdecl usunGracza(const char *kontrolkaNazwy, const char *kontrolkaHasla){
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

	SPACE_EXPLORERS_API void __cdecl zlecZadanieGraficzne(const char *plik, const char *funkcja)
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
				luaSkrypt->wykonaj(sFunkcja);
			}
		};
		SpEx::Zadanie zadanie(lambda);
		maszynaStanow.pobierzOknoGry().dodajZadanie(zadanie);
	}

	SPACE_EXPLORERS_API bool __cdecl ustawWlasciwosc(int ekran, const char *kontrolka, const char *nazwaWlasciwosci, const char *nowaWartosc){
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

	SPACE_EXPLORERS_API const char * __cdecl pobierzNazweAktualnegoGracza(){
		if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().czyZalogowano())
			return SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzNazweUzytkownika()().c_str();
		else
			return nullptr;
	}

	SPACE_EXPLORERS_API bool __cdecl wybudujObiekt(int id, int ilosc){
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

	SPACE_EXPLORERS_API void __cdecl aktualizujDaneListyObiektow(int idEkranu, const char *nazwaKontrolki)
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

	SPACE_EXPLORERS_API void __cdecl aktualizujDaneListySurowcow(int idEkranu, const char *nazwaKontrolki)
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
