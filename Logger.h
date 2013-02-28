#pragma once

#include "Main.h"
#include <sstream>
#include <stack>

class Logger:
	public LoggerInterface<Logger>
{
public:
	Logger();
	Logger( const string& );
	~Logger();

	template< class T >
	static string field( const string& name , const T& a){
		stringstream str;
		str << a;
		return str.str();
	}

	template< typename T , typename W >
	static string field( const string& name, const LoggerInterface<T> &liClassF, const LoggerInterface<W>   &liClassS ){
		stringstream str;
		if(name.size() > 0){
			str << name;
		}
		str << " { " << liClassF.toString() << " , " << liClassS.toString() <<" }";
		return str.str();
	}

	static string reMakeSimpleClassString( const string &className, const string &tekst ){
		return string(className + "[ " + tekst +" ]");
	}

	template< typename T >
	void addField( const string& name, const LoggerInterface<T>& liClass ){

		testPierwszy(); 

		napis << " "  << name << "=" << liClass.toString();
	}

	template< typename T , typename W >
	void addField( const string& name, const LoggerInterface<T> &liClassF, const LoggerInterface<W>   &liClassS ){

		testPierwszy();

		if(name.size() > 0){
			napis << name;
		}

		napis << "{ " << liClassF.toString() << " , " << liClassS.toString() <<" }";
	}
	
	string toString() const override;

	void addClass( const string& s );

	void startSubClass( const string& s ){
		
		testPierwszy();
		napis << s << "[ ";

		stos.push(true);
	}
	void endSubClass(){
		stos.pop();
		napis << " ]";
	}

private:

	void testPierwszy( ){
		if(!stos.top())
			napis<<", ";
		else
			stos.top() = false;
	}

	stringstream napis;
	int poziom;
	stack<bool> stos;
};

