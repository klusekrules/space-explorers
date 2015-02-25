#include "DaneTCP.h"
#include "zlib.h"
#include "StaleRPC.h"
#include "Aplikacja.h"
#include "VMPC_MAC.h"
#include "SHA3.h"

namespace SpEx{
	DaneTCP::DaneTCP(Klient& ref)
		: ref_(ref), flagi_(0), odbierz_(wyslij_)
	{
	}

	DaneTCP::DaneTCP(Klient& ref, const std::string& wyslij, std::string& odbierz, int flagi)
		: ref_(ref), odbierz_(odbierz), wyslij_(wyslij), flagi_(flagi), error_(0)
	{	
	}

	bool DaneTCP::odbierz(){
		if (odbierzWewnetrzna()){
			auto error = przetworzPoOdebraniu();
			if (!error){
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
					Json::Value root;
					Json::Reader reader;
					Json::StyledWriter writer;
					if (reader.parse(odbierz_, root)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Odebrano :\n" + writer.write(root));
					}
				}
				return true;
			}
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d przetwarzania odebranych danych : " + std::to_string(error));
			}
		}
		return false;
	}

	bool DaneTCP::wyslij(){

		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
			Json::Value root;
			Json::Reader reader;
			Json::StyledWriter writer;
			if (reader.parse(wyslij_, root)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Wys³ano :\n" + writer.write(root));
			}
		}

		auto error = przygotujDoWyslania();
		if (error){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d przetwarzania wysy³anych danych: " + std::to_string(error));
			}
			return false;
		}
		return wyslijWewnetrzna();
	}

	bool DaneTCP::wykonajMetode(){
		Json::Value root;
		Json::Reader reader; 
		if (reader.parse(odbierz_, root)){

			//Sprawdzanie metody
			auto error = MetodaRPC::waliduj(root,false);

			//Obs³uga b³êdu lub wykonanie metody.
			if (error){
				dodajKomunikatBledu(error, root);
			} else{
				auto metodaRPC = Aplikacja::pobierzInstancje().fabrykator_.TworzMetodeRPC(root, ref_);
				if (metodaRPC){
					if (metodaRPC->obsluzMetode(root)){
						//Pobieranie flag steruj¹cych dla pakietu zwrotnego.
						flagi_ = metodaRPC->pobierzFlagi();
					}
				}
			}

			Json::FastWriter writer;
			MetodaRPC::dodajCRC(root);
			wyslij_ = writer.write(root);
			return error == RPC_OK;
		}
		return false;
	}

	void DaneTCP::dodajKomunikatBledu(int blad, Json::Value& root){
		switch (blad){
		case RPC_OK:
			break;
		case RPC_ERROR_NEED_AUTHORIZATION:
			root[METODA_RPC_THROW][METODA_RPC_TYPE] = "Wymagana autoryzacja.";
			root[METODA_RPC_THROW][METODA_RPC_KOMUNIKAT] = "Metoda wymaga autoryzacji.";
			break;
		default:
			root[METODA_RPC_THROW][METODA_RPC_TYPE] = "Nieznany blad";
			root[METODA_RPC_THROW][METODA_RPC_KOMUNIKAT] = "Wystapil nieznany blad.";
			break;
		}
	}

	bool DaneTCP::odbierzWewnetrzna(){
		u_int64 rozmiar = 0;
		u_int64 header = 0;
		int rezultat = 0;
		std::vector <char> bufor;
		long tempRozmiar = 0;
		do{
			rezultat = ref_.odbierz((char*)&header, sizeof(u_int64));
			if (rezultat <= 0){
				if (rezultat == 0){
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					}
					return false;
				} else{
					if (WSAEWOULDBLOCK == WSAGetLastError()){
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						continue;
					} else{
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(WSAGetLastError()));
						}
						return false;
					}
				}
			}

			header = ntohll(header);

			rozmiar = (0xFFFFFFFF00000000 & header) >> 32;
			flagi_ = header & 0x00000000FFFFFFFF;

			bufor.reserve(rozmiar);
			bufor.resize(rozmiar, 0);
			do{
				rezultat = ref_.odbierz(&bufor.data()[tempRozmiar], rozmiar - tempRozmiar);
				if (rezultat <= 0){
					if (rezultat == 0){
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
						}
						return false;
					} else{
						if (WSAEWOULDBLOCK == WSAGetLastError()){
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							continue;
						} else{
							if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji recv: " + std::to_string(WSAGetLastError()));
							}
							return false;
						}
					}
				}
				tempRozmiar += rezultat;
			} while (tempRozmiar != rozmiar && !ref_.czyCzekaNaZakonczenie());

		} while ( (rozmiar == 0 || tempRozmiar != rozmiar) && !ref_.czyCzekaNaZakonczenie());

		std::string s(bufor.begin(), bufor.end());
		odbierz_ = std::move(s);
		return rozmiar > 0;
	}

	bool DaneTCP::wyslijWewnetrzna(){
		int rezultat = 0;
		u_int64 header = 0;
		u_int64 rozmiar = wyslij_.size();
		
		header = (rozmiar << 32) & 0xFFFFFFFF00000000 | flagi_ & 0x00000000FFFFFFFF;
		header = htonll(header);
		rezultat = ref_.wyslij((char*)&header, sizeof(u_int64));
		if (rezultat <= 0){
			if (rezultat == 0){
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
				}
			} else{
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(WSAGetLastError()));
				}
			}
			return false;
		}

		long tempRozmiar = rozmiar;
		do{
			rezultat = ref_.wyslij(&(wyslij_.data()[rozmiar - tempRozmiar]), rozmiar);
			if (rezultat <= 0){
				if (rezultat == 0){
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
					}
				} else{
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji send: " + std::to_string(WSAGetLastError()));
					}
				}
				return false;
			}
			tempRozmiar -= rezultat;
		} while (tempRozmiar != 0);

		return true;
	}

	void DaneTCP::wlaczKompresje(){
		flagi_ |= 0x1;
	}

	void DaneTCP::wlaczAutoryzacje(){
		flagi_ |= 0x2;
	}

	bool DaneTCP::kompresja(){
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
				error_ = 0;
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
			error_ = -1;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Z_MEM_ERROR");
			}
			break;
		case Z_BUF_ERROR:
			error_ = -1;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Z_BUF_ERROR");
			}
			break;
		default:
			error_ = -1;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Niezidentyfikowany.");
			}
			break;
		}
		return error_ == 0;
	}

	bool DaneTCP::dekompresja(){

		uLongf unSize = odbierz_.size() - 4;
		uLongf rozmiar = ((u_char)odbierz_[0] << 24) | ((u_char)odbierz_[1] << 16) | ((u_char)odbierz_[2] << 8) | (u_char)odbierz_[3];
		std::string out;
		out.resize(rozmiar, 0);
		int ret = uncompress((Bytef*)out.data(), &rozmiar, (Bytef*)&odbierz_.data()[4], unSize);

		switch (ret)
		{
		case Z_OK:
			{
				error_ = 0;
				odbierz_ = out;
			}
			break;
		case Z_MEM_ERROR:
			error_ = -1;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Z_MEM_ERROR");
			}
			break; 
		case Z_BUF_ERROR:
			error_ = -1;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Z_BUF_ERROR");
			}
			break;
		case Z_DATA_ERROR:
			error_ = -1;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Z_DATA_ERROR");
			}
			break;
		default:
			error_ = -1;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d dekompresji danych: Niezidentyfikowany");
			}
			break;
		}
		return error_ == 0;
	}

	bool DaneTCP::szyfrowanie(const std::string& klucz){

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

		return !wyslij_.empty();
	}

	bool DaneTCP::deszyfrowanie(const std::string& klucz){
		VMPC_MAC szyfr;
		SHA3 skrotKlucza(klucz);
		auto firstWektor = odbierz_.begin() + 20;
		auto firstMessage = firstWektor + skrotKlucza.pobierzKontener().size();
		VMPC_MAC::Bufor macVO(odbierz_.begin(), firstWektor);
		VMPC_MAC::Bufor vektorVO(firstWektor, firstMessage);

		odbierz_.erase(odbierz_.begin(), firstMessage);

		szyfr.InitKey(skrotKlucza.pobierzKontener(), vektorVO);
		szyfr.DecryptMAC(odbierz_);
		
		return !odbierz_.empty() && szyfr.OutputMAC() == macVO;
	}

	int DaneTCP::przygotujDoWyslania(){
		error_ = 0;
		if (flagi_ & 0x1){
			if (!kompresja())
				return error_;
		}
		if (flagi_ & 0x2){
			if (ref_.czyAutoryzowany()){
				if (!szyfrowanie(ref_.pobierzKlucz()))
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
		error_ = 0;
		if (flagi_ & 0x2){
			if (ref_.czyAutoryzowany()){
				if (!deszyfrowanie(ref_.pobierzKlucz()))
					return error_;
			} else{
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Próba deszyfrowania bez podania klucza.");
				}
				flagi_ &= ~0x2;
			}
		}
		if (flagi_ & 0x1){
			if (!dekompresja())
				return error_;
		}
		return error_;
	}
}