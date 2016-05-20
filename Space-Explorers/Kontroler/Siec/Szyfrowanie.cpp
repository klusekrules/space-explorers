#include "Szyfrowanie.h"
#include "Algorytmy\VMPC_MAC.h"
#include "Algorytmy\SHA3.h"
#include "RPC\StaleRPC.h"
#include "Logger\Log.h"
#include <WinSock2.h>
#define CHUNK 262144

SpEx::Szyfrowanie::Szyfrowanie(const std::string &klucz, FILE * in, FILE * out)
	: plikin_(in), plikout_(out), dane_(nullptr),skrotKlucza_(klucz)
{
}

SpEx::Szyfrowanie::Szyfrowanie(const std::string & klucz, std::string & dane)
	: plikout_(nullptr), plikin_(nullptr), dane_(&dane), skrotKlucza_(klucz)
{
}

int SpEx::Szyfrowanie::szyfrowanie() {
	if (plikin_ != nullptr && plikout_ != nullptr)
		return szyfrowanie_file_impl();
	if (dane_ != nullptr)
		return szyfrowanie_mem_impl();
	return ERROR_UNIDENTIFYING_ENCRYPTING_DATA_SOURCE;
}

int SpEx::Szyfrowanie::szyfrowanie_mem_impl(){
	std::string vektor(SLog::Log::pobierzInstancje().pobierzDateCzas());
	VMPC_MAC szyfr;
	SHA3 skrotVektora(vektor);
	auto &vektorV = skrotVektora.pobierzKontener();

	szyfr.InitKey(skrotKlucza_.pobierzKontener(), vektorV);
	szyfr.EncryptMAC(*dane_);

	auto &macV = szyfr.OutputMAC();

	std::string macS(macV.begin(), macV.end());
	std::string vectorS(vektorV.begin(), vektorV.end());
	*dane_ = macS + vectorS + *dane_;
	if (dane_->empty())
		return ERROR_LACK_OF_DATA;
	return ERROR_SUCCESS;
}

int SpEx::Szyfrowanie::szyfrowanie_file_impl(){
	std::string vektor(SLog::Log::pobierzInstancje().pobierzDateCzas());
	VMPC_MAC szyfr;
	SHA3 skrotVektora(vektor);
	auto &vektorV = skrotVektora.pobierzKontener();

	szyfr.InitKey(skrotKlucza_.pobierzKontener(), vektorV);
	std::string dane;
	dane.resize(CHUNK, 0);
	bool endWhile = false;
	int error = 0;
	do {

		if (dane.size() != CHUNK) {
			dane.resize(CHUNK,0);
		}
		auto read_size = fread(&dane[0], 1, CHUNK, plikin_);
		error = ferror(plikin_);
		if (error) {
			return error;
		}

		if (read_size != CHUNK) {
			dane.resize(read_size,0);
		}

		endWhile = (feof(plikin_)!=0);
		szyfr.EncryptMAC(dane);
		auto write_size = fwrite(&dane[0], 1, dane.size(), plikout_);
		error = ferror(plikout_);
		if ( write_size != dane.size() || error) {
			if(error)
				return error;
			return ERROR_ENCRYPTING_UNIDENTIFYING_WRITE;
		}

	} while (!endWhile);

	auto &macV = szyfr.OutputMAC();

	std::string macS(macV.begin(), macV.end());
	std::string vectorS(vektorV.begin(), vektorV.end());

	auto write_size = fwrite(&macS[0], 1, macS.size(), plikout_);
	error = ferror(plikout_);
	if (write_size != macS.size() || error) {
		if (error)
			return error;
		return ERROR_ENCRYPTING_UNIDENTIFYING_WRITE;
	}

	write_size = fwrite(&vectorS[0], 1, vectorS.size(), plikout_);
	error = ferror(plikout_);
	if (write_size != vectorS.size() || error) {
		if (error)
			return error;
		return ERROR_ENCRYPTING_UNIDENTIFYING_WRITE;
	}

	return ERROR_SUCCESS;
}


int SpEx::Szyfrowanie::deszyfrowanie() {
	if (plikin_ != nullptr && plikout_ != nullptr)
		return deszyfrowanie_file_impl();
	if (dane_ != nullptr)
		return deszyfrowanie_mem_impl();
	return ERROR_UNIDENTIFYING_DECRYPTING_DATA_SOURCE;
}

int SpEx::Szyfrowanie::deszyfrowanie_mem_impl(){
	VMPC_MAC szyfr;
	auto firstWektor = dane_->begin() + 20;
	auto firstMessage = firstWektor + skrotKlucza_.pobierzKontener().size();
	VMPC_MAC::Bufor macVO(dane_->begin(), firstWektor);
	VMPC_MAC::Bufor vektorVO(firstWektor, firstMessage);

	dane_->erase(dane_->begin(), firstMessage);

	szyfr.InitKey(skrotKlucza_.pobierzKontener(), vektorVO);
	szyfr.DecryptMAC(*dane_);

	if (dane_->empty())
		return ERROR_LACK_OF_DATA;
	if (szyfr.OutputMAC() != macVO)
		return ERROR_DECRYPTION_FAIL;
	return ERROR_SUCCESS;
}

int SpEx::Szyfrowanie::deszyfrowanie_file_impl(){
	VMPC_MAC szyfr;
	int error = 0;

	fseek(plikin_, 0, SEEK_END);
	error = ferror(plikin_);
	if (error) {
		return error;
	}
	auto fileSize = ftell(plikin_);
	auto dateSize = fileSize - (skrotKlucza_.pobierzKontener().size() + 20);

	if (dateSize <= 0) {
		return ERROR_LACK_OF_DATA;
	}

	fseek(plikin_, dateSize, SEEK_SET);
	error = ferror(plikin_);
	if (error) {
		return error;
	}

	VMPC_MAC::Bufor macV;
	macV.resize(20, 0);
	auto read_macV = fread(macV.data(), 1, 20, plikin_); 
	error = ferror(plikin_);
	if (error) {
		return error;
	}

	VMPC_MAC::Bufor vektorV;
	vektorV.resize(skrotKlucza_.pobierzKontener().size(), 0);
	auto read_vectorV = fread(vektorV.data(), 1, skrotKlucza_.pobierzKontener().size(), plikin_);
	error = ferror(plikin_);
	if (error) {
		return error;
	}

	fseek(plikin_, 0, SEEK_SET);
	error = ferror(plikin_);
	if (error) {
		return error;
	}

	szyfr.InitKey(skrotKlucza_.pobierzKontener(), vektorV);

	VMPC_MAC::Bufor dane;
	dane.resize(CHUNK, 0);
	bool endWhile = false;
	do {
		if (dateSize < CHUNK) {
			dane.resize(dateSize, 0);
			endWhile = true;
		}

		auto read_size = fread(dane.data(), 1, dane.size(), plikin_);
		error = ferror(plikin_);
		if (error) {
			return error;
		}

		if(feof(plikin_) != 0)
			return ERROR_LACK_OF_DATA;

		szyfr.DecryptMAC(dane);
		auto write_size = fwrite(dane.data(), 1, dane.size(), plikout_);
		error = ferror(plikout_);
		if (write_size != dane.size() || error) {
			if (error)
				return error;
			return ERROR_ENCRYPTING_UNIDENTIFYING_WRITE;
		}

		dateSize -= dane.size();

	} while (!endWhile && dateSize > 0);

	if (szyfr.OutputMAC() != macV)
		return ERROR_DECRYPTION_FAIL;
	return ERROR_SUCCESS;
}
