
#pragma once

#include "Je-Log.h"
#include "SourceInfo.h"
#include "ThreadInfo.h"
#include "JeTime.h"

// O------------------------------------------------------------------------------O
// | Je-Log Declarations                                                          |
// O------------------------------------------------------------------------------O
#pragma region Declarations

namespace JeLog
{

#pragma region LogRecord
#if !defined(JE_LOG_LOG_RECORD)

    /////////////////////////////////////////////////////////////////////////
    ///  \brief A LogRecord instance represents an event being Logged.
    ///
    /// LogRecord instances are created every time something is logged. They
    /// contain all the information pertinent to the event being logged. The
    /// main information passed in is in msg and args, which are combined
    /// using str(msg) % args to create the message field of the record. The
    /// record also includes information such as when the record was created,
    /// the source line where the logging call was made, and thread
    /// information to be logged.
    ///
    /////////////////////////////////////////////////////////////////////////
    class LogRecord
    {
    private:
        char *m_Name;
        char *m_Msg;
        JeLog::Level m_Level;
        JeLog::SourceInfo m_SrcInfo;
        JeLog::ThreadInfo m_ThdInfo;
        JeLog::Time *m_CreatedTime;

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize an empty Logging Record.
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize a Logging Record with provided Information.
        ///
        /// \param name
        /// \param message
        /// \param level
        /// \param sourceInfo
        /// \param creationTime
        /// \param threadID
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord(char *name, char *message, JeLog::Level level, JeLog::SourceInfo sourceInfo, JeLog::Time *creationTime, JeLog::ThreadInfo threadInfo);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *GetName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name for this LogRecord.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetName(char *name);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Level for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::Level GetLevel();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Level for this LogRecord.
        ///
        /// \param level
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetLevel(JeLog::Level level);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the message for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *GetMessage();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the message for this LogRecord.
        ///
        /// \param message
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetMessage(char *message);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name of the Function in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *GetFunction();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name of the Function in which this LogRecord was Created.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFunction(char *name);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the File Name in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *GetFileName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the File Name in which this LogRecord was Created.
        ///
        /// \param filename
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFileName(char *filename);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Line Number for which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        int GetLineNo();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Line Number for which this LogRecord was Created.
        ///
        /// \param lineno
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetLineNo(int lineno);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Thread ID for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        uint32_t GetThreadID();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Thread ID for this LogRecord.
        ///
        /// \param threadID
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetThreadID(uint32_t threadID);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Thread Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *GetThreadName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Thread Name for this LogRecord.
        ///
        /// \param threadName
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetThreadName(char *threadName);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Time of Creation for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::Time *GetCreationTime();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Time of Creation for this LogRecord.
        ///
        /// \param creationTime
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetCreationTime(JeLog::Time *creationTime);
    };

#define JE_LOG_LOG_RECORD
#endif // JE_LOG_LOG_RECORD

#pragma endregion // LogRecord

}; // namespace JeLog

// O------------------------------------------------------------------------------O
// | Je-Log Definitions                                                          |
// O------------------------------------------------------------------------------O
#pragma region Definitions
namespace JeLog
{

#pragma region LogRecord

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::LogRecord
    //-----------------------------------------------------------------------------
    // - LogRecord()
    // - ~LogRecord()
    // - GetName()
    // - GetLevel()
    // - GetMessage()
    // - GetFunction()
    // - Name()
    // - Level()
    // - Message()
    // - Function()
    // - GetFileName()
    // - GetLineNo()
    // - GetThreadID()
    // - GetThreadName()
    //-----------------------------------------------------------------------------

    // #if !defined(JE_LOG_LOG_RECORD)

    LogRecord::LogRecord()
    {
        m_Name = "";
        m_Msg = "";
        m_Level = JeLog::Level::unknown;
        m_SrcInfo = JeLog::SourceInfo();
        m_CreatedTime = nullptr;
        m_ThdInfo = JeLog::ThreadInfo();
    };

    LogRecord::LogRecord(char *name, char *message, JeLog::Level level, JeLog::SourceInfo sourceInfo, JeLog::Time *creationTime, JeLog::ThreadInfo threadInfo)
    {
        m_Name = name;
        m_Msg = message;
        m_Level = level;
        m_SrcInfo = sourceInfo;
        m_CreatedTime = creationTime;
        m_ThdInfo = threadInfo;
    };

    char *LogRecord::GetName()
    {
        return m_Name;
    };

    JeLog::Level LogRecord::GetLevel()
    {
        return m_Level;
    };

    void LogRecord::SetName(char *name)
    {
        // assert if name is not char* type
        m_Name = name;
    };

    void LogRecord::SetLevel(JeLog::Level level)
    {
        // assert if level is not int type
        m_Level = level;
    };

    char *LogRecord::GetMessage()
    {
        return m_Msg;
    };

    void LogRecord::SetMessage(char *message)
    {
        // assert if message is not char* type
        m_Msg = message;
    };

    char *LogRecord::GetFunction()
    {
        return m_SrcInfo.m_FuncName;
    };

    void LogRecord::SetFunction(char *function)
    {
        // assert if function is not char* type
        m_SrcInfo.m_FuncName = function;
    };

    char *LogRecord::GetFileName()
    {
        return m_SrcInfo.m_FileName;
    };

    void LogRecord::SetFileName(char *filename)
    {
        m_SrcInfo.m_FileName = filename;
    };

    int LogRecord::GetLineNo()
    {
        return m_SrcInfo.m_Line;
    };

    void LogRecord::SetLineNo(int line)
    {
        m_SrcInfo.m_Line = line;
    };

    uint32_t LogRecord::GetThreadID()
    {
        return m_ThdInfo.m_ThreadID;
    };

    void LogRecord::SetThreadID(uint32_t threadID)
    {
        m_ThdInfo.m_ThreadID = threadID;
    };

    char *LogRecord::GetThreadName()
    {
        return m_ThdInfo.m_ThreadName;
    };

    void LogRecord::SetThreadName(char *threadName)
    {
        m_ThdInfo.m_ThreadName = threadName;
    };

    JeLog::Time *LogRecord::GetCreationTime()
    {
        return m_CreatedTime;
    };

    void LogRecord::SetCreationTime(JeLog::Time *createdTime)
    {
        m_CreatedTime = createdTime;
    };

    // #define JE_LOG_LOG_RECORD
    // #endif // JE_LOG_LOG_RECORD

#pragma endregion // LogRecord

}; // namespace JeLog

#pragma endregion // Definitions
