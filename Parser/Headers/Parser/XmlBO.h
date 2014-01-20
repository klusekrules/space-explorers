#pragma once
#include "ParserInterfejs.h"
#include "TypyProste\TypyProste.h"
#include "WyjatekParser.h"
#include <exception>
#include <string>
#include <algorithm>

class THROW { };
class NOTHROW { };

class XmlBO{

public:
	typedef std::shared_ptr<SPar::ParserElement> ElementWezla;
	typedef std::shared_ptr<SPar::ParserAtrybut> AtrybutElementu;
	typedef std::function< bool(ElementWezla) > OperacjaWezla;
	typedef std::function< bool(AtrybutElementu) > OperacjaAtrybutu;

private:

	template < typename T > 
	static void trim( std::string &s ){
		s.erase(std::remove_if(s.begin(), s.end(), isSpace), s.end());
	}

	template < > 
	static void trim<STyp::SPG::Tekst>( std::string &s ){
	}

	static void decimal_point(std::string &s){
		std::replace_if(s.begin(),s.end(),[](char c){ return c==',' || c=='.'; },std::use_facet<std::numpunct<char>>(std::locale()).decimal_point());
	}

	static bool isSpace( unsigned char c ){
		return isspace(c)!=0;
	}

	template < typename T > 
	static ElementWezla bladWezla(ElementWezla element , const std::string& nazwaWezla){
		return nullptr;
	}

	template < > 
	static ElementWezla bladWezla<THROW>(ElementWezla element, const std::string& nazwaWezla){
		throw SPar::WyjatekParser(EXCEPTION_PLACE, std::string(), element.get() , std::string("B�ad odczytu elementu-dziecka o nazwie " + nazwaWezla + " z wezla: ") );
	}

	template < typename T > 
	static bool bladAtrybutu(ElementWezla element, const std::string& nazwaAtrybutu){
		return false;
	}

	template < > 
	static bool bladAtrybutu<THROW>(ElementWezla element, const std::string& nazwaAtrybutu){
		throw SPar::WyjatekParser(EXCEPTION_PLACE, std::string(), element.get(), std::string("B�ad odczytu atrybutu o nazwie " + nazwaAtrybutu + " z wezla: "));
	}

	template < typename T > 
	static void Zaladuj(const std::string& atrybut, STyp::PodstawowyInterfejs<T>& obiekt){
		obiekt(atrybut);
	}

	template <  > 
	static void Zaladuj<double>(const std::string& atrybut, STyp::PodstawowyInterfejs<double>& obiekt){
		double tmp;
		std::string kopia = atrybut;
		decimal_point(kopia);
		tmp = stod(kopia);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<long double>(const std::string& atrybut, STyp::PodstawowyInterfejs<long double>& obiekt){
		long double tmp;
		std::string kopia = atrybut;
		decimal_point(kopia);
		tmp = stold(kopia);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<int>(const std::string& atrybut, STyp::PodstawowyInterfejs<int>& obiekt){
		int tmp;
		tmp = stoul(atrybut,nullptr,0);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<unsigned int>(const std::string& atrybut, STyp::PodstawowyInterfejs<unsigned int>& obiekt){
		unsigned int tmp;
		tmp = stoul(atrybut);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<float>(const std::string& atrybut, STyp::PodstawowyInterfejs<float>& obiekt){
		float tmp;
		std::string kopia = atrybut;
		decimal_point(kopia);
		tmp = stof(kopia);
		obiekt(tmp);
	}
	
public:

	static bool ForEach(ElementWezla wezel, const char* nazwa, OperacjaWezla& funkcja){
		for(ElementWezla element = wezel->pobierzElement(nazwa);element!=nullptr; element = element->pobierzNastepnyElement(nazwa)){
			if(!funkcja(element))
				return false;
		}
		return true;
	}

	static bool ForEach(ElementWezla wezel, OperacjaAtrybutu& funkcja){
		for (AtrybutElementu element = wezel->pobierzAtrybut(nullptr); element != nullptr; element = element->pobierzNastepnyAtrybut()){
			if (!funkcja(element))
				return false;
		}
		return true;
	}

	static bool ForEach(ElementWezla wezel, OperacjaWezla& funkcja){
		return ForEach(wezel,nullptr,funkcja);
	}

	template<typename T>
	static ElementWezla ZnajdzWezel(ElementWezla wezel, const std::string& nazwa, ElementWezla poprzedniWezel = nullptr){
		if(wezel==nullptr || nazwa.empty())
			return bladWezla<T>(wezel, nazwa);
		if(poprzedniWezel)
			return poprzedniWezel->pobierzNastepnyElement(nazwa.c_str());
		else
			return wezel->pobierzElement(nazwa.c_str());
	}
	
	template<typename T>
	static ElementWezla ZnajdzWezelJezeli(ElementWezla wezel,
		const std::string& nazwaWezla,
		const std::string& nazwaAtrybutu,
		const std::string& wartoscAtrybutu,
		ElementWezla poprzedniWezel = nullptr)
	{
		if(wezel==nullptr || nazwaWezla.empty() || nazwaAtrybutu.empty())
			return bladWezla<T>(wezel, nazwaWezla);
		ElementWezla element = poprzedniWezel ? poprzedniWezel : wezel;
		for (auto wezelDziecko = element->pobierzElement(nazwaWezla.c_str()); wezelDziecko != nullptr; wezelDziecko = wezelDziecko->pobierzNastepnyElement(nazwaWezla.c_str())){
			auto tmp = wezelDziecko->pobierzAtrybut(nazwaAtrybutu.c_str());
			if(tmp && !strcmp(wartoscAtrybutu.c_str(),tmp) )
				return wezelDziecko;
		}
		return nullptr;
	}
	
	template<typename K,typename T>
	static bool WczytajAtrybut(ElementWezla wezel, const std::string& nazwa, STyp::PodstawowyInterfejs<T>& obiekt){
		if(!wezel)
			return bladAtrybutu<K>( wezel, nazwa);
		auto napis = wezel->pobierzAtrybut(nazwa.c_str());
		if(!napis)
			return bladAtrybutu<K>(wezel, nazwa);
		std::string atrybut(napis->pobierzWartosc());
		trim<T>(atrybut);
		if(atrybut.size()>0){
			Zaladuj<T>(atrybut,obiekt);
			return true;
		}
		return bladAtrybutu<K>(wezel, nazwa);
	}
	
	template<typename T>
	static T WczytajAtrybut(ElementWezla wezel, const std::string& nazwa, T domyslnaWartosc){
		if(!wezel)
			return domyslnaWartosc;
		auto ptr = wezel->pobierzAtrybut(nazwa.c_str());
		if(!ptr)
			return domyslnaWartosc;
		return std::string(ptr->pobierzWartosc());
	}

	template< >
	static int WczytajAtrybut<int>(ElementWezla wezel, const std::string& nazwa, int domyslnaWartosc){
		if(!wezel)
			return domyslnaWartosc;
		auto ptr = wezel->pobierzAtrybut(nazwa.c_str());
		if(!ptr)
			return domyslnaWartosc;
		const std::string napis(ptr->pobierzWartosc());
		if(napis.length()>0){
			return stoul(napis,nullptr,0);
		}
		return domyslnaWartosc;
	}

	template< >
	static unsigned int WczytajAtrybut<unsigned int>(ElementWezla wezel, const std::string& nazwa, unsigned int domyslnaWartosc){
		if(!wezel)
			return domyslnaWartosc;
		auto ptr = wezel->pobierzAtrybut(nazwa.c_str());
		if(!ptr)
			return domyslnaWartosc;
		const std::string napis(ptr->pobierzWartosc());
		if(napis.length()>0){
			return stoul(napis,nullptr,0);
		}
		return domyslnaWartosc;
	}

	template< >
	static long double WczytajAtrybut<long double>(ElementWezla wezel, const std::string& nazwa, long double domyslnaWartosc){
		if(!wezel)
			return domyslnaWartosc;
		auto ptr = wezel->pobierzAtrybut(nazwa.c_str());
		if(!ptr)
			return domyslnaWartosc;
		const std::string napis(ptr->pobierzWartosc());
		if(napis.length()>0){			
			std::string kopia = napis;
			decimal_point(kopia);
			return stold(kopia);
		}
		return domyslnaWartosc;
	}
};
