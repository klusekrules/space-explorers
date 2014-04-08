#pragma once
#include <string>
#include "NonCopyable.h"

namespace SpEx{
	class Skrypt :
		public se::NonCopyable
	{
	public:
		Skrypt() = default;
		virtual bool zaladuj(const std::string&) = 0;
		virtual bool wykonaj(const std::string& = std::string()) = 0;
		virtual ~Skrypt() = default;
	};
}
