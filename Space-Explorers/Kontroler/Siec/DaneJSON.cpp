#include "DaneJSON.h"
#include "zlib.h"
#include "RPC\StaleRPC.h"
#include "Kontroler\Aplikacja.h"
#include "Algorytmy\VMPC_MAC.h"
#include "Algorytmy\SHA3.h"
#include "Kontroler\Zarzadca\Fabrykator.h"
#include "DaneZPamieci.h"
#include "DaneTCP.h"

namespace SpEx{
	DaneJSON::DaneJSON(Klient& ref)
		: ref_(ref), flagi_((unsigned __int64)FLAGA_WERSJA << 32), odbierz_(wyslij_)
	{
	}

	DaneJSON::DaneJSON(Klient& ref, const std::string& wyslij, std::string& odbierz, int flagi)
		: ref_(ref), odbierz_(odbierz), wyslij_(wyslij), flagi_( (unsigned __int64)FLAGA_WERSJA << 32 | flagi), error_(0)
	{	
	}

	int DaneJSON::odbierz(){
		int error = odbierzWewnetrzna();
		if (error==RPC_OK){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
				Json::Value root;
				Json::Reader reader;
				Json::StyledWriter writer;
				if (reader.parse(odbierz_, root)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Odebrano :\n" + writer.write(root));
				}
			}
			if (error != RPC_OK && SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d przetwarzania odebranych danych : " + std::to_string(error));
			}
		}
		return error;
	}

	int DaneJSON::wyslij(){
		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
			Json::Value root;
			Json::Reader reader;
			Json::StyledWriter writer;
			if (reader.parse(wyslij_, root)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Wys³ano :\n" + writer.write(root));
			}
		}
		return wyslijWewnetrzna();
	}

	int DaneJSON::wykonajMetode(){
		Json::Value root;
		Json::Reader reader; 
		int error = RPC_OK;
		if (!reader.parse(odbierz_, root)){
			error = RPC_ERROR_PARSING_FAIL;
			root = Json::Value(Json::objectValue);
		}else{
			//Sprawdzanie metody
			error = MetodaRPC::waliduj(root, false);
			if (error == RPC_OK){
				auto metodaRPC = Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC(root, ref_);
				if (metodaRPC){
					try{
						if (metodaRPC->obsluzMetode(root)){
							//Pobieranie flag steruj¹cych dla pakietu zwrotnego.
							flagi_ = (unsigned __int64)FLAGA_WERSJA << 32 | metodaRPC->pobierzFlagi();
						} else{
							error = SOCK_PROCCESSING_BREAK;
						}
					}
					catch (STyp::Wyjatek& wyjatek){
						error = RPC_ERROR_EXCEPTION;
						root[METODA_RPC_ERROR][METODA_RPC_EXCEPTION_TYPE] = "STyp::Wyjatek";
						root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = wyjatek.generujKomunikat()();
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, wyjatek);
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Odebrane ¿¹danie:");
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, odbierz_);
						}						
					}
					catch (std::exception& exception){
						error = RPC_ERROR_EXCEPTION;
						root[METODA_RPC_ERROR][METODA_RPC_EXCEPTION_TYPE] = "std::exception";
						root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = exception.what();
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, exception.what());
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Odebrane ¿¹danie:");
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, odbierz_);
						}
					}
					catch (...){
						error = RPC_ERROR_EXCEPTION;
						root[METODA_RPC_ERROR][METODA_RPC_EXCEPTION_TYPE] = "unknown";
						root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = "Nieznany wyj¹tek."; 
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie obs³ugiwany wyj¹tek!");
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Odebrane ¿¹danie:");
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, odbierz_);
						}
					}
				} else{
					error = RPC_ERROR_MISSING_METHOD;
				}
			}
		}

		//Obs³uga b³êdu lub wykonanie metody.
		if (error!=RPC_OK){
			dodajKomunikatBledu(error, root);
		} 

		Json::FastWriter writer;
		MetodaRPC::dodajCRC(root);
		wyslij_ = writer.write(root);
		return error;
		
	}

	void DaneJSON::dodajKomunikatBledu(int blad, Json::Value& root){
		switch (blad){
		case RPC_ERROR_EXCEPTION:
			root[METODA_RPC_ERROR][METODA_RPC_TYPE] = TYPE_RPC_E_EXCEPTION;
			root[METODA_RPC_ERROR][METODA_RPC_NUMER] = blad;
			break;
		case RPC_OK:
			break;
		case RPC_ERROR_NEED_AUTHORIZATION:
			root[METODA_RPC_ERROR][METODA_RPC_TYPE] = TYPE_RPC_E_ERROR;
			root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = "Metoda wymaga autoryzacji.";
			root[METODA_RPC_ERROR][METODA_RPC_NUMER] = blad;
			break;
		case RPC_ERROR_PARSING_FAIL:
			root[METODA_RPC_ERROR][METODA_RPC_TYPE] = TYPE_RPC_E_ERROR;
			root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = "B³¹d parsowania.";
			root[METODA_RPC_ERROR][METODA_RPC_NUMER] = blad;
			break;
		case SOCK_PROCCESSING_BREAK:
			root[METODA_RPC_ERROR][METODA_RPC_TYPE] = TYPE_RPC_E_ERROR;
			root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = "Przetwarznie metody zwróci³o b³¹d.";
			root[METODA_RPC_ERROR][METODA_RPC_NUMER] = blad;
			break;
		case RPC_ERROR_MISSING_METHOD:
			root[METODA_RPC_ERROR][METODA_RPC_TYPE] = TYPE_RPC_E_ERROR;
			root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = "Nie uda³o siê stworzyæ metody na podstawie otrzymanych danych.";
			root[METODA_RPC_ERROR][METODA_RPC_NUMER] = blad;
			break;
		default:
			root[METODA_RPC_ERROR][METODA_RPC_TYPE] = TYPE_RPC_E_ERROR;
			root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = "Wystapil nieznany blad.";
			root[METODA_RPC_ERROR][METODA_RPC_NUMER] = blad;
			break;
		}
	}

	int DaneJSON::odbierzWewnetrzna(){

		DaneZPamieci dane(ref_);
		auto gniazdo = std::move(ref_.pobierzGniazdo());
		DaneTCP::Warunek warunek([&]()->bool { return !ref_.czyCzekaNaZakonczenie(); });
		DaneTCP tcp(gniazdo, dane, warunek);
		
		int ret = tcp.odbierz();

		if (ret == ERROR_SUCCESS)
			odbierz_ = std::move(dane.pobierzBufor());
		return ret;
	}

	int DaneJSON::wyslijWewnetrzna(){

		DaneZPamieci dane(ref_, std::move(wyslij_));

		dane.ustawFlagi(flagi_);

		auto gniazdo = std::move(ref_.pobierzGniazdo());
		DaneTCP::Warunek warunek([&]()->bool { return !ref_.czyCzekaNaZakonczenie(); });
		DaneTCP tcp(gniazdo, dane, warunek);

		return tcp.wyslij();
	}
	
}