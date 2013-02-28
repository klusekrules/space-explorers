#pragma once

/**
* Klasa bazowa u¿ywana do stworzenia jednolitego interfajsu
* dla klasy generuj¹cej logi z aplikacji.
*/
template< class C >
class LoggerInterface {
public:

	/**
	* Konstruktor domyœlny klasy z interfejsem do tworzenia logów.
	* \sa ~LoggerInterface()
	*/
	LoggerInterface(){
	}

	/**
	* Destruktor domyœlny klasy z interfejsem do tworzenia logów.
	* \sa LoggerInterface()
	*/
	virtual ~LoggerInterface(){
	}
	
	/**
	* Funkjca pobieraj¹ca nazwê klasy przekazanej jako argument szablonu.
	* \return Nazwa klasy przekazanej przez parametr szablonu.
	*/
	static string className() {
		return string(typeid(C).name()).substr(6);
	}

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	virtual string toString() const abstract;
};