#pragma once
#include "NonCopyable.h"
#include "NonMoveable.h"

namespace se{
	/**
	* \brief Szablon klasy wzorca singleton.
	*
	* Szablon klasy implementuj¹cej wzorzec singleton.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-06-2014
	*/
	template <class T>
	class Singleton : NonCopyable, NonMoveable
	{
	public:		
		static T& pobierzInstancje(){
			static T obiekt;
			return obiekt;
		}
	};

}
