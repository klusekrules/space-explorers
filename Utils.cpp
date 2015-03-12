#include "Utils.h"
#include "Aplikacja.h"
#include "Fabrykator.h"

namespace SpEx{

	const STyp::Fluktuacja Utils::FMAX = 1.0;
	const STyp::Fluktuacja Utils::FMIN = 0.0;

	void Utils::generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel){
		SPar::ParserUtils::generujWyjatekBleduStruktury(wezel, Aplikacja::pobierzInstancje().pobierzSladStosu(), pobierzDebugInfo());
	}

	std::string Utils::pobierzDebugInfo(){
		return std::move(Aplikacja::pobierzInstancje().pobierzDebugInfo());
	}

	__int64 Utils::pobierzLiczbeLosowa(){
		return Aplikacja::pobierzInstancje().pobierzNumerLosowy();
	}
	
	std::string Utils::konwertujDoHex(const char * tab, size_t size, bool prefix){
		std::string wartosc;
		size_t offset = 0;

		if (prefix){
			offset = 2;
			wartosc.resize(size * 2 + offset, 0);
			wartosc[0] = '0';
			wartosc[1] = 'x';
		} else{
			wartosc.resize(size * 2, 0);		
		}

		for (size_t i = 0; i < size; ++i){
			char pierwszy = (tab[i] >> 4) & 0x0F, drugi = tab[i] & 0x0F;
			if (pierwszy < 10){
				pierwszy += 0x30;
			} else{
				pierwszy += 55;
			}

			if (drugi < 10){
				drugi += 0x30;
			} else{
				drugi += 55;
			}
			wartosc[(i << 1) + offset] = pierwszy;
			wartosc[(i << 1) + 1 + offset] = drugi;
		}

		return std::move(wartosc);
	}

	std::shared_ptr<SZmi::ZmianaInterfejs> Utils::TworzZmiane(XmlBO::ElementWezla wezel){
		if (!wezel)
			return nullptr;
		auto zmiana = Aplikacja::pobierzInstancje().pobierzFabrykator().tworzZmiane(wezel);
		if (!zmiana)
			Utils::generujWyjatekBleduStruktury(wezel);
		return zmiana;
	}

	std::string Utils::konwersja(const STyp::Czas& czas){
		auto sekundy = static_cast <__int64>(round(czas()));
		char temp[64];
		sprintf_s(temp, 64, "%02lli:%02lli:%02lli", sekundy / 3600, (sekundy % 3600) / 60, (sekundy % 3600) % 60);
		return temp;
	}
	
	bool Utils::pobierzRozszezenie(const std::string & adres, std::string& rozszezenie){
		auto pos = adres.find_last_of('.');
		if (pos == std::string::npos)
			return false;
		auto end = adres.substr(pos+1);
		if (end.empty())
			return false;
		rozszezenie = std::move(end);
		return true;
	}

	std::vector < SLog::Log::TypLogow > Utils::dekodujListeTypowLogow(const std::string& str){
		std::vector < SLog::Log::TypLogow > ret;
		if (str.empty())
			return ret;
		size_t pos = 0;
		size_t start = 0;
		std::string sub;
		while (pos != std::string::npos){
			pos = str.find_first_of(',', pos);
			if (pos == std::string::npos){
				sub = std::move(str.substr(start));
			}
			else{
				sub = std::move(str.substr(start, pos - start));
				start = ++pos;
			}
			if (sub.empty())
				break;
			int i = stoi(sub);
			switch (i)
			{
			case SLog::Log::All: ret.emplace_back(SLog::Log::All);
				break;
			case SLog::Log::Debug: ret.emplace_back(SLog::Log::Debug);
				break;
			case SLog::Log::Info: ret.emplace_back(SLog::Log::Info);
				break;
			case SLog::Log::Warning: ret.emplace_back(SLog::Log::Warning);
				break;
			case SLog::Log::Error: ret.emplace_back(SLog::Log::Error);
				break;
			}
		}
		return ret;
	}
}
