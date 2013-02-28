#pragma once
#include <vector>
#include <string>

using namespace std;

class MakeVector
{
public:
	template< class... V >
	MakeVector( V&... tail ){
		step(a, tail... );
	}

	MakeVector( MakeVector&& d )
		: a(d.a)
	{
	}

	vector< string >& get() {
		return a;
	}
private:	
	vector< string > a;
	template< class T, class... V >
	void step( vector< string >& v, T &c ,V&... tail ){
		v.push_back(c);
		step(v, tail... );
	}

	template< class T >
	void step( vector< string >& v, T &c ){
		v.push_back(c);
	}

};

