#pragma once
#include <vector>
#include <string>
namespace SpEx{
	class MakeVector
	{
	public:
		template< class... V >
		MakeVector(V&... tail){
			step(a, tail...);
		}

		MakeVector(MakeVector&& d)
			: a(d.a)
		{
		}

		const std::vector< std::string >& get() {
			return a;
		}
	private:
		std::vector< std::string > a;

		template< class T, class... V >
		void step(std::vector< std::string >& v, T &c, V&... tail){
			v.push_back(c);
			step(v, tail...);
		}

		template< class T >
		void step(std::vector< std::string >& v, T &c){
			v.push_back(c);
		}

	};
};
