#pragma once
#include "NarzedziaSymbol.h"
#include <vector>
#include <string>
namespace SpEx{

	/**
	* \brief Klasa tworz¹ca wektor z listy argumentów.
	*
	* Klasa s³u¿¹ca do tworzenia wektora z listy argumentów przekazanych w konstruktorze.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class NARZEDZIA_API MakeVector
	{
	public:
		/**
		* \brief Konstruktor obiektu.
		*
		* Metoda konstruuj¹ca obiekt.
		* \param[in] tail - Lista obiektów.
		* \tparam V - Typ obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template< class... V >
		MakeVector(V&... tail){
			step(a, tail...);
		}

		/**
		* \brief Konstruktor przenosz¹cy.
		*
		* Konstruktor przenosz¹cy.
		* \param[inout] d - Obiekt Ÿród³owy.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		MakeVector(MakeVector&& d)
			: a(d.a)
		{
		}

		/**
		* \brief Metoda zwracaj¹ca stworzon¹ tablice.
		*
		* Metoda zwracaj¹ca stworzon¹ w konstruktorze tablice opisów obiektów.
		* \return Wektor obiektów.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		const std::vector< std::string >& get() {
			return a;
		}

	private:
		std::vector< std::string > a; /// Wektor z opisem obiektów przekazanych w konstruktorze.

		/**
		* \brief Metoda pojedyñczego kroku dodaj¹ca obiekt do wektora.
		*
		* Metoda dodaje opis obiektu do wektora. Wywo³uje koleny krok tworzenia opisu listy obiektów.
		* \param[inout] v - Wektor z opisem obiektów.
		* \param[in] c - Obiekt.
		* \param[in] tail - lista obiektów.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template< class T, class... V >
		void step(std::vector< std::string >& v, T &c, V&... tail){
			v.push_back(c);
			step(v, tail...);
		}

		/**
		* \brief Metoda pojedyñczego kroku dodaj¹ca obiekt do wektora.
		*
		* Metoda dodaje opis obiektu do wektora. Metoda koñczy tworzenie wektora z opisami obiektów.
		* \param[inout] v - Wektor z opisem obiektów.
		* \param[in] c - Obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template< class T >
		void step(std::vector< std::string >& v, T &c){
			v.push_back(c);
		}

	};
};
