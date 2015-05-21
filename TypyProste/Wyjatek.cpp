#include "Wyjatek.h"
#include "Logger\LoggerNazwaKlasy.h"
#include "Logger\Logger.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <iomanip>

namespace STyp{

	std::string pobierzSladStosu(){
		std::stringstream stackTrace;
#ifdef _DEBUG
		void *stack[150];
		unsigned short frames;
		SYMBOL_INFO *symbol;
		HANDLE hProcess;
		std::locale l("C");
		stackTrace.imbue(l);
		hProcess = GetCurrentProcess();
		SymInitialize(hProcess, nullptr, true);
		frames = CaptureStackBackTrace(0, 150, stack, nullptr);
		symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
		symbol->MaxNameLen = 255;
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		if (frames > 0){
			time_t rawtime;
			char buf[30];
			time(&rawtime);
			ctime_s(buf, 30, &rawtime);
			stackTrace << buf;
			// i = 1 - Pominiêcie wywo³ania funkcji getStackTrace
			// i = 0 - W³¹cznie do wyœwietlanego wyniku wywo³ania funkcji getStackTrace
			for (unsigned int i = 1; i < frames; i++)
			{
				SymFromAddr(hProcess, (DWORD_PTR)(stack[i]), 0, symbol);
				stackTrace << std::dec << (unsigned short)(frames - i - 1) << ": 0x" << std::setfill('0') << std::setw(8) << stack[i] << " " << (char*)(symbol->Name) << " = 0x" << std::setfill('0') << std::setw(8) << std::hex << symbol->Address << std::endl;
			}
		}
		free(symbol);
#endif
		return stackTrace.str();
	}

	Wyjatek::Wyjatek(const Tekst& plik, const Tekst& funkcja, const Ilosc& linia, const Tekst& debug, const Identyfikator& id, const Tekst& tytul, const Tekst& tresc)
		: identyfikator_(id), tytul_(tytul), tresc_(tresc), plik_(plik), funkcja_(funkcja), linia_(linia), stack_(pobierzSladStosu()), data_(Tekst(__DATE__) + Tekst(", ") + Tekst(__TIME__)), debug_(debug)
	{
	}

	Tekst Wyjatek::generujKomunikat()const
	{
		return std::move(Tekst("Tytul: ") + tytul_ +
			Tekst("\nID: ") + std::to_string(identyfikator_()) +
			Tekst("\nPlik: ") + plik_ +
			Tekst("\nFunkcja: ") + funkcja_ +
			Tekst("\nLinia: ") + std::to_string(linia_()) +
			Tekst("\nData kompilacji: ") + data_ +
			Tekst("\nTresc: ") + tresc_ +
			Tekst("\nStos wywo³añ: ") + stack_ + Tekst("\n"));
	}

	const Identyfikator& Wyjatek::getNumerWyjaku() const{
		return identyfikator_;
	}

	const Tekst& Wyjatek::getTytul() const{
		return tytul_;
	}

	const Tekst& Wyjatek::getTresc() const{
		return tresc_;
	}

	const Tekst& Wyjatek::getDebug() const{
		return debug_;
	}

	std::string Wyjatek::napis() const{
		SLog::Logger str(NAZWAKLASY(Wyjatek));
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		str.dodajPole(NAZWAPOLA(tytul_), tytul_);
		str.dodajPole(NAZWAPOLA(tresc_), tresc_);
		str.dodajPole(NAZWAPOLA(funkcja_), funkcja_);
		str.dodajPole(NAZWAPOLA(plik_), plik_);
		str.dodajPole(NAZWAPOLA(linia_), linia_);
		str.dodajPole(NAZWAPOLA(data_), data_);
		str.dodajPole(NAZWAPOLA(stack_), stack_);
		str.dodajPole(NAZWAPOLA(debug_), debug_);
		return std::move(str.napis());
	}

	const char * Wyjatek::what()const{
		komunikat_ = std::move(generujKomunikat());
		return komunikat_().c_str();
	}
}
