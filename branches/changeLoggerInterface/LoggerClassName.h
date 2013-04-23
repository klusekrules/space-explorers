#pragma once

#define CLASSNAME(C) LoggerClassName::className<C>()
/**
* Klasa bazowa u�ywana do stworzenia jednolitego interfajsu
* dla klasy generuj�cej logi z aplikacji.
*/
class LoggerClassName {
public:	
	/**
	* Funkjca pobieraj�ca nazw� klasy przekazanej jako argument szablonu.
	* \return Nazwa klasy przekazanej przez parametr szablonu.
	*/
	template< class C >
	static string className() {
		return string(typeid(C).name()).substr(6);
	}
};