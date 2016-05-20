#pragma once
#include "AlgorytmySymbol.h"
#include <vector>
#include <string>

class ALGORYTMY_API VMPC_MAC
{
public:
	typedef std::vector < unsigned char > Bufor;
	VMPC_MAC();
	~VMPC_MAC();
	void InitKey(const Bufor& Key, const Bufor& Vector);
	
	void EncryptMAC(std::string& Data);
	void DecryptMAC(std::string& Data);
	void EncryptMAC(Bufor& Data);
	void DecryptMAC(Bufor& Data);
	const Bufor& OutputMAC();
private:
	Bufor P;
	unsigned char s, n;

	Bufor MAC;
	unsigned char m1, m2, m3, m4, mn;

	void Encrypt(Bufor& Data);
	void InitKeyRound(const Bufor&);
};

