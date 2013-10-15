#pragma once
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"
#include <exception>
#include <string>
#include <algorithm>
using std::remove_if;
using std::replace_if;
using std::string;
using std::exception;

class THROW { };
class NOTHROW { };

class XmlBO{
private:

	template < typename T > 
	static void trim( string &s ){
		s.erase(remove_if(s.begin(), s.end(), isSpace), s.end());
	}

	template < > 
	static void trim<SPG::Tekst>( string &s ){
	}

	static void decimal_point( string &s ){
		replace_if(s.begin(),s.end(),[](char c){ return c==',' || c=='.'; },std::use_facet<std::numpunct<char>>(std::locale()).decimal_point());
	}

	static bool isSpace( unsigned char c ){
		return isspace(c)!=0;
	}

	template < typename T > 
	static TiXmlElement * blad( bool czyWezelPusty , const string& nazwaWezla ){
		return nullptr;
	}

	template < > 
	static TiXmlElement * blad<THROW>( bool czyWezelPusty , const string& nazwaWezla ){
		throw WyjatekParseraXML(EXCEPTION_PLACE,exception(string(nazwaWezla + " isNull=" + std::to_string(czyWezelPusty)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
	}

	template < typename T > 
	static bool blad( const string& wezel , const string& nazwaAtrybutu ){
		return false;
	}

	template < > 
	static bool blad<THROW>( const string& wezel , const string& nazwaAtrybutu ){
		string opis("Nie uda³o siê odczytaæ atrybutu: ");
		opis+=nazwaAtrybutu + " z wêz³a: " + wezel;
		throw WyjatekParseraXML(EXCEPTION_PLACE,exception(opis.c_str()),WyjatekParseraXML::trescBladStrukturyXml);
	}

	template < typename T > 
	static void Zaladuj(const string& atrybut, PodstawowyInterfejs<T>& obiekt){
		obiekt(atrybut);
	}

	template <  > 
	static void Zaladuj<double>(const string& atrybut, PodstawowyInterfejs<double>& obiekt){
		double tmp;
		string kopia = atrybut;
		decimal_point(kopia);
		tmp = stod(kopia);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<long double>(const string& atrybut, PodstawowyInterfejs<long double>& obiekt){
		long double tmp;
		string kopia = atrybut;
		decimal_point(kopia);
		tmp = stold(kopia);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<int>(const string& atrybut, PodstawowyInterfejs<int>& obiekt){
		int tmp;
		tmp = stoul(atrybut,nullptr,0);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<unsigned int>(const string& atrybut, PodstawowyInterfejs<unsigned int>& obiekt){
		unsigned int tmp;
		tmp = stoul(atrybut);
		obiekt(tmp);
	}

	template <  > 
	static void Zaladuj<float>(const string& atrybut, PodstawowyInterfejs<float>& obiekt){
		float tmp;
		string kopia = atrybut;
		decimal_point(kopia);
		tmp = stof(kopia);
		obiekt(tmp);
	}
	
public:
	template<typename T>
	static TiXmlElement* ZnajdzWezel( TiXmlElement* wezel , const string& nazwa, TiXmlElement* poprzedniWezel = nullptr ){
		if(wezel==nullptr || nazwa.empty())
			return blad<T>(wezel==nullptr,nazwa);
		if(poprzedniWezel)
			return poprzedniWezel->NextSiblingElement(nazwa);
		else
			return wezel->FirstChildElement(nazwa);
	}
	
	template<typename T>
	static TiXmlElement* ZnajdzWezelJezeli( TiXmlElement* wezel ,
											const string& nazwaWezla,
											const string& nazwaAtrybutu,
											const string& wartoscAtrybutu,
											TiXmlElement* poprzedniWezel = nullptr )
	{
		if(wezel==nullptr || nazwaWezla.empty() || nazwaAtrybutu.empty())
			return blad<T>(wezel==nullptr,nazwaWezla);
		TiXmlElement* element = poprzedniWezel ? poprzedniWezel : wezel;
		for(TiXmlElement* wezelDziecko = element->FirstChildElement(nazwaWezla); wezelDziecko!= nullptr; wezelDziecko = wezelDziecko->NextSiblingElement(nazwaWezla) ){
			auto tmp = wezelDziecko->Attribute(nazwaAtrybutu);
			if(tmp && wartoscAtrybutu == *tmp)
				return wezelDziecko;
		}
		return nullptr;
	}
	
	template<typename K,typename T>
	static bool WczytajAtrybut( TiXmlElement* wezel , const string& nazwa, PodstawowyInterfejs<T>& obiekt ){
		if(!wezel)
			return blad<K>(string(),string());
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return blad<K>(string(wezel->Value()),nazwa);
		string atrybut = *napis;
		trim<T>(atrybut);
		if(atrybut.size()>0){
			Zaladuj<T>(atrybut,obiekt);
			return true;
		}
		return blad<K>(string(wezel->Value()),nazwa);
	}
	
	template<typename T>
	static T WczytajAtrybut( TiXmlElement* wezel , const string& nazwa , T domyslnaWartosc ){
		if(!wezel)
			return domyslnaWartosc;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return domyslnaWartosc;
		return *napis;
	}

	template< >
	static int WczytajAtrybut<int>( TiXmlElement* wezel , const string& nazwa , int domyslnaWartosc ){
		if(!wezel)
			return domyslnaWartosc;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return domyslnaWartosc;
		if(napis->length()>0){
			return stoul(*napis,nullptr,0);
		}
		return domyslnaWartosc;
	}

	template< >
	static long double WczytajAtrybut<long double>( TiXmlElement* wezel , const string& nazwa , long double domyslnaWartosc ){
		if(!wezel)
			return domyslnaWartosc;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return domyslnaWartosc;
		if(napis->length()>0){			
			string kopia = *napis;
			decimal_point(kopia);
			return stold(kopia);
		}
		return domyslnaWartosc;
	}
};