#include "BasicLogger.h"

#include <fstream>    // std::ofstream
#include <iostream>   // std::cout, std::endl
#include <iomanip>    // std::setfill, std::setw 
#include <Windows.h>  // SYSTEMTIME, GetLocalTime


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

void BasicLogger::Log( const char *message, LogPriority priority ) {
    if( priority >= m_verbosity ) {
        std::ofstream FILE( m_filepath, std::ios_base::app );
        switch( priority ) {
        case LogPriority::TraceP: FILE << "Trace: \t"; break;
        case LogPriority::DebugP: FILE << "Debug: \t"; break;
        case LogPriority::InfoP: FILE << "Info: \t"; break;
        case LogPriority::WarnP: FILE << "Warn: \t"; break;
        case LogPriority::ErrorP: FILE << "Error: \t"; break;
        case LogPriority::FatalP: FILE << "Fatal: \t"; break;
        }
        // Date & Time
        SYSTEMTIME time;
        GetLocalTime( &time );

        FILE << " [" << time.wYear << '.'
            << std::setfill( '0' ) << std::setw( 2 ) << time.wMonth << '.'
            << std::setfill( '0' ) << std::setw( 2 ) << time.wDay << ' '
            << std::setfill( ' ' ) << std::setw( 2 ) << time.wHour << ':'
            << std::setfill( '0' ) << std::setw( 2 ) << time.wMinute << ':'
            << std::setfill( '0' ) << std::setw( 2 ) << time.wSecond << '.'
            << std::setfill( '0' ) << std::setw( 3 ) << time.wMilliseconds << "] ";

        FILE << message << std::endl;
        FILE.close();
    }
}