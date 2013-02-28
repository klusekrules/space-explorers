#pragma once

/**
* Klasa bazowa u�ywana do stworzenia jednolitego interfajsu
* dla klasy generuj�cej logi z aplikacji.
*/
template< class C >
class LoggerInterface {
public:

	/**
	* Konstruktor domy�lny klasy z interfejsem do tworzenia log�w.
	* \sa ~LoggerInterface()
	*/
	LoggerInterface(){
	}

	/**
	* Destruktor domy�lny klasy z interfejsem do tworzenia log�w.
	* \sa LoggerInterface()
	*/
	virtual ~LoggerInterface(){
	}
	
	/**
	* Funkjca pobieraj�ca nazw� klasy przekazanej jako argument szablonu.
	* \return Nazwa klasy przekazanej przez parametr szablonu.
	*/
	static string className() {
		return string(typeid(C).name()).substr(6);
	}

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	virtual string toString() const abstract;
};