#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )

#include <sstream>
#include "Logger\LoggerInterface.h"

namespace STyp{

	/**
	* \brief Klasa bazowa dla podstawowych typów atrybutów.
	*
	* Klasa bazowa z uniwersalnym interfejsem dla u³atwienia zmiany typów podstawowych w grze
	* oraz dla ujednolicenia interfejsu.
	* \author Daniel Wojdak
	* \version 1
	* \date 10-07-2013
	*/
	template< typename T >
	class PodstawowyInterfejs :
		virtual public SLog::LoggerInterface
	{
	public:

		typedef T nazwa_typu;

	protected:
		nazwa_typu wartosc_;

	public:
		PodstawowyInterfejs() = default;

		virtual ~PodstawowyInterfejs() = default;

		PodstawowyInterfejs(const PodstawowyInterfejs&) = default;

		PodstawowyInterfejs(PodstawowyInterfejs&&) = default;

		PodstawowyInterfejs& operator=(const PodstawowyInterfejs&) = default;

		PodstawowyInterfejs& operator=(PodstawowyInterfejs&&) = default;

		PodstawowyInterfejs(const nazwa_typu& wartosc) : wartosc_(wartosc) {}

		nazwa_typu operator()() const { return wartosc_; }

		void operator()(const nazwa_typu& wartosc){ wartosc_ = wartosc; }

		std::string napis() const override{
			std::stringstream str;
			str << wartosc_;
			return std::move(str.str());
		}
	};





	template < typename T >
	class TypObliczeniowy :
		public PodstawowyInterfejs < T >
	{
	public:
		TypObliczeniowy() = default;

		virtual ~TypObliczeniowy() = default;

		TypObliczeniowy(const TypObliczeniowy&) = default;

		TypObliczeniowy(TypObliczeniowy&&) = default;

		TypObliczeniowy& operator=(const TypObliczeniowy&) = default;

		TypObliczeniowy& operator=(TypObliczeniowy&&) = default;

		TypObliczeniowy(const nazwa_typu& wartosc) : PodstawowyInterfejs(wartosc) {}

		bool operator==(const TypObliczeniowy& wartosc)const{ return wartosc_ == wartosc.wartosc_; }

		bool operator!=(const TypObliczeniowy& wartosc)const{ return wartosc_ != wartosc.wartosc_; }

		bool operator<(const TypObliczeniowy& wartosc)const{ return wartosc_ < wartosc.wartosc_; }

		bool operator>(const TypObliczeniowy& wartosc)const{ return wartosc_ > wartosc.wartosc_; }

		bool operator<=(const TypObliczeniowy& wartosc)const{ return wartosc_ <= wartosc.wartosc_; }

		bool operator>=(const TypObliczeniowy& wartosc)const{ return wartosc_ >= wartosc.wartosc_; }

		TypObliczeniowy& operator-=(const TypObliczeniowy& wartosc){ wartosc_ -= wartosc.wartosc_; return *this; }

		TypObliczeniowy& operator+=(const TypObliczeniowy& wartosc){ wartosc_ += wartosc.wartosc_; return *this; }

		TypObliczeniowy operator-(const TypObliczeniowy& wartosc)const{ return wartosc_ - wartosc.wartosc_; }

		TypObliczeniowy operator-()const{ return -wartosc_; }

		TypObliczeniowy operator+(const TypObliczeniowy& wartosc)const{ return wartosc_ + wartosc.wartosc_; }

		TypObliczeniowy& operator*=(const TypObliczeniowy& wartosc){ wartosc_ *= wartosc.wartosc_; return *this; }

		TypObliczeniowy& operator/=(const TypObliczeniowy& wartosc){ wartosc_ /= wartosc.wartosc_; return *this; }

		TypObliczeniowy operator*(const TypObliczeniowy& wartosc)const{ return wartosc_ * wartosc.wartosc_; }

		TypObliczeniowy operator/(const TypObliczeniowy& wartosc)const{ return wartosc_ / wartosc.wartosc_; }

		TypObliczeniowy& operator++(){ ++wartosc_;	return (*this); }

		TypObliczeniowy operator++(int){ TypObliczeniowy t(*this); ++wartosc_; return t; }

	};





	template < typename T >
	class TypBoolowski :
		public PodstawowyInterfejs < T >
	{
	public:
		TypBoolowski() = default;

		virtual ~TypBoolowski() = default;

		TypBoolowski(const TypBoolowski&) = default;

		TypBoolowski(TypBoolowski&&) = default;

		TypBoolowski& operator=(const TypBoolowski&) = default;

		TypBoolowski& operator=(TypBoolowski&&) = default;
		
		TypBoolowski(const nazwa_typu& wartosc) : PodstawowyInterfejs(wartosc) {}

		bool operator==(const TypBoolowski& wartosc)const{ return wartosc_ == wartosc.wartosc_; }

		bool operator!=(const TypBoolowski& wartosc)const{ return wartosc_ != wartosc.wartosc_; }

		bool operator<(const TypBoolowski& wartosc)const{ return wartosc_ < wartosc.wartosc_; }

		bool operator>(const TypBoolowski& wartosc)const{ return wartosc_ > wartosc.wartosc_; }

		bool operator<=(const TypBoolowski& wartosc)const{ return wartosc_ <= wartosc.wartosc_; }

		bool operator>=(const TypBoolowski& wartosc)const{ return wartosc_ >= wartosc.wartosc_; }

	};





	template < typename T >
	class TypTekstowy :
		public PodstawowyInterfejs < T >
	{
	public:
		TypTekstowy() = default;

		virtual ~TypTekstowy() = default;

		TypTekstowy(const TypTekstowy&) = default;

		TypTekstowy(TypTekstowy&&) = default;

		TypTekstowy& operator=(const TypTekstowy&) = default;

		TypTekstowy& operator=(TypTekstowy&&) = default;

		TypTekstowy(const nazwa_typu& wartosc) : PodstawowyInterfejs(wartosc) {}

		bool operator==(const TypTekstowy& wartosc)const{ return wartosc_ == wartosc.wartosc_; }

		bool operator!=(const TypTekstowy& wartosc)const{ return wartosc_ != wartosc.wartosc_; }

		bool operator<(const TypTekstowy& wartosc)const{ return wartosc_ < wartosc.wartosc_; }

		bool operator>(const TypTekstowy& wartosc)const{ return wartosc_ > wartosc.wartosc_; }

		bool operator<=(const TypTekstowy& wartosc)const{ return wartosc_ <= wartosc.wartosc_; }

		bool operator>=(const TypTekstowy& wartosc)const{ return wartosc_ >= wartosc.wartosc_; }

		TypTekstowy& operator+=(const TypTekstowy& wartosc){ wartosc_ += wartosc.wartosc_; return *this; }

		TypTekstowy operator+(const TypTekstowy& wartosc)const{ return wartosc_ + wartosc.wartosc_; }

		bool isEmpty() const{ return wartosc_.empty(); }

		std::string napis() const override{ return std::move(dodajCudzyslow()); }

	private:
		nazwa_typu dodajCudzyslow() const {
			nazwa_typu s("\"");
			s += wartosc_ + "\"";
			return std::move(s);
		}

	};

	namespace SPG{
		typedef bool			Bool;
		typedef int				Identyfikator;
		typedef unsigned int	Poziom;
		typedef long long		Klucz; // sizeof(Identyfikator) + sizeof(Poziom)
		typedef float			Fluktuacja;
		typedef std::string		Tekst;
		typedef long double		IloscJednostek;
		typedef double			Objetosc;
		typedef double			Masa;
		typedef double			Dystans;
		typedef double			Temperatura;
		typedef double			Predkosc;
		typedef double			Powierzchnia;
		typedef double			Parametr;
		typedef long double		Czas;
		typedef double			Obrazenia;
		typedef double			ZuzyciePaliwa;
		typedef double			Moc;
		typedef long double		Wartosc; // Wartosc wykorzystywana w projekcie zmiana.
	}

	typedef class TypBoolowski<SPG::Bool> Bool;
	typedef class TypObliczeniowy<SPG::Czas> Czas;
	typedef class TypObliczeniowy<SPG::Dystans> Dystans;
	typedef class TypObliczeniowy<SPG::Fluktuacja> Fluktuacja;
	typedef class TypBoolowski<SPG::Identyfikator> Identyfikator;	
	typedef class TypObliczeniowy<SPG::IloscJednostek> Ilosc;
	typedef class TypBoolowski<SPG::Klucz> Klucz;
	typedef class TypObliczeniowy<SPG::Masa> Masa;
	typedef class TypObliczeniowy<SPG::Moc> Moc;
	typedef class TypObliczeniowy<SPG::Objetosc> Objetosc;
	typedef class TypObliczeniowy<SPG::Obrazenia> Obrazenia;
	typedef class TypObliczeniowy<SPG::Parametr> Parametr;
	typedef class TypObliczeniowy<SPG::Powierzchnia> Powierzchnia;
	typedef class TypObliczeniowy<SPG::Poziom> Poziom;
	typedef class TypObliczeniowy<SPG::Predkosc> Predkosc;
	typedef class TypTekstowy<SPG::Tekst> Tekst;
	typedef class TypObliczeniowy<SPG::Temperatura> Temperatura;
	typedef class TypObliczeniowy<SPG::ZuzyciePaliwa> ZuzyciePaliwa;
	typedef class TypObliczeniowy<SPG::Wartosc> Wartosc;
}