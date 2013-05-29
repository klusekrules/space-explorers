// Logger.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "Logger.h"

Logger::Logger()
{
	stos.push(true);
}

Logger::~Logger(){
}

Logger::Logger( const string& nazwa )
{
	stos.push(true);
	napis<<nazwa<<"[";
}

string Logger::toString() const{
	return napis.str() + " ]";
}

void Logger::addClass( const string& tekst ){
	testPierwszy();
	napis<<" "<<tekst;
}

string Logger::field( const string& name, const LoggerInterface& liClassF, const LoggerInterface& liClassS ){
	stringstream str;
	str << name << " { " << liClassF.toString() << " , " << liClassS.toString() <<" }";
	return str.str();
}

string Logger::reMakeSimpleClassString( const string &className, const string &tekst ){
	return string(className + "[ " + tekst +" ]");
}

void Logger::addField( const string& name, const LoggerInterface& liClass ){
	testPierwszy();
	napis << " "  << name << "=" << liClass.toString();
}

void Logger::addField( const string& name, const string& liClass ){
	testPierwszy();
	napis << " "  << name << "=" << liClass;
}

void Logger::addField( const string& name, const LoggerInterface& liClassF, const LoggerInterface& liClassS ){
	testPierwszy();
	napis << name << "{ " << liClassF.toString() << " , " << liClassS.toString() <<" }";
}

void Logger::startSubClass( const string& s ){
	testPierwszy();
	napis << s << "[ ";
	stos.push(true);
}

void Logger::endSubClass(){
	stos.pop();
	napis << " ]";
}

void Logger::testPierwszy( ){
	if(!stos.top())
		napis<<", ";
	else
		stos.top() = false;
}