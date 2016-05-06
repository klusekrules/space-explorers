#include "Szyfrowanie.h"
#include "Algorytmy\VMPC_MAC.h"
#include "Algorytmy\SHA3.h"
#include "RPC\StaleRPC.h"
#include "Logger\Log.h"

int SpEx::Szyfrowanie::szyfrowanie_mem_impl(){
	std::string vektor(SLog::Log::pobierzInstancje().pobierzDateCzas());
	VMPC_MAC szyfr;
	SHA3 skrotKlucza(klucz_);
	SHA3 skrotVektora(vektor);
	auto &vektorV = skrotVektora.pobierzKontener();

	szyfr.InitKey(skrotKlucza.pobierzKontener(), vektorV);
	szyfr.EncryptMAC(*dane_);

	auto &macV = szyfr.OutputMAC();

	std::string macS(macV.begin(), macV.end());
	std::string vectorS(vektorV.begin(), vektorV.end());
	*dane_ = macS + vectorS + *dane_;
	if (dane_->empty())
		return RPC_ERROR_NO_DATA;
	return RPC_OK;
}

int SpEx::Szyfrowanie::deszyfrowanie_mem_impl(){
	VMPC_MAC szyfr;
	SHA3 skrotKlucza(klucz_);
	auto firstWektor = dane_->begin() + 20;
	auto firstMessage = firstWektor + skrotKlucza.pobierzKontener().size();
	VMPC_MAC::Bufor macVO(dane_->begin(), firstWektor);
	VMPC_MAC::Bufor vektorVO(firstWektor, firstMessage);

	dane_->erase(dane_->begin(), firstMessage);

	szyfr.InitKey(skrotKlucza.pobierzKontener(), vektorVO);
	szyfr.DecryptMAC(*dane_);

	if (dane_->empty())
		return RPC_ERROR_NO_DATA;
	if (szyfr.OutputMAC() != macVO)
		return RPC_ERROR_DECRYPTION_FAIL;
	return RPC_OK;
}
