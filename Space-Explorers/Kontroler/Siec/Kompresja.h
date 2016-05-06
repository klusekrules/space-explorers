#pragma once
#include <stdio.h>
#include <string>

namespace SpEx {
	class Komperesja {
	public:
		Komperesja(FILE*);
		Komperesja(std::string*);
		~Komperesja();
	private:
		int kompresja();
		int kompresja_mem_impl();
		int kompresja_file_impl();
		int dekompresja();
		int dekompresja_mem_impl();
		int dekompresja_file_impl();
		std::string* dane_ = nullptr;
		FILE* plik_ = nullptr;
	};
}