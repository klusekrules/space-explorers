#include "SpShader.h"
#include <SFML\Graphics\GLExtensions.hpp>

bool sf::SpShader::loadFromParam(const std::string & value){
	fragmentFile_ = odczytajAdresPliku(value, "Fragment");
	vertexFile_ = odczytajAdresPliku(value, "Vertex");
	if (fragmentFile_.empty() && vertexFile_.empty())
		return false;
	if (fragmentFile_.empty() && !vertexFile_.empty())
		return loadFromFile(vertexFile_,Vertex);
	if (!fragmentFile_.empty() && vertexFile_.empty())
		return loadFromFile(fragmentFile_, Fragment);
	return loadFromFile(fragmentFile_, vertexFile_);
}

bool sf::SpShader::isParameter(const std::string & name) const{
	return  GLEXT_glGetUniformLocation(this->getNativeHandle(), name.c_str()) != -1;
}

sf::String sf::SpShader::getParamString() const{
	if(fragmentFile_.empty() && vertexFile_.empty())
		return std::move(std::string("none"));
	std::string value;

	if (!fragmentFile_.empty())
		value += "Fragment \"" + fragmentFile_ + "\"";
	
	if (!vertexFile_.empty())
		value += " Vertex \"" + vertexFile_ + "\"";
	return std::move(value);
}

std::string sf::SpShader::odczytajAdresPliku(const std::string & value, const char * begin) const {
	auto pozycjaNaglowka = value.find_first_of(begin);
	if (pozycjaNaglowka == std::string::npos)
		return std::string();
	else {
		std::string::size_type pozStart = std::string::npos;
		std::string::size_type pozStop = std::string::npos;
		for (pozStart = pozycjaNaglowka + strlen(begin); pozStart < value.size(); ++pozStart) {
			if (value[pozStart] == '"') {
				++pozStart;
				break;
			}
			if (value[pozStart] == ' ' || value[pozStart] == '\t')
				continue;
			pozStart = std::string::npos;
			break;
		}

		if (pozStart != std::string::npos && pozStart < value.size()) {
			for (pozStop = pozStart; pozStop < value.size(); ++pozStop) {
				if (value[pozStop] == '"')
					break;
			}
			if (pozStop != std::string::npos && pozStop < value.size() && pozStop > pozStart) {
				return std::move(value.substr(pozStart, pozStop - pozStart));
			}
		}

	}
	return std::string();
}
