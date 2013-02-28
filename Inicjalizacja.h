#pragma once
/*
class Inicjalizacja
{
public:

	static bool czyNazwane( const string& , const ticpp::Element& );
	static string pobierzAtrybut( const string& , const ticpp::Element& ) throw( BrakAtrybutuXML );
	static Inicjalizacja* getSingleton();
	static string communique( const string& );
	static pair<string,string> message( const string& );

	void zaladuj( const string&  ) throw( WyjatekParseraXML , BrakMaski , WyjatekSTL , BrakAtrybutuXML , OgolnyWyjatek );
	
	StatekInfo* getStatekInfo( int );
	SurowceInfo* getSurowceInfo( int );

	list<StatekInfo*> getStatekInfo( );
	list<SurowceInfo*> getSurowceInfo( );

	string getKomunikat( const string& ) const;
	pair< string , string > getWiadomosc( const string& ) const;

	virtual string toString() const;

	SPG::IdType Inicjalizacja::pobierzMaske( const string& nazwa ) const throw( BrakMaski );

private:

	Inicjalizacja( );
	~Inicjalizacja( );

	bool addSurowceInfo( SurowceInfo* );
	bool addStatekInfo( StatekInfo* );

	bool addKomunikat( const pair< string , string > & );
	bool addWiadomosc( const pair< string , pair< string , string > >& );
	
	list<SurowceInfo*> surowceInfo;
	list<StatekInfo*> statekInfo;

	hash_map< string , pair< string , string > > Wiadomosci;
	hash_map< string ,  string > Komunikaty;
	
	map< string , SPG::IdType > mapaMask;

	void zaladujSurowceInfo( const ticpp::Document &)throw( WyjatekParseraXML , BrakMaski , WyjatekSTL , BrakAtrybutuXML , OgolnyWyjatek );
	void zaladujStatekInfo( const ticpp::Document & )throw( WyjatekParseraXML , BrakMaski , WyjatekSTL , BrakAtrybutuXML , OgolnyWyjatek );
	void ZaladujKomunikaty( const ticpp::Document& ) throw( WyjatekParseraXML , BrakAtrybutuXML );
	void ZaladujWiadomosci( const ticpp::Document& ) throw( WyjatekParseraXML , BrakAtrybutuXML );

	ticpp::Iterator<ticpp::Element> find( const string& , ticpp::Element * = NULL , bool = false ) const;
		
	pair< string ,  SPG::IdType > ZaladujMaske( const ticpp::Iterator<ticpp::Element>& ) const throw( WyjatekSTL , BrakAtrybutuXML );
	SurowceInfo* ZaladujObiektSurowceInfo( const ticpp::Iterator<ticpp::Element>& ) const throw( WyjatekParseraXML , BrakAtrybutuXML , BrakMaski );
	Obiekt* ZaladujObiekt( const ticpp::Iterator<ticpp::Element>& ) const throw( WyjatekSTL , BrakAtrybutuXML );
	Info* ZaladujInfo( const ticpp::Iterator<ticpp::Element>& child ) const throw( BrakAtrybutuXML , WyjatekParseraXML );
	StatekInfo* ZaladujObiektStatekInfo( const ticpp::Iterator<ticpp::Element>& ) const throw( WyjatekParseraXML , BrakAtrybutuXML , BrakMaski );
	Cena* ZaladujCena( const ticpp::Iterator<ticpp::Element>& ) const throw( WyjatekParseraXML , BrakAtrybutuXML , OgolnyWyjatek );
	pair< string, string > ZaladujKomunikat( const ticpp::Iterator<ticpp::Element>& ) const throw( WyjatekParseraXML , BrakAtrybutuXML );
	pair< string, pair< string, string > > ZaladujWiadomosc( const ticpp::Iterator<ticpp::Element>& ) const throw( WyjatekParseraXML , BrakAtrybutuXML );

};

*/