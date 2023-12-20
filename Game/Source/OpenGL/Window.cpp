#include "OpenGL/Window.h"
#include "Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef _DEBUG
#include <iostream>
#endif

Window::Window() {
	m_pWindow = nullptr;

	// Clear all keys
	for( int i = 0; i < TOTAL_KEYS; i++ ) {
		m_bKeys[i] = false;
	}

	m_BufferWidth = 0;
	m_BufferHeight = 0;
}

bool Window::Initialization( unsigned int width, unsigned int height, const char *title, GLFWwindow *shareContents ) {
	if( glfwInit() == false ) {
		TheLogger::Instance()->Log( "*** GLFW failed to start up. ***", LogPriority::ErrorP );
		glfwTerminate();
		return false;
	}

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
	glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

	// Grab list of monitors
	int count;
	GLFWmonitor **monitors = glfwGetMonitors( &count );
	const GLFWvidmode *mode = nullptr;

	// Primary Window setup
	mode = glfwGetVideoMode( monitors[0] );

	// **********************************
	glfwWindowHint( GLFW_AUTO_ICONIFY, GLFW_TRUE );
	glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
	glfwWindowHint( GLFW_RED_BITS, mode->redBits );
	glfwWindowHint( GLFW_GREEN_BITS, mode->greenBits );
	glfwWindowHint( GLFW_BLUE_BITS, mode->blueBits );
	glfwWindowHint( GLFW_REFRESH_RATE, mode->refreshRate );

	m_pWindow = glfwCreateWindow( mode->width, mode->height, title, nullptr, nullptr );

	TheLogger::Instance()->Log( std::ostringstream{} << "Hello world! " << mode->width << mode->height << " Testing..." );

	if( !m_pWindow ) {
		TheLogger::Instance()->Log( "*** Window failed to be created. ***", LogPriority::ErrorP );
		glfwTerminate();
		return false;
	}

	// Need to make current context so glViewport and Glew will work on the correct window
	this->MakeCurrentContext();

	// Set the viewport and lock it
	glViewport( 0, 0, mode->width, mode->height );
	glfwSetWindowSize( m_pWindow, mode->width, mode->height );

	// Get buffer size information
	glfwGetFramebufferSize( m_pWindow, &m_BufferWidth, &m_BufferHeight );


	// Enable OpenGL commands as everything up to this point has been GLFW
	this->CallGlew();

	// Set up callbacks on primary monitor... keyboard polling, mouse polling, etc
	CreateCallbacks();

	return true;
}

bool Window::CallGlew() {
	glfwMakeContextCurrent( m_pWindow );

	// Allow modern extension features
	glewExperimental = GL_TRUE; // Tells drivers to expose all addresses
	if( glewInit() != GLEW_OK ) {
		TheLogger::Instance()->Log( "*** GLEW failed to initalize. ***", LogPriority::ErrorP );
		glfwDestroyWindow( m_pWindow );
		glfwTerminate();
		return false;
	}

	return true;
}

void Window::MakeCurrentContext() {
	glfwMakeContextCurrent( m_pWindow );
}

void Window::HideWindow( bool hide ) {
	if( hide == true ) {
		glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE );
	}
	else {
		glfwWindowHint( GLFW_VISIBLE, GLFW_TRUE );
	}
}

void Window::ClearColorBuffer( float red, float green, float blue ) {
	glClearColor( red, green, blue, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Window::SwapBuffers() {
	glfwSwapBuffers( m_pWindow );
}

void Window::PollEvents() {
	glfwPollEvents();
}

void Window::CleanUp() {
	if( m_pWindow != nullptr ) {
		glfwDestroyWindow( m_pWindow );
		m_pWindow = nullptr;
	}

	glfwTerminate();
}

void Window::GetVersion() {
	// Does not work unless CallGlew GLEW has been called...
	#ifdef _DEBUG
		TheLogger::Instance()->LogTime( (const char *)glGetString( GL_VENDOR ) );
		TheLogger::Instance()->LogTime( (const char *)glGetString( GL_RENDERER ) );
		TheLogger::Instance()->LogTime( (const char *)glGetString( GL_VERSION ) );
	#endif
}

float Window::GetBufferWidth() {
	return (float)m_BufferWidth;
}

float Window::GetBufferHeight() {
	return (float)m_BufferHeight;
}

bool *Window::GetsKeys() {
	return m_bKeys;
}

bool Window::IsKeyUp( int key ) {
	if( key != 0 ) {
		return m_bKeys[key];
	}

	return false;
}

bool Window::IsKeyDown( int key ) {
	if( key != 0 ) {
		return !m_bKeys[key];
	}

	return false;
}

bool Window::GetShouldClose() {
	return int( glfwWindowShouldClose( m_pWindow ) );
}

GLFWwindow *Window::GetWindow() {
	return m_pWindow;
}

void Window::CreateCallbacks() {
	// Setup GLFW callback that uses this object as owner
	// or else keys won't work
	glfwSetWindowUserPointer( m_pWindow, this );

	// Callback that captures key presses and releases
	glfwSetKeyCallback( m_pWindow, HandleKeys );
	glfwSetInputMode( m_pWindow, GLFW_STICKY_KEYS, 1 );
}

void Window::HandleKeys( GLFWwindow *window,
	int key,
	int code,
	int action,
	int mode ) {
	// Window pointer user function
	Window *theWindow = static_cast<Window *>( glfwGetWindowUserPointer( window ) );

	if( ( key == GLFW_KEY_ESCAPE ) && ( action == GLFW_PRESS ) ) {
		glfwSetWindowShouldClose( window, GL_TRUE );
		theWindow->m_bKeys[GLFW_KEY_ESCAPE] = true;
	}

	if( ( key >= 0 ) && ( key < 1024 ) ) {
		if( action == GLFW_PRESS ) {
			theWindow->m_bKeys[key] = true;
			#ifdef _DEBUG
				std::cout << "Pressed " << key << std::endl; // Trouble Shooting Code
				TheLogger::Instance()->Log( std::ostringstream{} << "Pressed " << key );
			#endif
		}
		else if( action == GLFW_RELEASE ) {
			theWindow->m_bKeys[key] = false;
			#ifdef _DEBUG
				std::cout << "Released " << key << std::endl; // Trouble Shooting Code
				TheLogger::Instance()->Log( std::ostringstream{} << "Released " << key );
			#endif
		}
	}

}