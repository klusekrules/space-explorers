#pragma once
#include <functional>

template< typename T>
class RefGen {
	typedef std::function< void(const T&) > ConstRefCallback;
	typedef std::function< void(T&) > RefCallback;
	std::ref<T> ref_;

public:
	RefGen(T ref) : ref_(ref) {}
	RefGen(const RefGen&) = delete;
	RefGen(RefGen&& m) : ref_(std::move(m.ref_)) {}
	RefGen& operator=(const RefGen&) = delete;
	RefGen& operator=(RefGen&& m) {
		ref_ = std::move(m.ref_);
		return *this;
	}
	
};