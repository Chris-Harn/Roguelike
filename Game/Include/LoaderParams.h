#ifndef __LOADERPARAMS__
#define __LOADERPARAMS__

#include <string> // std::string

class LoaderParams {
public:
    LoaderParams( std::string textureID );
private:
    std::string m_textureID;
};

#endif