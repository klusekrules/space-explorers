#include "MaszynaStanow.h"
#include "OknoGry.h"
#include "Aplikacja.h"
#include "FPSCounter.h"

namespace SpEx{
	MaszynaStanow::LuaStan::LuaStan()
		: poprawne_aktualny_(false), poprawne_nastepny_(false), poprawne_poprzedni_(false), poprawne_zdarzenie_(false)
	{
	}

	void MaszynaStanow::LuaStan::ustawNowyStanNastepny(const STyp::Identyfikator& id){
		if (komunikat_){
			nastepny_.idStanu_ = id();
			komunikat_->idNowegoStanu_ = std::make_shared<STyp::Identyfikator>(id);
		}
	}

	void MaszynaStanow::LuaStan::ustawNowyNumerNastepny(int numer){
		if (komunikat_){
			nastepny_.numer_ = numer;
		}
	}

	MaszynaStanow::MaszynaStanow()
		: watekGraficzny_(true), stan_(nullptr), stanNastepny_(nullptr), pulaWatkow_()
	{
		auto root = SpEx::Aplikacja::pobierzInstancje().pobierzZarzadce().pobierzWezelKonfiguracyjnyMaszynyStanow();
		XmlBO::WczytajAtrybut<SpEx::STACKTHROW>(root, ATRYBUT_XML_STAN_POCZATKOWY, idStanuPoczatkowy_);
		pulaWatkow_.ustawLiczbeWatkow(XmlBO::WczytajAtrybut<unsigned char>(root, ATRYBUT_XML_PULA_WATKOW, 4));
		XmlBO::ForEach<SpEx::STACKTHROW>(root, WEZEL_XML_STAN, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
			auto stan = std::make_shared<StanInfo>(element);
			wszystkieStany_.insert(std::make_pair(stan->pobierzIdentyfikator(), stan));
			return true;
		}));
		watekGraficzny_.zatrzymajPoInicjalizacji();
		watekGraficzny_.odblokuj();
	}

	bool MaszynaStanow::kolejkujOkno(int id){
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		auto ptr = watekGraficzny_.pobierzEkran(STyp::Identyfikator(id));
		if (ptr != nullptr){
			stosEkranow_.push_back(ptr);
			return true;
		}
		return false;
	}

	bool MaszynaStanow::zdejmijOkno(){
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		if (stosEkranow_.empty())
			return false;
		stosEkranow_.pop_back();
		return true;
	}
		
	void MaszynaStanow::wyczyscKolejkeOkien(){
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		stosEkranow_.clear();
	}

	Stan MaszynaStanow::pobierzStan(OknoGry::StosEkranow& stos) const{
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		stos = stosEkranow_;
		return stan_;
	}

	Stan MaszynaStanow::pobierzStan() const{
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		return stan_;
	}

	void MaszynaStanow::kolejkujZdarzenie(const Zdarzenie &komunikat){
		std::lock_guard<std::mutex> blokada(mutexZdarzen_);
		kolejkaZdarzen_.push_back(komunikat);
	}

	void MaszynaStanow::wstawZdarzenie(const Zdarzenie &komunikat){
		std::lock_guard<std::mutex> blokada(mutexZdarzen_);
		kolejkaZdarzen_.push_front(komunikat);
	}

	std::shared_ptr<StanInfo> MaszynaStanow::pobierzOpisStanu(const STyp::Identyfikator& id) const{
		auto iter = wszystkieStany_.find(id);
		if (iter != wszystkieStany_.end())
			return iter->second;
		else
			return nullptr;
	}

	bool MaszynaStanow::pobierzKomunikat(Zdarzenie &komunikat){
		std::lock_guard<std::mutex> blokada(mutexZdarzen_);
		if (kolejkaZdarzen_.empty())
			return false;
		komunikat = kolejkaZdarzen_.front();
		kolejkaZdarzen_.pop_front();
		return true;
	}

	void MaszynaStanow::start(){
		Stan s(wszystkieStany_.at(idStanuPoczatkowy_));
		ustawNastepnyStan(s);

		wlaczone = watekGraficzny_.czekajNaInicjalizacje();

		if (wlaczone)
			przejdzDoNastepnegoStanu();

		watekGraficzny_.uruchom();
#ifdef _FPS_COUNT
		FPSCounter fpsCounter;
#endif
		while (wlaczone)
		{
#ifdef _FPS_COUNT
			fpsCounter.nextFrame();
#endif
			luaStan_.poprawne_zdarzenie_ = false;
			obslugaZdarzenia();
			przejdzDoNastepnegoStanu();
			std::this_thread::yield(); 
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
#ifdef _FPS_COUNT
			if (fpsCounter.ready())
			{
				Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Error, std::string("MaszynaStanow: ") + std::to_string(fpsCounter.FPS()));
			}
#endif
		}
		
		watekGraficzny_.czekajNaZakonczenie();
		if (watekGraficzny_.blad()){
			throw watekGraficzny_.bladInfo();
		}
	}

	void MaszynaStanow::przejdzDoNastepnegoStanu(){
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		if (stanNastepny_.opisStanu()){
			stan_.akcjaWyjscia();

			luaStan_.ustawPoprzedni(stan_);
			stan_ = stanNastepny_;
			luaStan_.ustawAktualny(stan_);
			luaStan_.poprawne_nastepny_ = false;
			stan_.akcjaWejscia();
		}else{
			luaStan_.ustawPoprzedni(stan_);
			stan_.numer_ = stanNastepny_.numer_;
			luaStan_.ustawAktualny(stan_);
			luaStan_.poprawne_nastepny_ = false;
			stan_.akcjaWewnetrzna();
		}
	}

	void MaszynaStanow::obslugaZdarzenia(){

		Zdarzenie komunikat;
		Stan aktualny = pobierzStan();
		Stan nowy(aktualny,nullptr);

		if (pobierzKomunikat(komunikat)){
			if (aktualny == komunikat){
				auto opisStanu = aktualny.opisStanu();
				auto opisZdarzenia = opisStanu->pobierzZdarzenie(komunikat.idZdarzenia_);
				if (opisZdarzenia){
					auto idNowegoStanu = opisZdarzenia->pobierzStan();
					if (idNowegoStanu && *idNowegoStanu != aktualny.id_){
						auto nowyStan = pobierzOpisStanu(*idNowegoStanu);
						if (nowyStan){
							nowy = Stan(nowyStan);
						}
					}

					auto numerNowegoStanu = opisZdarzenia->pobierzNumer();
					if (numerNowegoStanu){
						nowy.numer_ = *numerNowegoStanu;
					}

					luaStan_.ustawNastepny(nowy);
					luaStan_.ustawZdarzenie(komunikat);
					luaStan_.komunikat_ = &komunikat;
					opisZdarzenia->wykonaj();
					luaStan_.komunikat_ = nullptr;

					if (komunikat.idNowegoStanu_){
						auto nowyStan = pobierzOpisStanu(*komunikat.idNowegoStanu_);
						if (nowyStan){
							nowy = Stan(nowyStan);
						}
					}
					nowy.numer_ = luaStan_.nastepny_.numer_;
				}
			}
		}

		ustawNastepnyStan(nowy);
	}

	OknoGry& MaszynaStanow::pobierzOknoGry(){
		return watekGraficzny_;
	}

	void MaszynaStanow::ustawNastepnyStan(Stan& stan){
		std::lock_guard<std::recursive_mutex> blokada(mutexStanu_);
		stanNastepny_ = stan;
		luaStan_.ustawNastepny(stanNastepny_);
	}

	void MaszynaStanow::inicjujZamykanie(){
		watekGraficzny_.zakmnij();
		wlaczone = false;
	}

	void MaszynaStanow::dodajZadanie(Zadanie& zadanie){
		pulaWatkow_.dodajZadanie(zadanie);
	}

	bool MaszynaStanow::LuaStan::pobierzZdarzenie(struct Zdarzenie_t& z){
		if (poprawne_zdarzenie_)
			z = zdarzenie_;
		return poprawne_zdarzenie_;
	}

	bool MaszynaStanow::LuaStan::pobierzPoprzedniStan(struct Stan_t& s){
		if (poprawne_poprzedni_)
			s = poprzedni_;
		return poprawne_poprzedni_;
	}

	bool MaszynaStanow::LuaStan::pobierzAktualnyStan(struct Stan_t& s){
		if (poprawne_aktualny_)
			s = aktualny_;
		return poprawne_aktualny_;
	}

	bool MaszynaStanow::LuaStan::pobierzNastepnyStan(struct Stan_t& s){
		if (poprawne_nastepny_)
			s = nastepny_;
		return poprawne_nastepny_;
	}

	void MaszynaStanow::LuaStan::ustawZdarzenie(const Zdarzenie& z){
		poprawne_zdarzenie_ = true;
		zdarzenie_.idStanu_ = z.idStanu_();
		zdarzenie_.numer_ = z.numer_;
		zdarzenie_.idZdarzenia_ = z.idZdarzenia_();
	}

	void MaszynaStanow::LuaStan::ustawPoprzedni(const Stan& z){
		poprawne_poprzedni_ = true;
		poprzedni_.idStanu_ = z.id_();
		poprzedni_.numer_ = z.numer_;
		//poprzedni_.dt_ = z.dt_.count();
	}

	void MaszynaStanow::LuaStan::ustawAktualny(const Stan& z){
		poprawne_aktualny_ = true;
		aktualny_.idStanu_ = z.id_();
		aktualny_.numer_ = z.numer_;
		//aktualny_.dt_ = z.dt_.count();
	}

	void MaszynaStanow::LuaStan::ustawNastepny(const Stan& z){
		poprawne_nastepny_ = true;
		nastepny_.idStanu_ = z.id_();
		nastepny_.numer_ = z.numer_;
		//nastepny_.dt_ = z.dt_.count();
	}
};
