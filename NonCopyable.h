#pragma once
namespace se{
	class NonCopyable
	{
	public:
		NonCopyable(){}
	private:
		NonCopyable& operator=( const NonCopyable& ){}
		NonCopyable( const NonCopyable& ){}
	};
}
