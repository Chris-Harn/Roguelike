#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "OpenGL/Window.h"

class Engine {
public:
    static Engine *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new Engine();
        }
        return s_pInstance;
    }

    bool Init( const char *title, int windowWidth, int windowHeight, int targetFPS );
    void HandleEvents();
    void Render();
    void CleanUp();

    bool Running();

    // OpenGL Objects
    Window *m_pWindow;
private:
    Engine();
    ~Engine() {}

    static Engine *s_pInstance;

    // Controls
    bool m_bRunning;
};

typedef Engine TheEngine;

#endif