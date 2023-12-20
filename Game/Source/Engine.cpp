#include "Engine.h"

#include "Logger.h"

#include <iostream> // std::bac_alloc

Engine *Engine::s_pInstance = 0;

Engine::Engine() {
	// OpenGL globals
	m_pWindow = nullptr;

	// Engine globals
	m_bRunning = false;
}

bool Engine::Init( const char *title, int windowWidth, int windowHeight, int targetFps ) {
	try { m_pWindow = new Window(); }
	catch( const std::bad_alloc &e ) {
		(void)e;
		TheLogger::Instance()->Log( "*** Window failed to have memory allocated. ***", LogPriority::ErrorP );
		return false;
	}
	if( m_pWindow->Initialization( windowWidth,
		windowHeight,
		title,
		nullptr ) == false ) {
		TheLogger::Instance()->Log( "*** Exited Program ***", LogPriority::FatalP );
		return false;
	}
	m_pWindow->GetVersion();

	m_pWindow->MakeCurrentContext();

	// Everything started up without issue, play game
	m_bRunning = true;

	return true;
}

void Engine::HandleEvents() {
	m_pWindow->PollEvents();

	if( ( m_pWindow->GetsKeys()[256] == true ) ||
		( m_pWindow->GetShouldClose() == true ) ) {
		m_bRunning = false; // GLFW_KEYS_ESCAPE
	}
}

void Engine::Render() {
	m_pWindow->MakeCurrentContext();
	m_pWindow->ClearColorBuffer();

	m_pWindow->SwapBuffers();
}

void Engine::CleanUp() {
	m_pWindow->MakeCurrentContext();
	m_pWindow->CleanUp();
}

bool Engine::Running() {
	return m_bRunning;
}