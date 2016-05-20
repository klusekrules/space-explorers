#include "VMPC_MAC.h"
#include <string.h>
#include "keccak.h"

VMPC_MAC::VMPC_MAC()
{
	P.reserve(256);
	for (size_t x = 0; x < 256; ++x){//Permut123[x]=x
		P.emplace_back(static_cast<unsigned char>(x));
	}

	m1 = m2 = m3 = m4 = mn = 0;
	MAC.clear();
	MAC.resize(32, 0);
}

VMPC_MAC::~VMPC_MAC(){
	P.clear();
	MAC.clear();
	s = n = m1 = m2 = m3 = m4 = mn = 0;
}

void VMPC_MAC::InitKeyRound(const Bufor& Data)
/*Data: klucz lub wektor inicjujacy
Len=1,2,3,...,64: dlugosc klucza/wektora inicjujacego (w bajtach)
Src=0: pierwsze inicjowanie klucza (tablica P i zmienna s zostana najpierw przywrocone do stanu poczatkowego)
Src=1: ponowne inicjowanie klucza, np. wektorem inicjujacym*/
{
	auto Len = Data.size();	
	unsigned char k = 0;
	n = 0;

	for (int x = 0; x<768; x++)
	{
		s = P[(s + P[n] + Data[k]) & 255];

		unsigned char t = P[n];  P[n] = P[s];  P[s] = t;

		k++;  if (k == Len) k = 0;
		n++;
	}
}

void VMPC_MAC::InitKey(const Bufor& Key, const Bufor& Vec)   //LeyLen, VecLen={1,2,3,...,256}
{
	InitKeyRound(Key);
	InitKeyRound(Vec);
	InitKeyRound(Key);
}

void VMPC_MAC::Encrypt(Bufor& Data)
{
	auto Len = Data.size();
	for (unsigned int x = 0; x<Len; x++)
	{
		s = P[(s + P[n]) & 255];

		Data[x] ^= P[(P[P[s]] + 1) & 255];

		unsigned char t = P[n];  P[n] = P[s];  P[s] = t;

		n++;
	}
}

void VMPC_MAC::EncryptMAC(std::string& Data)
{
	auto Len = Data.size();
	for (unsigned int x = 0; x<Len; x++)
	{
		s = P[(s + P[n]) & 255];

		Data[x] ^= P[(P[P[s]] + 1) & 255];

		m4 = P[(m4 + m3) & 255];
		m3 = P[(m3 + m2) & 255];
		m2 = P[(m2 + m1) & 255];
		m1 = P[(m1 + s + Data[x]) & 255];

		MAC[mn] ^= m1;
		MAC[mn + 1] ^= m2;
		MAC[mn + 2] ^= m3;
		MAC[mn + 3] ^= m4;

		unsigned char t = P[n];  P[n] = P[s];  P[s] = t;

		mn = (mn + 4) & 31;
		n++;
	}
}

void VMPC_MAC::DecryptMAC(std::string& Data)
{
	auto Len = Data.size();
	for (unsigned int x = 0; x<Len; x++)
	{
		s = P[(s + P[n]) & 255];

		m4 = P[(m4 + m3) & 255];
		m3 = P[(m3 + m2) & 255];
		m2 = P[(m2 + m1) & 255];
		m1 = P[(m1 + s + Data[x]) & 255];

		MAC[mn] ^= m1;
		MAC[mn + 1] ^= m2;
		MAC[mn + 2] ^= m3;
		MAC[mn + 3] ^= m4;

		Data[x] ^= P[(P[P[s]] + 1) & 255];

		unsigned char t = P[n];  P[n] = P[s];  P[s] = t;

		mn = (mn + 4) & 31;
		n++;
	}
}

void VMPC_MAC::EncryptMAC(Bufor & Data){
	auto Len = Data.size();
	for (unsigned int x = 0; x<Len; x++)
	{
		s = P[(s + P[n]) & 255];

		Data[x] ^= P[(P[P[s]] + 1) & 255];

		m4 = P[(m4 + m3) & 255];
		m3 = P[(m3 + m2) & 255];
		m2 = P[(m2 + m1) & 255];
		m1 = P[(m1 + s + Data[x]) & 255];

		MAC[mn] ^= m1;
		MAC[mn + 1] ^= m2;
		MAC[mn + 2] ^= m3;
		MAC[mn + 3] ^= m4;

		unsigned char t = P[n];  P[n] = P[s];  P[s] = t;

		mn = (mn + 4) & 31;
		n++;
	}
}

void VMPC_MAC::DecryptMAC(Bufor & Data){
	auto Len = Data.size();
	for (unsigned int x = 0; x<Len; x++)
	{
		s = P[(s + P[n]) & 255];

		m4 = P[(m4 + m3) & 255];
		m3 = P[(m3 + m2) & 255];
		m2 = P[(m2 + m1) & 255];
		m1 = P[(m1 + s + Data[x]) & 255];

		MAC[mn] ^= m1;
		MAC[mn + 1] ^= m2;
		MAC[mn + 2] ^= m3;
		MAC[mn + 3] ^= m4;

		Data[x] ^= P[(P[P[s]] + 1) & 255];

		unsigned char t = P[n];  P[n] = P[s];  P[s] = t;

		mn = (mn + 4) & 31;
		n++;
	}
}

const VMPC_MAC::Bufor& VMPC_MAC::OutputMAC()
{
	for (unsigned int x = 1; x <= 24; x++)
	{
		s = P[(s + P[n]) & 255];

		m4 = P[(m4 + m3 + x) & 255];
		m3 = P[(m3 + m2 + x) & 255];
		m2 = P[(m2 + m1 + x) & 255];
		m1 = P[(m1 + s + x) & 255];

		MAC[mn] ^= m1;
		MAC[mn + 1] ^= m2;
		MAC[mn + 2] ^= m3;
		MAC[mn + 3] ^= m4;

		unsigned char t = P[n];  P[n] = P[s];  P[s] = t;

		mn = (mn + 4) & 31;
		n++;
	}
	InitKeyRound(MAC);
	MAC.clear();
	MAC.resize(20, 0);
	Encrypt(MAC);
	return MAC;
}
