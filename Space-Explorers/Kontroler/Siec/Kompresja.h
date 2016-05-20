#pragma once
#include <stdio.h>
#include <string>

namespace SpEx {
	class Kompresja {
	public:
		Kompresja(FILE*,FILE*);
		Kompresja(const std::string &, std::string &);
		int kompresja();
		int dekompresja();
		~Kompresja() = default;
	private:
		int kompresja_mem_impl();
		int kompresja_file_impl();
		int dekompresja_mem_impl();
		int dekompresja_file_impl();
		const std::string* danein_;
		std::string* daneout_;
		FILE* plikin_ = nullptr;
		FILE* plikout_ = nullptr;
	};
}