#pragma once
#include "Zmiana\ZmianaFabryka.h"
#include "Skrypt.h"
#include "Parser\json\json.h"
#include "Licznik.h"

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
		typedef bool(*RejestrujSkrypt)(Fabrykator& fabryka, SLog::Log& logger); /// Nag��wek metody rejestruj�cej skrypt w fabryce.

		typedef STyp::Tekst IdentyfikatorMetoryRPC;
		typedef std::shared_ptr<MetodaRPC>(*KreatorMetodyRPC)(const Json::Value &, Klient&);
		typedef bool(*RejestratorMetodyRPC)(Fabrykator& fabryka, SLog::Log& logger);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-07-2014
		*/
		Fabrykator();

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
		std::shared_ptr<Skrypt> TworzSkrypt(XmlBO::ElementWezla wezel) const;

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
		std::shared_ptr<Skrypt> TworzSkrypt(const IdentyfikatorSkryptu& identyfikator, XmlBO::ElementWezla wezel) const;

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
		std::shared_ptr<Skrypt> TworzSkrypt(const std::string& plik) const;

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
		std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla wezel) const;

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

		/**
		* \brief Metoda rejestruj�ca typ skryptu.
		*
		* Metoda zapisuje do kontenera metod� tworz�c� skrypt o podany typie.
		* \param[in] identyfikator - Identyfikator skryptu.
		* \param[in] funkcja - Metoda tworz�ca.
		* \return Zwracana jest warto�� true, je�eli uda si� zarejestrowa� metode lub false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool rejestracjaSkryptu(const IdentyfikatorSkryptu& identyfikator, KreatorSkryptu funkcja);
		
		std::shared_ptr<MetodaRPC> TworzMetodeRPC(const Json::Value &, Klient&) const;
		
		template <class T_>
		inline std::shared_ptr<T_> TworzMetodeRPC(Klient& klient){
			return std::dynamic_pointer_cast<T_>(TworzMetodeRPC(typename T_::NazwaTypu_, klient));
		}

		template <class T_>
		inline bool RejestrujMetodeRPC(){
			if (typename T_::NazwaTypu_.empty() || metodRpcCallbacks_.find(typename T_::NazwaTypu_) != metodRpcCallbacks_.end())
				return false;
			metodRpcCallbacks_[typename T_::NazwaTypu_] = typename T_::TworzObiekt;
			return true;
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

		std::shared_ptr<MetodaRPC> TworzMetodeRPC(const std::string &, Klient&) const;

		TablicaKreatorowMetodRPC metodRpcCallbacks_;

		ScriptCallbacks callbacks_; /// Kontener przechowuj�cy metody tworz�ce instancje skrypt�w.

		SZmi::ZmianaFabryka fabrykaZmian_; /// Instancja fabryki zmian.

		mutable Licznik identyfikatorZadania_;
	};
};
