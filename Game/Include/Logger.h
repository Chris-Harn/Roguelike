#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <sstream> // std::ostringstream
#include <string>  // std::string

// Note: Not multiple thread safe. Need to add a
// mutex to Log at some point in the future...

enum class LogPriority {
    TraceP, 
    DebugP, 
    InfoP,
    WarnP, 
    ErrorP, 
    FatalP
};

class Logger {
public:
    static Logger *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new Logger();
        }
        return s_pInstance;
    }

    LogPriority m_verbosity;

    void Open( const char *path );
    void SetVerbosity( LogPriority newPriority );
    void Log( const char *message, LogPriority priority = LogPriority::InfoP );
    void Log( const std::ostringstream &stream, LogPriority priority = LogPriority::InfoP );
    void Log( const std::string &text, LogPriority priority = LogPriority::InfoP );
    void LogTime( const char *message, LogPriority priority = LogPriority::InfoP );    
private:
    Logger();
    ~Logger() {}

    static Logger *s_pInstance;
    const char *m_filepath;
};

typedef Logger TheLogger;

#endif
