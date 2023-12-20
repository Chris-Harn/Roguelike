#include "BasicLogger.h"

#include <fstream>  // std::ofstream
#include <iostream> // std::cout, std::endl

BasicLogger *BasicLogger::s_pInstance = 0;

BasicLogger::BasicLogger() {
    m_verbosity = LogPriority::TraceP;
    m_filepath = "log.txt";
}

void BasicLogger::Open( const char *path ) {
    m_filepath = path;
}

void BasicLogger::SetVerbosity( LogPriority newPriority ) {
    m_verbosity = newPriority;
}

void BasicLogger::Log( LogPriority priority, const char *message ) {
    if( priority >= m_verbosity ) {
        //std::ofstream FILE( "log.txt", std::ios_base::app );
        std::ofstream FILE( m_filepath, std::ios_base::app );
        switch( priority ) {
        case LogPriority::TraceP: FILE << "Trace: \t"; break;
        case LogPriority::DebugP: FILE << "Debug: \t"; break;
        case LogPriority::InfoP: FILE << "Info: \t"; break;
        case LogPriority::WarnP: FILE << "Warn: \t"; break;
        case LogPriority::ErrorP: FILE << "Error: \t"; break;
        case LogPriority::FatalP: FILE << "Fatal: \t"; break;
        }

        FILE << message << std::endl;
        FILE.close();
    }
}