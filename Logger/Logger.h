// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LOGGER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LOGGER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once
#include "ExportSymbol.h"
#include <sstream>
#include <stack>

using std::stringstream;
using std::stack;
using std::deque;

LOGGER_EXPIMP_TEMPLATE template class LOGGER_API deque<bool>;
LOGGER_EXPIMP_TEMPLATE template class LOGGER_API stack<bool>;

#include "LoggerInterface.h"

class LOGGER_API Logger :
	public LoggerInterface
{
public:
	Logger();
	Logger( const string& );
	~Logger();

	template< class T >
	static string field( const T& a){
		stringstream str;
		str << a;
		return str.str();
	}

	static string field( const string& name, const LoggerInterface& liClassF, const LoggerInterface& liClassS );

	static string reMakeSimpleClassString( const string &className, const string &tekst );

	void addField( const string& name, const LoggerInterface& liClass );

	void addField( const string& name, const string& liClass );

	void addField( const string& name, const LoggerInterface& liClassF, const LoggerInterface& liClassS );
	
	void addClass( const string& s );

	void startSubClass( const string& s );

	void endSubClass();

	string toString() const override;

private:

	void testPierwszy( );

	stringstream napis;
	stack<bool> stos;
};

