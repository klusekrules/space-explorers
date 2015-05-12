#pragma once
#include <functional>
#include <map>
#include <list>

template < typename T , typename ... A>
class CallbackSystemInterfejs{
public:
	typedef std::function < void(A ...) > Callback;
	~CallbackSystemInterfejs() = default;
	void dodajCallback(Callback funkcja, T wyzwalacz){
		callbacks_[wyzwalacz].emplace_back(funkcja);
	}
protected:
	CallbackSystemInterfejs() = default;

	void wywolaj(T wyzwalacz, A ... args) const{
		auto iter = callbacks_.find(wyzwalacz);
		if (iter != callbacks_.end()){
			for (auto & f : iter->second){
				f(args...);
			}
		}
	}
private:
	std::map< T, std::list<Callback> > callbacks_;		
};