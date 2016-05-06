#pragma once
#include <stdio.h>
#include <string>
#include "Algorytmy\SHA3.h"

namespace SpEx {
	class Szyfrowanie {
	public:
		Szyfrowanie(const std::string&,FILE*);
		Szyfrowanie(std::string*);
		~Szyfrowanie();
	private:
		int szyfrowanie();
		int szyfrowanie_mem_impl();
		int szyfrowanie_file_impl();
		int deszyfrowanie();
		int deszyfrowanie_mem_impl();
		int deszyfrowanie_file_impl();
		std::string* dane_ = nullptr;
		std::string klucz_;
		SHA3 skrotKlucza_;
		FILE* plik_ = nullptr;
	};
}
