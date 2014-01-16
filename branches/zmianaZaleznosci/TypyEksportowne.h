extern "C"{ 

	struct __declspec(dllexport) Stan_t{
		int idStanu_;
		int numer_;
		long double dt_; //Milisekundy
	};

	struct __declspec(dllexport) Zdarzenie_t{
		int idStanu_;
		int numer_;
		int idZdarzenia_;
	};
};
