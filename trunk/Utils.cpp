#include "Utils.h"
#include "Aplikacja.h"

namespace SpEx{

	const STyp::Fluktuacja Utils::FMAX = 1.0;
	const STyp::Fluktuacja Utils::FMIN = 0.0;

	XmlBO::ElementWezla STACKTHROW::bladWezla(XmlBO::ElementWezla element, const std::string& nazwaWezla){
		return THROW::bladWezla(element, nazwaWezla, Aplikacja::pobierzInstancje().pobierzSladStosu(), Utils::pobierzDebugInfo());
	}

	bool STACKTHROW::bladAtrybutu(XmlBO::ElementWezla element, const std::string& nazwaAtrybutu){
		return THROW::bladAtrybutu(element, nazwaAtrybutu, Aplikacja::pobierzInstancje().pobierzSladStosu(), Utils::pobierzDebugInfo());
	}

	void Utils::generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel){
		SPar::ParserUtils::generujWyjatekBleduStruktury(wezel, Aplikacja::pobierzInstancje().pobierzSladStosu(), pobierzDebugInfo());
	}
	std::string Utils::pobierzDebugInfo(){
		return Aplikacja::pobierzInstancje().pobierzDebugInfo();
	}

	std::shared_ptr<SZmi::ZmianaInterfejs> Utils::TworzZmiane(XmlBO::ElementWezla wezel){
		if (!wezel)
			return nullptr;
		auto zmiana = Aplikacja::pobierzInstancje().fabrykator_.TworzZmiane(wezel);
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
