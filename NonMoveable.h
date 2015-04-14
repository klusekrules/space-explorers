#pragma once
namespace se{
	/**
	* \brief Klasa blokuj¹ca przenoszenie.
	*
	* Klasa  blokuje u¿ycie domyœlnych konstruktorów prznosz¹cych.
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
