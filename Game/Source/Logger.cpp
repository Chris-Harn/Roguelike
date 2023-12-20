#include "Logger.h"

#include <iostream>   // std::cout, std::endl
#include <fstream>    // std::ofstream
#include <iomanip>    // std::setfill, std::setw 
#include <Windows.h>  // SYSTEMTIME, GetLocalTime

Logger *Logger::s_pInstance = 0;

Logger::Logger() {
    m_verbosity = LogPriority::TraceP;
    m_filepath = "log.txt";
}

void Logger::Open( const char *path ) {
    m_filepath = path;
}

void Logger::SetVerbosity( LogPriority newPriority ) {
    m_verbosity = newPriority;
}

void Logger::Log( const char *message, LogPriority priority ) {
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

        FILE << message << std::endl;
        FILE.close();
    }
}

void Logger::Log( const std::ostringstream &stream, LogPriority priority ) {
    Log( stream.str().c_str(), priority );
}

void Logger::Log( const std::string &text, LogPriority priority ) {
    Log( text.c_str(), priority );
}

void Logger::LogTime( const char *message, LogPriority priority ) {
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


