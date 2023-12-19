#include "Engine.h"

#include <iostream>

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
	// Engine globals
	m_bRunning = false;
}

bool Engine::Init( const char *title, int windowWidth, int windowHeight, int targetFps, int majorVersionOGL, int minorVersionOGL ) {
	std::cout << "Inside Init." << std::endl;
	return true;
}

void Engine::HandleEvents() {
	std::cout << "Inside HandleEvents." << std::endl;
}

void Engine::Render() {
	std::cout << "Inside Render." << std::endl;
}

void Engine::CleanUp() {
	std::cout << "Inside CleanUp." << std::endl;
}

bool Engine::Running() {
	return m_bRunning;
}