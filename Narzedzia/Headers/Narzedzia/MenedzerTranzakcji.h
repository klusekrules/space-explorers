#pragma once
#include "NarzedziaSymbol.h"
#include "Logger\LoggerInterface.h"
#include "Logger\Log.h"
#include "Operacja.h"
#include <vector>
#include <memory>
namespace SpEx{
	/**
	* \brief Klasa reprezentuj¹ca tranzakcje.
	*
	* Klasa zawiera zbiór operacji i odpowiadaj¹cych im operacji odwrotnych, sk³adaj¹cych siê na jedn¹ tranzakcjê.
	* Klasa gwarantuje wykonanie siê wszystkiego albo niczego, je¿eli siê to nie uda zostanie wyrzucony wyj¹tek.
	* W takim wypadku nie wiadomo co zosta³o cofniête, a co nie zosta³o cofniête. W celu zabezbieczenia siê przed
	* dalszymi b³ednymi zmianami danych zaleca siê przerwanie dzia³ania programu.
	*/
	class NARZEDZIA_API MenedzerTranzakcji :
		virtual public SLog::LoggerInterface
	{
	private:
		typedef std::shared_ptr< Operacja > Element; /// Type elementów przechowywanych w kontenerze.
		typedef std::vector< Element > Kontener; /// Typ kontenera przechowuj¹cego elementy.
		Kontener listaOperacji_; /// Lista przechowywanych operacji.
		SLog::Log& log_;

	public:

		/**
		* \brief Konstruktor.
		*/
		MenedzerTranzakcji(SLog::Log& log);

		/**
		* \brief Destruktor.
		*/
		virtual ~MenedzerTranzakcji() = default;

		/**
		* \brief Metoda dodaje operacje do listy oczekuj¹cych na wykonanie.
		*
		* \param[in] operacja - Operacja dodawana do listy.
		*/
		void dodaj(Element operacja);

		/**
		* \brief Metoda wykonuj¹ca wszystkie operacje tranzakcyjne jakie przechowuje.
		*
		* Metoda wykonuje wszystkie operacje w takiej kolejnoœci jakiej zosta³y dodane.
		* W przypadku niepowodzenia jednej operacji wszytskie wykonane sa cofane kolejno pocz¹wszy od ostatnio udanej.
		* \return Metoda zwraca true, je¿eli siê powiedzie lub false w przeciwnym wypadku.
		*/
		bool wykonaj();

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;
	};
};
