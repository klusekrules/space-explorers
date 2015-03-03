#pragma once
#include "ZarzadcaZasobow.h"
#include "SHA3.h"
#define TYP_ZASOBU_SUMA_KONTROLNA_PLIKU "fileSHA3"

namespace SpEx{
	class SumaKontrolnaPliku
		: public Zasob
	{
	public:
		friend class std::_Ref_count_obj<SumaKontrolnaPliku>;
		typedef std::shared_ptr<SumaKontrolnaPliku> SharedPtr; /// Silny wskaŸnik na klasê.
		typedef std::weak_ptr<SumaKontrolnaPliku> WeakPtr; /// S³aby wskaŸnik na klasê.

		static bool Rejestruj(ZarzadcaZasobow &fabryka);

		
		bool inicjalizuj() override;

		virtual ~SumaKontrolnaPliku() = default;

		inline const std::string& pobierzAdresPliku() const{
			return plik_;
		}

		inline const SHA3& pobierzSumeKontrolna() const{
			return sumaKontrolna_;
		}

	private:
		SumaKontrolnaPliku(const std::string& plik);

		static Zasob::SharedPtr Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache);
		std::string plik_;
		SHA3 sumaKontrolna_;
	};
}
