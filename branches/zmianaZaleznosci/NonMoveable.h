#pragma once
namespace se{
	class NonMoveable
	{
	public:
		NonMoveable(void){}
	private:
		NonMoveable& operator=( NonMoveable&& ){}
		NonMoveable( NonMoveable&& ){}
	};
}
