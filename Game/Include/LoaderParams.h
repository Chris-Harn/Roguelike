#ifndef __LOADERPARAMS_H__
#define __LOADERPARAMS_H__

#include <string> // std::string

class LoaderParams {
public:
    LoaderParams( std::string textureID );
private:
    std::string m_textureID;
};

#endif