#pragma once
namespace se{
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		virtual ~NonCopyable() = default;
		NonCopyable& operator=(const NonCopyable&) = delete;
		NonCopyable(const NonCopyable&) = delete;
		//NonCopyable& operator=(NonCopyable&&) = default;
		//NonCopyable(NonCopyable&&) = default;
	};
}
