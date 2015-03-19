#include "DaneTCP.h"
#include "zlib.h"
#include "StaleRPC.h"
#include "Aplikacja.h"
#include "VMPC_MAC.h"
#include "SHA3.h"
#include "Fabrykator.h"

namespace SpEx{
	DaneTCP::DaneTCP(Klient& ref)
		: ref_(ref), flagi_(0), odbierz_(wyslij_)
	{
	}

	DaneTCP::DaneTCP(Klient& ref, const std::string& wyslij, std::string& odbierz, int flagi)
		: ref_(ref), odbierz_(odbierz), wyslij_(wyslij), flagi_(flagi), error_(0)
	{	
	}

	int DaneTCP::odbierz(){
		int error = odbierzWewnetrzna();
		if (error==RPC_OK){
			error = przetworzPoOdebraniu();			
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

	int DaneTCP::wyslij(){
		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
			Json::Value root;
			Json::Reader reader;
			Json::StyledWriter writer;
			if (reader.parse(wyslij_, root)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Wys³ano :\n" + writer.write(root));
			}
		}

		auto error = przygotujDoWyslania();
		if (error!=RPC_OK){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d przetwarzania wysy³anych danych: " + std::to_string(error));
			}
			return error;
		}
		return wyslijWewnetrzna();
	}

	int DaneTCP::wykonajMetode(){
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
							flagi_ = metodaRPC->pobierzFlagi();
						} else{
							error = RPC_ERROR_PROCOSSING_METHOD;
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

	void DaneTCP::dodajKomunikatBledu(int blad, Json::Value& root){
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
		case RPC_ERROR_PROCOSSING_METHOD:
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

	int DaneTCP::odbierzWewnetrzna(){
		u_int64 rozmiar = 0;
		u_int64 header = 0;
		int rezultat = 0;
		std::vector <char> bufor;
		size_t tempRozmiar = 0;
		size_t lrozmiar = 0;
		do{
			rezultat = ref_.odbierz((char*)&header, sizeof(u_int64));
			if (rezultat <= 0){
				if (rezultat == 0){
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					}
					return RPC_ERROR_CONNECTION_CLOSED;
				} else{
					if (WSAEWOULDBLOCK == WSAGetLastError()){
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						continue;
					} else{
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(WSAGetLastError()));
						}
						return WSAGetLastError();
					}
				}
			}

			header = ntohll(header);

			rozmiar = (0xFFFFFFFF00000000 & header) >> 32;
			flagi_ = header & 0x00000000FFFFFFFF;

			lrozmiar = static_cast<size_t>(rozmiar);
			bufor.reserve(lrozmiar);
			bufor.resize(lrozmiar, 0);
			do{
				rezultat = ref_.odbierz(&bufor.data()[tempRozmiar], lrozmiar - tempRozmiar);
				if (rezultat <= 0){
					if (rezultat == 0){
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
						}
						return RPC_ERROR_CONNECTION_CLOSED;
					} else{
						if (WSAEWOULDBLOCK == WSAGetLastError()){
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							continue;
						} else{
							if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(WSAGetLastError()));
							}
							return WSAGetLastError();
						}
					}
				}
				tempRozmiar += rezultat;
			} while (tempRozmiar != lrozmiar && !ref_.czyCzekaNaZakonczenie());

		} while ((rozmiar == 0 || tempRozmiar != rozmiar) && !ref_.czyCzekaNaZakonczenie());

		std::string s(bufor.begin(), bufor.end());
		odbierz_ = std::move(s);
		if (rozmiar > 0)
			return RPC_OK;
		else
			return RPC_ERROR_NO_DATA;
	}

	int DaneTCP::wyslijWewnetrzna(){
		int rezultat = 0;
		u_int64 header = 0;
		u_int64 rozmiar = wyslij_.size();
		
		header = (rozmiar << 32) & 0xFFFFFFFF00000000 | flagi_ & 0x00000000FFFFFFFF;
		header = htonll(header);
		rezultat = ref_.wyslij((char*)&header, sizeof(u_int64));
		if (rezultat <= 0){
			int error = 0;
			if (rezultat == 0){
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					error = RPC_ERROR_CONNECTION_CLOSED;
				}
			} else{
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
					error = WSAGetLastError();
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(error));					
				}
			}
			return error;
		}
		size_t lrozmiar = static_cast<size_t>(rozmiar);
		size_t tempRozmiar = lrozmiar;
		do{
			rezultat = ref_.wyslij(&(wyslij_.data()[lrozmiar - tempRozmiar]), lrozmiar);
			if (rezultat <= 0){
				int error = 0;
				if (rezultat == 0){
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
						error = RPC_ERROR_CONNECTION_CLOSED;
					}
				} else{
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
						error = WSAGetLastError();
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(error));
					}
				}
				return error;
			}
			tempRozmiar -= rezultat;
		} while (tempRozmiar != 0);

		return RPC_OK;
	}

	void DaneTCP::wlaczKompresje(){
		flagi_ |= 0x1;
	}

	void DaneTCP::wlaczAutoryzacje(){
		flagi_ |= 0x2;
	}

	int DaneTCP::kompresja(){
		auto rozmiar = wyslij_.size();
		auto bound = compressBound(rozmiar);
		uLongf after = bound;
		std::string out;
		out.resize(after, 0);
		int ret = compress((Bytef*)out.data(), &after, (const Bytef*)wyslij_.data(), rozmiar);
		
		switch (ret)
		{
		case Z_OK:
			{
				error_ = RPC_OK;
				std::string temp;
				temp.push_back((rozmiar >> 24) & 0xff);
				temp.push_back((rozmiar >> 16) & 0xff);
				temp.push_back((rozmiar >> 8) & 0xff);
				temp.push_back(rozmiar & 0xff);
				out.resize(after);
				wyslij_ = temp + out;
			}
			break;
		case Z_MEM_ERROR:
			error_ = RPC_ERROR_COMPRESION_Z_MEM_ERROR;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Z_MEM_ERROR");
			}
			break;
		case Z_BUF_ERROR:
			error_ = RPC_ERROR_COMPRESION_Z_BUF_ERROR;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Z_BUF_ERROR");
			}
			break;
		default:
			error_ = RPC_ERROR_UNIDENTIFYING;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Niezidentyfikowany.");
			}
			break;
		}
		return error_;
	}

	int DaneTCP::dekompresja(){

		uLongf unSize = odbierz_.size() - 4;
		uLongf rozmiar = ((u_char)odbierz_[0] << 24) | ((u_char)odbierz_[1] << 16) | ((u_char)odbierz_[2] << 8) | (u_char)odbierz_[3];
		std::string out;
		out.resize(rozmiar, 0);
		int ret = uncompress((Bytef*)out.data(), &rozmiar, (Bytef*)&odbierz_.data()[4], unSize);

		switch (ret)
		{
		case Z_OK:
			{
				error_ = RPC_OK;
				odbierz_ = out;
			}
			break;
		case Z_MEM_ERROR:
			error_ = RPC_ERROR_COMPRESION_Z_MEM_ERROR;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Z_MEM_ERROR");
			}
			break; 
		case Z_BUF_ERROR:
			error_ = RPC_ERROR_COMPRESION_Z_BUF_ERROR;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Z_BUF_ERROR");
			}
			break;
		case Z_DATA_ERROR:
			error_ = RPC_ERROR_COMPRESION_Z_DATA_ERROR;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Z_DATA_ERROR");
			}
			break;
		default:
			error_ = RPC_ERROR_UNIDENTIFYING;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Niezidentyfikowany");
			}
			break;
		}
		return error_;
	}

	int DaneTCP::szyfrowanie(const std::string& klucz){

		std::string vektor(SLog::Log::pobierzInstancje().pobierzDateCzas());
		VMPC_MAC szyfr;
		SHA3 skrotKlucza(klucz);
		SHA3 skrotVektora(vektor);
		auto &vektorV = skrotVektora.pobierzKontener();

		szyfr.InitKey(skrotKlucza.pobierzKontener(), vektorV);
		szyfr.EncryptMAC(wyslij_);

		auto &macV = szyfr.OutputMAC();

		std::string macS(macV.begin(), macV.end());
		std::string vectorS(vektorV.begin(), vektorV.end());
		wyslij_ = macS + vectorS + wyslij_;
		if (wyslij_.empty())
			return RPC_ERROR_NO_DATA;
		return RPC_OK;
	}

	int DaneTCP::deszyfrowanie(const std::string& klucz){
		VMPC_MAC szyfr;
		SHA3 skrotKlucza(klucz);
		auto firstWektor = odbierz_.begin() + 20;
		auto firstMessage = firstWektor + skrotKlucza.pobierzKontener().size();
		VMPC_MAC::Bufor macVO(odbierz_.begin(), firstWektor);
		VMPC_MAC::Bufor vektorVO(firstWektor, firstMessage);

		odbierz_.erase(odbierz_.begin(), firstMessage);

		szyfr.InitKey(skrotKlucza.pobierzKontener(), vektorVO);
		szyfr.DecryptMAC(odbierz_);
		
		if (odbierz_.empty())
			return RPC_ERROR_NO_DATA;
		if (szyfr.OutputMAC() != macVO)
			return RPC_ERROR_DECRYPTION_FAIL;
		return RPC_OK;
	}

	int DaneTCP::przygotujDoWyslania(){
		error_ = RPC_OK;
		if (flagi_ & 0x1){
			error_ = kompresja();
			if (error_!=RPC_OK)
				return error_;
		}
		if (flagi_ & 0x2){
			if (ref_.czyAutoryzowany()){
				error_ = szyfrowanie(ref_.pobierzKlucz());
				if (error_ != RPC_OK)
					return error_;
			} else{
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Próba szyfrowania bez podania klucza. Wy³aczenie szyfrowania.");
				}
				flagi_ &= ~0x2;
			}
		}
		return error_;
	}

	int DaneTCP::przetworzPoOdebraniu(){
		error_ = RPC_OK;
		if (flagi_ & 0x2){
			if (ref_.czyAutoryzowany()){
				error_ = deszyfrowanie(ref_.pobierzKlucz());
				if (error_!= RPC_OK)
					return error_;
			} else{
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Próba deszyfrowania bez podania klucza.");
				}
				flagi_ &= ~0x2;
			}
		}
		if (flagi_ & 0x1){
			error_ = dekompresja();
			if (error_ != RPC_OK)
				return error_;
		}
		return error_;
	}
}