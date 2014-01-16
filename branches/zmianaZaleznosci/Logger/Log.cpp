#include "stdafx.h"
#include "Log.h"

void Log::wyswietl( TypLogow typ, const std::string& p ) const{
	for( auto f : outstream)
		f(typ,p);
}

void Log::dodajGniazdoWyjsciowe( const Strumien &t ){
	outstream.push_back(t);
}

void Log::ustawFormatCzasu( FormatCzasu format ){
	switch (format)
	{
	case FormatCzasu::Data: formatCzasu_="%Y-%m-%d";
		break;
	case FormatCzasu::Czas: formatCzasu_="%H:%M:%S";
		break;
	case FormatCzasu::DataCzas: formatCzasu_="%Y-%m-%d %H:%M:%S";
		break;
	default:
		break;
	}
}

Log& Log::pobierzInstancje(){
	static Log log;
	return log;
}

bool Log::czyLogiOdblokowane(TypLogow typ)const{
	return poziomy_[typ];
}

void Log::odblokujLogi(TypLogow typ){
	poziomy_[typ] = true;
}

void Log::zablokujLogi(TypLogow typ){
	poziomy_[typ] = false;
}

void Log::loguj( TypLogow typ, const std::string& komunikat ) const{
	if(poziomy_[TypLogow::All] && poziomy_[typ]){
		wyswietl( typ, pobierzDateCzas() + " [INFO] " + komunikat + "\n" );
	}
}

void Log::loguj( TypLogow typ, const LoggerInterface& komunikat ) const{
	if(poziomy_[TypLogow::All] && poziomy_[typ]){
		wyswietl( typ, pobierzDateCzas() + " [INFO] " + komunikat.napis() + "\n" );
	}
}

std::string&& Log::pobierzDateCzas() const{
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration dtn = t1.time_since_epoch();
	time_t pSekundy = dtn.count() * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
	struct tm timeinfo;
	localtime_s(&timeinfo,&pSekundy);
	short unsigned int pMilisekundy = static_cast<long long>( dtn.count() * ( static_cast<long double>(std::chrono::steady_clock::period::num) / static_cast<long double>(std::chrono::steady_clock::period::den) ) * 1000 ) % 1000;
	char s[20];
	strftime(s,20,formatCzasu_.c_str(),&timeinfo);
	std::stringstream str;
	str << s << "." << std::setw (3) << std::setfill ('0') << pMilisekundy;
	return std::move(str.str());
}
