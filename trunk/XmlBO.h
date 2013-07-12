#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class THROW { };
class NOTHROW { };

class XmlBO{
private:
	template < typename T > 
	static TiXmlElement * blad( bool czyWezelPusty , string nazwaWezla ){
		return nullptr;
	}

	template < > 
	static TiXmlElement * blad<THROW>( bool czyWezelPusty , string nazwaWezla ){
		throw WyjatekParseraXML(EXCEPTION_PLACE,exception((nazwaWezla + " isNull=" + to_string(czyWezelPusty)).c_str()),WyjatekParseraXML::trescBladStrukturyXml);
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
	
	template<typename T>
	static bool WczytajAtrybut( TiXmlElement* wezel , const string& nazwa, PodstawowyInterfejs<T>& obiekt ){
		if(!wezel)
			return false;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return false;
		obiekt(napis);
		return true;
	}

	template< >
	static bool WczytajAtrybut<double>( TiXmlElement* wezel , const string& nazwa, PodstawowyInterfejs<double>& obiekt ){
		if(!wezel)
			return false;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return false;
		if(napis->length()>0){
			double tmp;
			tmp = stod(*napis);
			obiekt(tmp);
		}
		return true;
	}

	template< >
	static bool WczytajAtrybut<long double>( TiXmlElement* wezel , const string& nazwa, PodstawowyInterfejs<long double>& obiekt ){
		if(!wezel)
			return false;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return false;
		if(napis->length()>0){
			long double tmp;
			tmp = stold(*napis);
			obiekt(tmp);
		}
		return true;
	}

	template< >
	static bool WczytajAtrybut<int>( TiXmlElement* wezel , const string& nazwa, PodstawowyInterfejs<int>& obiekt ){
		if(!wezel)
			return false;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return false;
		if(napis->length()>0){
			int tmp;
			tmp = stoul(*napis,nullptr,0);
			obiekt(tmp);
		}
		return true;
	}

	template< >
	static bool WczytajAtrybut<unsigned int>( TiXmlElement* wezel , const string& nazwa, PodstawowyInterfejs<unsigned int>& obiekt ){
		if(!wezel)
			return false;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return false;
		if(napis->length()>0){
			unsigned int tmp;
			tmp = stoul(*napis,nullptr,0);
			obiekt(tmp);
		}
		return true;
	}

	template< >
	static bool WczytajAtrybut<float>( TiXmlElement* wezel , const string& nazwa, PodstawowyInterfejs<float>& obiekt ){
		if(!wezel)
			return false;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return false;
		if(napis->length()>0){
			float tmp;
			tmp = stof(*napis);
			obiekt(tmp);
		}
		return true;
	}

	template<typename T>
	static T WczytajAtrybut( TiXmlElement* wezel , const string& nazwa ){
		if(!wezel)
			return 0;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return 0;
		return *napis;
	}

	template< >
	static int WczytajAtrybut<int>( TiXmlElement* wezel , const string& nazwa ){
		if(!wezel)
			return 0;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return 0;
		if(napis->length()>0){
			return stoul(*napis,nullptr,0);
		}
		return 0;
	}

	template< >
	static long double WczytajAtrybut<long double>( TiXmlElement* wezel , const string& nazwa ){
		if(!wezel)
			return 0;
		const string * napis = wezel->Attribute(nazwa);
		if(!napis)
			return 0;
		if(napis->length()>0){
			return stold(*napis);
		}
		return 0;
	}

};