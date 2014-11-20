// DebugInfoView.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DebugInfoView.h"
#include "resource.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				Otworz();
HWND hTree;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DEBUGINFOVIEW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEBUGINFOVIEW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEBUGINFOVIEW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DEBUGINFOVIEW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 900, 520, NULL, NULL, hInstance, NULL);

   hTree = CreateWindowEx(WS_EX_CLIENTEDGE, WC_TREEVIEW, "Drzefko",
	   WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT,
	   5, 5, 300, 450, hWnd, (HMENU)1001, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

class Parser{
public:
	struct Element{
		std::string nazwaTypu_;
		std::string nazwaZmiennej_;
		std::string wartosc_;

		Element(){
			nazwaTypu_.clear();
			nazwaZmiennej_.clear();
			wartosc_.clear();
		}

		bool ok(){
			return !nazwaTypu_.empty();
		}
	};

	std::vector<std::shared_ptr<Element>> elementy_;

	Parser()
	{
		znSp_[0] = '[';
		znSp_[1] = '=';
		znSp_[2] = ';';
		znSp_[3] = ']';

		tvi_.mask = TVIF_TEXT | TVIF_PARAM;
		tvi_.lParam = -1;

		tvins_.item = tvi_;
		tvins_.hParent = TVI_ROOT;
		tvins_.hInsertAfter = TVI_LAST;
	}

	void parsuj(const std::string& napis, HWND hTreeView){
		str_ = napis;
		hTreeView_ = hTreeView;
		el_ = std::make_shared<Element>();
		tvi_.lParam = elementy_.size();
		elementy_.push_back(el_);

		while (krok()){
			switch (znakSpecjalny_){
			case '[':
				if (el_->ok()){
					stosEl_.push(el_);
					el_ = std::make_shared<Element>();
					tvi_.lParam = elementy_.size();
					elementy_.push_back(el_);
				}
				el_->nazwaTypu_ = napis_;
				if (czyZmiennaPusta()){
					dodajElement(napis_, true, false);
				}
				else{
					if (!stos_.empty())
						stos_.top().zmienna_ = false;
				}
				break;
			case ';':
				/*if (!czyZmiennaPusta()){
					if (!napis_.empty()) // do analizy
						dodajElement(napis_, false, false);
					pop();
				}*/
				break;
			case '=':
				if (el_->ok()){
					stosEl_.push(el_);
					el_ = std::make_shared<Element>();
					tvi_.lParam = elementy_.size();
					elementy_.push_back(el_);
				}
				el_->nazwaZmiennej_ = napis_;
				dodajElement(napis_, true, true);
				break;
			case ']':
				if (nawiasy_){
					el_->wartosc_ = napis_;
				}
				pop();
				if (!stosEl_.empty()){
					el_ = stosEl_.top();
					stosEl_.pop();
				}
				break;
			default:
				break;
			}
		}
	}

private:

	struct Level
	{
		Level(HTREEITEM h, bool z):handle_(h), zmienna_(z){}
		HTREEITEM handle_;
		bool zmienna_;
	};

	TVITEM tvi_;
	TVINSERTSTRUCT tvins_;
	std::stack<Level> stos_;
	std::stack<std::shared_ptr<Element>> stosEl_;
	std::shared_ptr<Element> el_;
	std::string str_;
	HWND hTreeView_;

	std::string::size_type pos_ = 0;
	char znSp_[4];
	std::string napis_;
	char znakSpecjalny_;
	bool nawiasy_;

	bool krok(){
		std::string nowy;

		if (pos_ >= str_.size())
			return false;

		nawiasy_ = false;
		for (; pos_ < str_.size() && isspace(str_[pos_]); ++pos_);
		if (str_[pos_] != '"'){
			for (; pos_ < str_.size() && !czyZnakSpecjalny(str_[pos_]); ++pos_)
				nowy.push_back(str_[pos_]);
		}else{
			nawiasy_ = true;
			for (++pos_; pos_ < str_.size() && str_[pos_] != '"'; ++pos_)
				nowy.push_back(str_[pos_]);
			for (; pos_ < str_.size() && !czyZnakSpecjalny(str_[pos_]); ++pos_);
		}

		napis_ = std::move(nowy);
		znakSpecjalny_ = str_[pos_];
		++pos_;
		return true;
	}

	bool czyZnakSpecjalny(char c){
		for (int i = 0; i < 4; ++i)
			if (znSp_[i] == c)
				return true;
		return false;
	}

	void ustawNazwe( const std::string& nazwa ){
		tvi_.pszText = (char *)nazwa.c_str();
		tvi_.cchTextMax = (int)nazwa.size();
	}

	void ustawRodzica(){
		if (stos_.empty())
			tvins_.hParent = TVI_ROOT;
		else
			tvins_.hParent = stos_.top().handle_;
	}

	void wstawElement(bool naStos , bool zmienna){
		tvins_.item = tvi_; 
		if (naStos)
			stos_.emplace(TreeView_InsertItem(hTreeView_, &tvins_), zmienna);
		else
			TreeView_InsertItem(hTreeView_, &tvins_);
	}

	void dodajElement( const std::string& napis, bool naStos, bool zeZmienna){
		ustawNazwe(napis);
		ustawRodzica();
		wstawElement(naStos, zeZmienna);
	}

	void pop(){
		if (!stos_.empty())
			stos_.pop();
	}

	bool czyZmiennaPusta(){
		return stos_.empty() || (!stos_.empty() && !stos_.top().zmienna_);
	}
};

Parser parser;

void Otworz(){
	//std::string str = "SpEx::ZarzadcaZasobow[ MapaInicjalizatorow[  Inicjalizator[  Typ=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"lua\" ] Poprawny=bool[ \"true\" ] ] Inicjalizator[  Typ=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"dll\" ] Poprawny=bool[ \"true\" ] ] ] TablicaLokalizacjiZasobu[  WpisLokalizacjiZasobu[  IdentyfikatorZasobu=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"StartScreen\" ] Lokalizacja=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"resource\\Space_start_screen.png\" ] ] WpisLokalizacjiZasobu[  IdentyfikatorZasobu=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"BrakObrazka\" ] Lokalizacja=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"resource\\Brak_obrazka.png\" ] ] ] generator_=SpEx::GeneratorIdentyfikatorow[ mapa_0=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"StartScreen\" ] mapa_1=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"BrakObrazka\" ] mapa_2=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"lua_\" ] mapa_3=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"dll_\" ] mapa_4=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"lua_wspolna\" ] ] MapaZasobow[  Element[  Identyfikator=int[ \"2\" ] WpisZasobu[  SlabyWsk=std::weak_ptr<class SpEx::Zasob>[ \"0x40cc3c0\" ] SilnyWsk=std::shared_ptr<class SpEx::Zasob>[ \"0x40cc3c0\" ] Przechowywany=bool[ \"true\" ] ] ] Element[  Identyfikator=int[ \"3\" ] WpisZasobu[  SlabyWsk=std::weak_ptr<class SpEx::Zasob>[ \"0x40cc060\" ] SilnyWsk=std::shared_ptr<class SpEx::Zasob>[ \"0x40cc060\" ] Przechowywany=bool[ \"true\" ] ] ] Element[  Identyfikator=int[ \"4\" ] WpisZasobu[  SlabyWsk=std::weak_ptr<class SpEx::Zasob>[ \"0x40cd110\" ] SilnyWsk=std::shared_ptr<class SpEx::Zasob>[ \"0x40cd110\" ] Przechowywany=bool[ \"true\" ] ] ] ] pustyNapis_=std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >[ \"\" ] ]";
	//std::string str = "Uklad ID=int[ \"3\" ]";
	std::ifstream t("zrzut.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();
	parser.parsuj(buffer.str(), hTree);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static std::string str;
	RECT rect;
	rect.top = 10;
	rect.left = 310;
	rect.bottom = 440;
	rect.right = 890;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_OTWORZ:
		{
			Otworz();
		}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{
		case TVN_SELCHANGED:
		{
			NMTREEVIEW* pnmtv = (LPNMTREEVIEW)lParam;
			//LPTSTR str = (pnmtv->itemNew.pszText);
			if (pnmtv->itemNew.lParam >= 0 && pnmtv->itemNew.lParam < parser.elementy_.size()){
				str = "Typ: " + parser.elementy_[pnmtv->itemNew.lParam]->nazwaTypu_ + "\nZmienna: " 
					+ parser.elementy_[pnmtv->itemNew.lParam]->nazwaZmiennej_ + "\nWartosc: " + parser.elementy_[pnmtv->itemNew.lParam]->wartosc_;
				InvalidateRect(hWnd, &rect, true);
				//MessageBox(hWnd, str.c_str(), "load", MB_OK);
			}
			//MessageBox(hWnd, str, "load", MB_OK);
			//HTREEITEM hCurrentItem = TreeView_GetSelection(hTree);
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		}
			break;

		}
	}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); 
		DrawText(hdc, str.c_str(), str.size(), &rect, DT_WORDBREAK | DT_END_ELLIPSIS);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
