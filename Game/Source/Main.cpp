#include "Engine.h"

enum PROTO {
    WINDOW_WIDTH = 1280,
    WINDOW_HEIGHT = 1024,
    TARGET_FPS = 60,
    OPENGL_MAJOR_VERISON = 4,
    OPENGL_MINOR_VERSION = 6,
};

int main( int argc, char *argv[] ) {
    if( TheEngine::Instance()->Init( "Roguelike Game",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        TARGET_FPS ) == true ) {
        while( TheEngine::Instance()->Running() ) {
            TheEngine::Instance()->HandleEvents();
            TheEngine::Instance()->Render();
        }
    }
    TheEngine::Instance()->CleanUp();

    return 0;
}