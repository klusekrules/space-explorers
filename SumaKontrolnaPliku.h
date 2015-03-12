#pragma once
#include "ZarzadcaZasobow.h"
#include "SHA3.h"

namespace SpEx{
	class SumaKontrolnaPliku
		: public Zasob,
		virtual public SLog::LoggerInterface
	{
	public:
		friend class std::_Ref_count_obj<SumaKontrolnaPliku>;
		static const std::string NazwaTypu_;
		typedef std::shared_ptr<SumaKontrolnaPliku> SharedPtr; /// Silny wskaŸnik na klasê.
		typedef std::weak_ptr<SumaKontrolnaPliku> WeakPtr; /// S³aby wskaŸnik na klasê.

		bool inicjalizuj() override;

		virtual ~SumaKontrolnaPliku() = default;

		inline const std::string& pobierzAdresPliku() const{
			return plik_;
		}

		inline const SHA3& pobierzSumeKontrolna() const{
			return sumaKontrolna_;
		}

		std::string napis() const override;

	private:
		SumaKontrolnaPliku(const std::string& plik);

		std::string plik_;
		SHA3 sumaKontrolna_;
	};
}
