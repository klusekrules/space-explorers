#pragma once
namespace se{
	/**
	* \brief Klasa blokująca przenoszenie.
	*
	* Klasa  blokuje użycie domyślnych konstruktorów prznoszących.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-06-2014
	*/
	class NonMoveable
	{
	public:
		NonMoveable() = default;
		virtual ~NonMoveable() = default;
		NonMoveable& operator=(NonMoveable&&) = delete;
		NonMoveable(NonMoveable&&) = delete;
		NonMoveable& operator=(const NonMoveable&) = default;
		NonMoveable(const NonMoveable&) = default;
	};
}
