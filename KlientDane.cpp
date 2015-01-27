#include "Klient.h"
#include "zlib.h"

namespace SpEx{
	Klient::Dane::Dane(Klient& ref)
		: ref_(ref), flagi_(0)
	{
	}

	Klient::Dane::Dane(Klient& ref, std::string&& dane)
		: ref_(ref), dane_(dane), flagi_(0)
	{
	}

	bool Klient::Dane::odbierz(int & error){
		u_int64 rozmiar = 0;
		u_int64 header = 0;
		int rezultat = 0;

		rezultat = recv(ref_.gniazdo_, (char*)&header, sizeof(u_int64), 0);
		header = ntohll(header);
	
		rozmiar = (0xFFFFFFFF00000000 & header) >> 32;
		flagi_ = header & 0x00000000FFFFFFFF;

		if (rezultat <= 0){
			error = (rezultat == 0 ? 0 : WSAGetLastError());
			return false;
		}
		long tempRozmiar = 0;
		std::vector <char> bufor;
		bufor.reserve(rozmiar + 1);
		bufor.resize(rozmiar + 1, 0);
		do{
			rezultat = recv(ref_.gniazdo_, &bufor.data()[tempRozmiar], rozmiar - tempRozmiar, 0);
			if (rezultat <= 0){
				error = (rezultat == 0 ? 0 : WSAGetLastError());
				if (WSAEWOULDBLOCK == error){
					continue;
				} else{
					return false;
				}
			}
			tempRozmiar += rezultat;
		} while (tempRozmiar != rozmiar && !ref_.czyZakonczyc());
		std::string s(bufor.begin(), bufor.end());
		dane_ = std::move(s); 
		error = 0;
		return rozmiar > 0;
	}

	bool Klient::Dane::wyslij(int & error){
		int rezultat = 0;
		u_int64 header = 0;
		u_int64 rozmiar = dane_.size();
		
		header = (rozmiar << 32) & 0xFFFFFFFF00000000 | flagi_ & 0x00000000FFFFFFFF;
		header = htonll(header);
		rezultat = send(ref_.gniazdo_, (char*)&header, sizeof(u_int64), 0);
		
		if (rezultat <= 0){
			error = (rezultat == 0 ? 0 : WSAGetLastError());
			return false;
		}
		long tempRozmiar = rozmiar;
		do{
			rezultat = send(ref_.gniazdo_, &(dane_.data()[rozmiar - tempRozmiar]), rozmiar, 0);
			if (rezultat <= 0){
				error = (rezultat == 0 ? 0 : WSAGetLastError());
				return false;
			}
			tempRozmiar -= rezultat;
		} while (tempRozmiar != 0);
		error = 0;
		return true;
	}

	void Klient::Dane::wlaczKompresje(){
		flagi_ |= 0x1;
	}

	void Klient::Dane::wlaczAutoryzacje(){
		flagi_ |= 0x2;
	}

	const std::string& Klient::Dane::pobierzDane(){
		return dane_;
	}

	bool Klient::Dane::kompresja(){
		auto rozmiar = dane_.size();
		auto bound = compressBound(rozmiar);
		uLongf after = bound;
		std::string out;
		out.resize(after, 0);
		int ret = compress((Bytef*)out.data(), &after, (const Bytef*)dane_.data(), rozmiar);
		
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
				dane_ = temp + out;
			}
			break;
		case Z_MEM_ERROR:
			error_ = -1;
			break;
		case Z_BUF_ERROR:
			error_ = -1;
			break;
		default:
			error_ = -1;
			break;
		}
		return error_ == 0;
	}

	bool Klient::Dane::dekompresja(){

		uLongf unSize = dane_.size() - 4;
		uLongf rozmiar = ((u_char)dane_[0] << 24) | ((u_char)dane_[1] << 16) | ((u_char)dane_[2] << 8) | (u_char)dane_[3];
		std::string out;
		out.resize(rozmiar, 0);
		int ret = uncompress((Bytef*)out.data(), &rozmiar, (Bytef*)&dane_.data()[4], unSize);

		switch (ret)
		{
		case Z_OK:
			{
				error_ = 0;
				dane_ = out;
			}
			break;
		case Z_MEM_ERROR:
			error_ = -1;
			break; 
		case Z_BUF_ERROR:
			error_ = -1;
			break;
		case Z_DATA_ERROR:
			error_ = -1;
			break;
		default:
			error_ = -1;
			break;
		}
		return error_ == 0;
	}

	bool Klient::Dane::szyfrowanie(){
		return error_ == 0;
	}

	bool Klient::Dane::deszyfrowanie(){
		return error_ == 0;
	}

	int Klient::Dane::przygotujDoWyslania(){
		error_ = 0;
		if (flagi_ & 0x1){
			if (!kompresja())
				return error_;
		}
		if (flagi_ & 0x2){
			if (!szyfrowanie())
				return error_;
		}
		return error_;
	}

	int Klient::Dane::przetworzPoOdebraniu(){
		error_ = 0;
		if (flagi_ & 0x2){
			if (!deszyfrowanie())
				return error_;
		}
		if (flagi_ & 0x1){
			if (!dekompresja())
				return error_;
		}
		return error_;
	}
}