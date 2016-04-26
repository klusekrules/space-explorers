#include "SprawdzSumyKontrolneRPC.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"
#include "Narzedzia\ZarzadcaZasobow.h"
#include "Narzedzia\SumaKontrolnaPliku.h"
#include "Kontroler\Zarzadca\ZarzadcaPluginow.h"
#include "StaleRPC.h"
#include "Narzedzia\Stale.h"
#include "Algorytmy\base64.h"

#define LISTA_PLIKOW "lista"
#define NAZWA_PLIKU "nazwa"
#define SUMA_PLIKU "suma"

namespace SpEx{

	static inline std::string& pobierzAdresPliku(const std::string nazwa){
		return Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()[nazwa];
	}

	static inline SumaKontrolnaPliku::SharedPtr pobierzSumeKontrolna(const std::string& adres){
		return Aplikacja::pobierzInstancje().pobierzZarzadceZasobow().pobierzZasob<SumaKontrolnaPliku>(adres);
	}
	
	const std::string SprawdzSumyKontrolneRPC::NazwaTypu_ = "SprawdzSumyKontrolne";

	void SprawdzSumyKontrolneRPC::ustawListePlikow(const std::vector<std::string>& lista){
		lista_ = &lista;
	}

	std::string SprawdzSumyKontrolneRPC::napis() const{
		SLog::Logger logger(NAZWAKLASY(SprawdzSumyKontrolneRPC));
		logger.dodajKlase(MetodaRPC::napis());
		return logger.napis();
	}

	bool SprawdzSumyKontrolneRPC::przygotowanieDoWyslania(){
		if (lista_){
			parametry_[LISTA_PLIKOW] = Json::Value(Json::arrayValue);
			int a = 0;
			for (auto& e : *lista_){
				Json::Value plik(Json::objectValue);
				plik[NAZWA_PLIKU] = e;
				auto suma = pobierzSumeKontrolna(e);
				if (suma == nullptr || suma->pobierzSumeKontrolna().pobierzKontener().empty()){
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak sumy kontrolnej pliku: " + e);
					}
					return false;
				}
				plik[SUMA_PLIKU] = std::move(suma->pobierzSumeKontrolna().pobierzNapis<Base64>());
				parametry_[LISTA_PLIKOW][a++] = plik;
			}
		}
		return true;
	}

	void SprawdzSumyKontrolneRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		if (parametry_[LISTA_PLIKOW].isArray() && parametry_[LISTA_PLIKOW].size() > 0){
			std::vector<std::string> temp;
			for (auto& zasob : Aplikacja::pobierzInstancje().pobierzZarzadcePluginow().pobierzListeSumKontrolnych()){
				temp.emplace_back(zasob->pobierzAdresPliku());
			}
			temp.emplace_back(Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()[ATRYBUT_PLIK_DANYCH]);
			odpowiedz[LISTA_PLIKOW] = Json::Value(Json::arrayValue);
			int a = 0;
			for (auto & element : parametry_[LISTA_PLIKOW]){
				if (element.isObject() && element[NAZWA_PLIKU].isString() && element[SUMA_PLIKU].isString()){
					Json::Value plik(Json::objectValue);
					plik[NAZWA_PLIKU] = element[NAZWA_PLIKU];
					auto iter = std::find(temp.begin(), temp.end(), element[NAZWA_PLIKU].asString());
					if (iter != temp.end()){
						if (pobierzSumeKontrolna(*iter)->pobierzSumeKontrolna().pobierzNapis<Base64>() == element[SUMA_PLIKU].asString()){
							if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Suma kontrolna poprawna dla pliku: " + *iter);
							}
							plik[SUMA_PLIKU] = true;
						}
					} else{
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Nie odnaleziono pliku: " + *iter);
						}
						plik[SUMA_PLIKU] = false;
					}
					odpowiedz[LISTA_PLIKOW][a++] = plik;
				} else{
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Niepoprawny parametr!");
					}
				}
			}
		}
	}

	bool SprawdzSumyKontrolneRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		bool ok = true;
		if (lista_ != nullptr && odpowiedz[LISTA_PLIKOW].isArray() && odpowiedz[LISTA_PLIKOW].size() > 0){
			std::vector<std::string> temp;
			for (auto& element : odpowiedz[LISTA_PLIKOW]){
				if (element.isObject() && element[NAZWA_PLIKU].isString() && element[SUMA_PLIKU].isBool()){
					temp.emplace_back(element[NAZWA_PLIKU].asString());
					auto iter = std::find(lista_->begin(), lista_->end(), element[NAZWA_PLIKU].asString());
					if (iter != lista_->end()){
						if (element[SUMA_PLIKU].asBool()){
							if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, *iter + " - plik poprawny");
							}
						} else{
							if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, *iter + " - plik nie poprawny");
							}
							ok = false;
						}
					} else{
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, element[NAZWA_PLIKU].asString() + " - plik nadmiarowy");
						}
						ok = false;
					}
				}
			}

			if (temp != *lista_){
				for (const auto& s : *lista_){
					auto iter = std::find(temp.begin(), temp.end(), s);
					if (iter == temp.end()){
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, s + " - brak odwo³ania do pliku");
						}
					}
				}
			}

		}
		return ok;
	}
}
