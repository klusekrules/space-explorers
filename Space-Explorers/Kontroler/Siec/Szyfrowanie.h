#pragma once
#include <stdio.h>
#include <string>
#include "Algorytmy\SHA3.h"

namespace SpEx {
	class Szyfrowanie {
	public:
		Szyfrowanie(const std::string &, FILE*,FILE*);
		Szyfrowanie(const std::string &,std::string &);
		~Szyfrowanie() = default;
		void ustawKlucz();
		int szyfrowanie();
		int deszyfrowanie();
	private:
		int szyfrowanie_mem_impl();
		int szyfrowanie_file_impl();
		int deszyfrowanie_mem_impl();
		int deszyfrowanie_file_impl();
		std::string* dane_ = nullptr;
		SHA3 skrotKlucza_;
		FILE* plikin_ = nullptr;
		FILE* plikout_ = nullptr;
	};
}
