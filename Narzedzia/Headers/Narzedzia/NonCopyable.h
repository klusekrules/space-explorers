#pragma once
namespace se{
	/**
	* \brief Klasa blokuj¹ca kopiowanie.
	*
	* Klasa blokuje u¿ycie domyœlnych konstruktorów kopiuj¹cych.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-06-2014
	*/
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		virtual ~NonCopyable() = default;
		NonCopyable& operator=(const NonCopyable&) = delete;
		NonCopyable(const NonCopyable&) = delete;
	};
}
