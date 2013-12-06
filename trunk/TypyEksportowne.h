extern "C"{ 

	__declspec(dllexport) struct Stan_t{
		int idStanu_;
		int numer_;
		long double dt_; //Milisekundy
	};

	__declspec(dllexport) struct Zdarzenie_t{
		int idStanu_;
		int numer_;
		int idZdarzenia_;
	};
};
