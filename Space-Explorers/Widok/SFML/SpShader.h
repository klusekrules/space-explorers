#pragma once
#include <SFML\Graphics\Shader.hpp>
#include <SFML\System\String.hpp>

namespace sf {
	class SpShader : public Shader {
	public:
		using Shader::Shader;
		bool loadFromParam(const std::string &);
		bool isParameter(const std::string&) const;
		sf::String getParamString() const;
	private:

		std::string odczytajAdresPliku(const std::string&, const char*) const;

		std::string fragmentFile_;
		std::string vertexFile_;
	};
};