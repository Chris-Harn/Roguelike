#ifndef __ENGINE_H__
#define __ENGINE_H__

class Engine {
public:
    static Engine *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new Engine();
        }
        return s_pInstance;
    }

    bool Init( const char *title, int windowWidth, int windowHeight, int targetFPS, int majorVersionOGL, int minorVersionOGL );
    void HandleEvents();
    void Render();
    void CleanUp();

    bool Running();
private:
    Engine();
    ~Engine() {}

    static Engine *s_pInstance;

    // Controls
    bool m_bRunning;
};

typedef Engine TheEngine;

#endif