#pragma once
#include "Zmiana\ZmianaFabryka.h"
#include "Kontroler\MaszynaStanow\Skrypty\Skrypt.h"
#include "Parser\json\json.h"
#include "Model\Licznik.h"

namespace SpEx{
	class MetodaRPC;
	class Klient;
	/**
	* \brief Klasa przechowuj�ca obiekty fabryk.
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
		typedef std::shared_ptr<Skrypt>(*KreatorSkryptu)(XmlBO::ElementWezla wezel); /// Nag��wek metody tworz�cej skrypt.

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
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Fabrykator() = default;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych w w�le przez parametr.
		* \param[in] wezel - W�ze� opisuj�cy skrypt.
		* \return Zwracany jest wska�nik do skryptu, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> tworzSkrypt(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] identyfikator - Identyfikator typu skryptu.
		* \param[in] wezel - W�ze� opisuj�cy skrypt.
		* \return Zwracany jest wska�nik do skryptu, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<Skrypt> tworzSkrypt(const IdentyfikatorSkryptu& identyfikator, XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda tworzy skrypt.
		*
		* Metoda tworzy obiekt skryptu na podstawie danych przekazanych przez parametry.
		* \param[in] plik - Adres pliku, kt�ry ma by� wczytany jako skrypt.
		* \return Zwracany jest wska�nik do skryptu, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		std::shared_ptr<Skrypt> tworzSkrypt(const std::string& plik) const;

		/**
		* \brief Metoda tworz�ca zmian�.
		*
		* Metoda tworzy obiekt zmiany na podstawie danych przekazanych przez parametry.
		* \param[in] wezel - W�ze� opisuj�cy zmian�.
		* \return Zwracany jest wska�nik do skryptu, je�eli operacja si� powiedzie lub nullptr w przypadku b��du.
		* \throw Metoda generuje wyj�tek, je�eli w�ze� nie zawiera odpowiedniego atrybutu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		std::shared_ptr<SZmi::ZmianaInterfejs> tworzZmiane(XmlBO::ElementWezla wezel) const;

		/**
		* \brief Metoda pobieraj�ca fabryke zmian.
		*
		* Meoda pobiera raferencje do fabryki zmian.
		* \return Referencja do fabryki zmian.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		SZmi::ZmianaFabryka& pobierzFabrykeZmian();

		std::shared_ptr<MetodaRPC> tworzMetodeRPC(const Json::Value &, Klient&) const;
		
		template <class T_>
		inline std::shared_ptr<T_> tworzMetodeRPC(Klient& klient){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "MetodaRPC -> " + typename T_::NazwaTypu_);
			}
			auto ptr = std::make_shared<T_>(klient);			
			ptr->nazwa_ = typename T_::NazwaTypu_;
			ptr->id_unikalne_ = std::to_string(static_cast<unsigned long long>(identyfikatorZadania_()()));
			if (!ptr->inicjuj()){
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod�a si� inicjalizacja metody: " + typename T_::NazwaTypu_);
				}
				return nullptr;
			}
			return ptr;
		}

		template <class T_>
		inline bool rejestrujMetodeRPC(){
			return rejestruj<T_>(metodRpcCallbacks_, &Fabrykator::tworz<T_>);
		}

		template <class T_>
		inline bool rejestrujSkrypt(){
			return rejestruj<T_>(callbacks_, &typename T_::Tworz);
		}

		/**
		* Funkcja s�u��ca do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 26-11-2014
		*/
		std::string napis() const override;

	private:
		typedef std::map<IdentyfikatorSkryptu, KreatorSkryptu> ScriptCallbacks; /// Typ kontenera przechowuj�cego metody tworz�ce instancje skrypt�w.

		typedef std::map<IdentyfikatorMetoryRPC, KreatorMetodyRPC> TablicaKreatorowMetodRPC;
		
		template <class T_, class K_, class F_>
		inline bool rejestruj(K_ & kontener, F_ funkcja){
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
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod�a si� deserializacja metody: " + typename T_::NazwaTypu_);
			}
			return nullptr;
		}

		TablicaKreatorowMetodRPC metodRpcCallbacks_;

		ScriptCallbacks callbacks_; /// Kontener przechowuj�cy metody tworz�ce instancje skrypt�w.

		SZmi::ZmianaFabryka fabrykaZmian_; /// Instancja fabryki zmian.

		mutable Licznik identyfikatorZadania_;
	};
};
