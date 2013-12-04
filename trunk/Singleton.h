#pragma once
#include "NonCopyable.h"
#include "NonMoveable.h"

namespace se{
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
