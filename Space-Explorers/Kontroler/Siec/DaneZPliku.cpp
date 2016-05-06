#include "DaneZPliku.h"
#include <winerror.h>

SpEx::DaneZPliku::DaneZPliku(const std::string & adresPliku)
	: plik_ (nullptr)
{
	if (!adresPliku.empty()) {

	}
}

SpEx::DaneZPliku::~DaneZPliku(){
	if (plik_ != nullptr)
		fclose(plik_);
}

unsigned __int64 SpEx::DaneZPliku::rozmiar() const{
	return rozmiar_;
}

int SpEx::DaneZPliku::wez(const char * dane, unsigned __int64 rozmiar){
	if (plik_ == nullptr)
		return ERROR_FILE_NOT_FOUND;

	int offset = 0;
	do {
		size_t written = fwrite(&dane[offset], sizeof(char), rozmiar - offset, plik_);
		if (written == 0) {
			return ferror(plik_);
		}
		offset += written;
		rozmiar_ += written;
	} while (offset < rozmiar);
	return ERROR_SUCCESS;
}

int SpEx::DaneZPliku::daj(const char ** dane, unsigned __int64 & rozmiar){
	if (plik_ == nullptr)
		return ERROR_FILE_NOT_FOUND;

	size_t num;
	if (rozmiar != 0) {
		num = fread(&dane, 1, rozmiar, plik_);
	} else {
		num = fread(buffor_, 1, ROZMIAR_BUFFORA, plik_);
	}

	if (num==0) {
		return ferror(plik_);
	}

	rozmiar = num;

	return ERROR_SUCCESS;
}
