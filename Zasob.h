#pragma once
#include <memory>
#include "TypyProste\TypyProste.h"
#include "NonCopyable.h"

namespace SpEx{

	/**
	* \brief Klasa zawieraj�ca interfejs zasobu.
	*
	* Klasa zawiera podstawowy interfejs dla zasobu.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-08-2014
	*/
	class Zasob
		: se::NonCopyable
	{
		friend class ZarzadcaZasobow;
	public:
		typedef std::shared_ptr<Zasob> SharedPtr; /// Silny wska�nik na zas�b.
		typedef std::weak_ptr<Zasob> WeakPtr; /// S�aby wska�nik na zas�b.

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		Zasob() = default;

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Zasob() = default;

		/**
		* \brief Metoda zwracaj�ca identyfikator zasobu.
		*
		* Metoda Zwraca identyfikator zasobu.
		* \return Identyfikator zasobu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		inline const STyp::Identyfikator& pobierzIdentyfikator() const{
			return identyfikator_;
		}

		/**
		* \brief Metoda inicjalizuj�ca zas�b.
		*
		* Metoda inicjalizuje zas�b.
		* \return Zwracana jest warto�� true, je�eli uda si� zainicjalizowa� zas�b poprawnie. Zwracana jest warto�� false, w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		virtual bool inicjalizuj() = 0;

	private:
		STyp::Identyfikator identyfikator_; /// Identyfikator zasobu.
	};
};
