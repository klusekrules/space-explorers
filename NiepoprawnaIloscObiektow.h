#pragma once
#include "TypyProste\\Wyjatek.h"
namespace SpEx{
/**
* Wyj¹tek informuje, ze przekazana iloœæ obiektów jest nie poprawna dla danej operacji.
*/
class NiepoprawnaIloscObiektow :
	virtual public SLog::LoggerInterface,
	public STyp::Wyjatek
{
public:
	static const STyp::Identyfikator idNiepoprawnaIloscObiektow;
	
	NiepoprawnaIloscObiektow(const STyp::Tekst& tPlik, const STyp::Ilosc& iLinia, const STyp::Ilosc& ilosc);
	virtual ~NiepoprawnaIloscObiektow(void) = default;
	
	const STyp::Ilosc& getIlosc() const;
	void setIlosc(const STyp::Ilosc& ilosc);
	
	STyp::Tekst generujKomunikat() const override;

	std::string napis() const override;

private:
	STyp::Ilosc i;
	
	static const STyp::Tekst tytulNiepoprawnaIloscObiektow;
	static const STyp::Tekst trescNiepoprawnaIloscObiektow;
};

}