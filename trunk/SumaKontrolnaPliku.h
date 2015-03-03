#pragma once
#include "ZarzadcaZasobow.h"
#include "SHA3.h"
#define TYP_ZASOBU_SUMA_KONTROLNA_PLIKU "fileSHA3"

namespace SpEx{
	class SumaKontrolnaPliku
		: public Zasob
	{
	public:
		typedef std::shared_ptr<SumaKontrolnaPliku> SharedPtr; /// Silny wska�nik na klas�.
		typedef std::weak_ptr<SumaKontrolnaPliku> WeakPtr; /// S�aby wska�nik na klas�.

		static bool Rejestruj(ZarzadcaZasobow &fabryka);

		SumaKontrolnaPliku(const std::string& plik);

		bool inicjalizuj() override;

		virtual ~SumaKontrolnaPliku() = default;

		inline const std::string& pobierzAdresPliku() const{
			return plik_;
		}

		inline const SHA3& pobierzSumeKontrolna() const{
			return sumaKontrolna_;
		}

	private:
		static Zasob::SharedPtr Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache);
		std::string plik_;
		SHA3 sumaKontrolna_;
	};
}
