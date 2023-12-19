#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "LoaderParams.h"

class GameObject {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

protected:
    GameObject( const LoaderParams *pParms ) { }
    virtual ~GameObject() { }
};

#endif