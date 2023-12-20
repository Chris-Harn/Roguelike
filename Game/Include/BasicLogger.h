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

class BasicLogger {
public:
    static BasicLogger *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new BasicLogger();
            //s_pInstance->Open(  );
        }
        return s_pInstance;
    }

    LogPriority m_verbosity;

    void Open( const char *path );
    void SetVerbosity( LogPriority newPriority );
    void Log( LogPriority priority, const char *message );
private:
    BasicLogger();
    ~BasicLogger() {}

    static BasicLogger *s_pInstance;
    const char *m_filepath;
};

typedef BasicLogger TheBasicLogger;

#endif
