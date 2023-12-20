#ifndef __BASICLOGGER_H__
#define __BASICLOGGER_H__

enum class LogPriority {
    TraceP, 
    DebugP, 
    InfoP,
    WarnP, 
    ErrorP, 
    FatalP
};

// Not multiple thread safe. Need to add a mutex
// to Log at some point in the future.

class BasicLogger {
public:
    static BasicLogger *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new BasicLogger();
        }
        return s_pInstance;
    }

    LogPriority m_verbosity;

    void Open( const char *path );
    void SetVerbosity( LogPriority newPriority );
    void Log( const char *message, LogPriority priority = LogPriority::TraceP );
    void LogTime( const char *message, LogPriority priority = LogPriority::TraceP );
private:
    BasicLogger();
    ~BasicLogger() {}

    static BasicLogger *s_pInstance;
    const char *m_filepath;
};

typedef BasicLogger TheBasicLogger;

#endif
