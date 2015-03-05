#pragma once
#include "Zmiana\ZmianaFabryka.h"
#include "Skrypt.h"
#include "Parser\json\json.h"
#include "Licznik.h"

namespace SpEx{
	class MetodaRPC;
	class Klient;
	/**
	* \brief Klasa przechowuj¹ca obiekty fabryk.
	*
	* Klasa przechowuje obiekty fabryk.
	* \author Daniel Wojdak
	* \version 4
	* \date 26-11-2014
	*/
	class Fabrykator :
		public virtual SLog::LoggerInterface
	{
	public:
		typedef STyp::Tekst IdentyfikatorSkryptu; /// Typ skryptu.
		typedef std::shared_ptr<Skrypt>(*KreatorSkryptu)(XmlBO::ElementWezla wezel); /// Nag³ówek metody tworz¹cej skrypt.

		typedef STyp::Tekst IdentyfikatorMetoryRPC;
		typedef std::shared_ptr<MetodaRPC>(*KreatorMetodyRPC)(const Json::Value &, Klient&);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		Fabrykator() = default;

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Fabrykator() = default;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych w wêŸle przez parametr.
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] identyfikator - Identyfikator typu skryptu.
		* \param[in] wezel - Wêze³ opisuj¹cy skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(const IdentyfikatorSkryptu& identyfikator, XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] plik - Adres pliku, który ma byæ wczytany jako skrypt.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		std::shared_ptr<Skrypt> TworzSkrypt(const std::string& plik) const;

		/**
		* \brief Metoda tworz¹ca zmianê.
		*
		* Metoda tworzy obiekt zmiany na podstawie danych przekazanych przez parametry.
		* \param[in] wezel - Wêze³ opisuj¹cy zmianê.
		* \return Zwracany jest wskaŸnik do skryptu, je¿eli operacja siê powiedzie lub nullptr w przypadku b³êdu.
		* \throw Metoda generuje wyj¹tek, je¿eli wêze³ nie zawiera odpowiedniego atrybutu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda pobieraj¹ca fabryke zmian.
		*
		* Meoda pobiera raferencje do fabryki zmian.
		* \return Referencja do fabryki zmian.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		SZmi::ZmianaFabryka& pobierzFabrykeZmian();

		std::shared_ptr<MetodaRPC> TworzMetodeRPC(const Json::Value &, Klient&) const;
		
		template <class T_>
		inline std::shared_ptr<T_> TworzMetodeRPC(Klient& klient){
			auto ptr = std::make_shared<T_>(klient);
			ptr->nazwa_ = typename T_::NazwaTypu_;
			ptr->id_unikalne_ = std::to_string(static_cast<unsigned long long>(identyfikatorZadania_()()));
			if (!ptr->inicjuj()){
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê inicjalizacja metody: " + typename T_::NazwaTypu_);
				}
				return nullptr;
			}
			return ptr;
		}

		template <class T_>
		inline bool RejestrujMetodeRPC(){
			return Rejestruj<T_>(metodRpcCallbacks_, &Fabrykator::tworz<T_>);
		}

		template <class T_>
		inline bool RejestrujSkrypt(){
			return Rejestruj<T_>(callbacks_, &typename T_::Tworz);
		}

		/**
		* Funkcja s³u¿¹ca do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-11-2014
		*/
		std::string napis() const override;

	private:
		typedef std::map<IdentyfikatorSkryptu, KreatorSkryptu> ScriptCallbacks; /// Typ kontenera przechowuj¹cego metody tworz¹ce instancje skryptów.

		typedef std::map<IdentyfikatorMetoryRPC, KreatorMetodyRPC> TablicaKreatorowMetodRPC;
		
		template <class T_, class K_, class F_>
		inline bool Rejestruj(K_ & kontener, F_ funkcja){
			if (typename T_::NazwaTypu_.empty() || kontener.find(typename T_::NazwaTypu_) != kontener.end())
				return false;
			kontener[typename T_::NazwaTypu_] = funkcja;
			return true;
		}

		template <class T_>
		static std::shared_ptr<SpEx::MetodaRPC> tworz(const Json::Value & metoda, Klient& klient){
			auto ptr = std::make_shared<T_>(klient);			
			if ( (*ptr) << metoda && ptr->inicjuj(metoda)){
				return std::move(ptr);
			}
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê deserializacja metody: " + typename T_::NazwaTypu_);
			}
			return nullptr;
		}

		TablicaKreatorowMetodRPC metodRpcCallbacks_;

		ScriptCallbacks callbacks_; /// Kontener przechowuj¹cy metody tworz¹ce instancje skryptów.

		SZmi::ZmianaFabryka fabrykaZmian_; /// Instancja fabryki zmian.

		mutable Licznik identyfikatorZadania_;
	};
};
