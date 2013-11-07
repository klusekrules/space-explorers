#pragma once

#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "TGUI-x64-d" )
#else if _WIN32
#pragma comment( lib, "TGUI-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "TGUI-x64-r" )
#else if _WIN32
#pragma comment( lib, "TGUI-x86-r" )
#endif
#endif


#include <map>
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <unordered_map>
#include <chrono>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include "RoundedRectangleShape.hpp"

