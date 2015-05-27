#pragma once
#include "NarzedziaSymbol.h"
#include <functional>
#include <map>
#include <list>
#include <mutex>

template < typename T , typename ... A>
class CallbackSystemInterfejs{
public:
	typedef std::function < void(A ...) > Callback;
	typedef std::pair< T, typename std::list<Callback>::iterator > Identyfikator;
	~CallbackSystemInterfejs() = default;

	Identyfikator dodajCallback(Callback funkcja, T wyzwalacz){
		std::lock_guard<std::mutex> blokada(mux_);
		Identyfikator para;
		para.first = wyzwalacz;
		callbacks_[wyzwalacz].emplace_back(funkcja);
		para.second = std::prev(callbacks_[wyzwalacz].end());
		return std::move(para);
	}

	void usunCallback(Identyfikator id){
		std::lock_guard<std::mutex> blokada(mux_);
		callbacks_[id.first].erase(id.second);
	}

protected:
	CallbackSystemInterfejs() = default;

	void wywolaj(T wyzwalacz, A ... args) const{
		std::lock_guard<std::mutex> blokada(mux_);
		auto iter = callbacks_.find(wyzwalacz);
		if (iter != callbacks_.end()){
			for (auto & f : iter->second){
				f(args...);
			}
		}
	}
private:
	mutable std::mutex mux_;
	std::map< T, std::list<Callback> > callbacks_;		
};