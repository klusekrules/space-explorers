#pragma once
#define METODA_RPC_AUTORYZACJA "autoryzacja"
#define METODA_RPC_INSTANCJA "instancja"
#define METODA_RPC_METODA "metoda"
#define METODA_RPC_NAZWA "nazwa"
#define METODA_RPC_ID_UNIKALNE "id-unikalne"
#define METODA_RPC_POWTORZENIE "powtorzenie"
#define METODA_RPC_CZAS_WYWOLANIA "czas-wywolania"
#define METODA_RPC_CZAS_ODPOWIEDZI "czas-odpowiedzi"
#define METODA_RPC_PARAMETRY "parametry"
#define METODA_RPC_RETURN "return"


#define METODA_RPC_THROW "throw"
#define METODA_RPC_TYPE "typ"
#define METODA_RPC_KOMUNIKAT "komunikat"

#define RPC_FLAG_COMPRESSION 0x1
#define RPC_FLAG_AUTHORIZATION 0x2

#define RPC_OK 0
#define RPC_ERROR_MISSING_AUTORYZACJA -1
#define RPC_ERROR_MISSING_INSTANCJA -2
#define RPC_ERROR_MISSING_METODA -3
#define RPC_ERROR_MISSING_NAZWA_METODY -4
#define RPC_ERROR_MISSING_ID_UNIKALNE -5
#define RPC_ERROR_MISSING_POWTORZENIE -6
#define RPC_ERROR_MISSING_CZAS_WYWOLANIA -7

#define RPC_ERROR_UNAUTHORIZED -8
#define RPC_ERROR_WITHOUT_AUTHORIZED -9
#define RPC_ERROR_NEED_AUTHORIZATION -10


#define RPC_ERROR_MISSING_CRC -11
#define RPC_ERROR_INVALID_CRC -12