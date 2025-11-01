
#pragma once

#include <string>

#include <Jelog/JeTime.h>
#include <Jelog/Level.h>
#include <Jelog/SourceInfo.h>
#include <Jelog/ThreadInfo.h>

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
        std::string m_Name;
        std::string m_Msg;
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
        /// \param level
        /// \param sourceInfo
        /// \param creationTime
        /// \param message
        /// \param threadInfo
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord(std::string name, Level level, SourceInfo sourceInfo, Time *creationTime, char *message, ThreadInfo threadInfo);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        std::string GetName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name for this LogRecord.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetName(std::string name);

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
        std::string GetMessage();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the message for this LogRecord.
        ///
        /// \param message
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetMessage(std::string message);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name of the Function in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        std::string GetFunction();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name of the Function in which this LogRecord was Created.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFunction(std::string name);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the File Name in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        std::string GetFileName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the File Name in which this LogRecord was Created.
        ///
        /// \param filename
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFileName(std::string filename);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Line Number for which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        size_t GetLineNo();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Line Number for which this LogRecord was Created.
        ///
        /// \param lineno
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetLineNo(size_t lineno);

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
        std::string  GetThreadName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Thread Name for this LogRecord.
        ///
        /// \param threadName
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetThreadName(std::string threadName);

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

    LogRecord::LogRecord(std::string name, Level level, SourceInfo sourceInfo, Time *creationTime, char *message, ThreadInfo threadInfo)
    {
        m_Name = name;
        m_Msg = message;
        m_Level = level;
        m_SrcInfo = sourceInfo;
        m_CreatedTime = creationTime;
        m_ThdInfo = threadInfo;
    };

    std::string LogRecord::GetName()
    {
        return m_Name;
    };

    JeLog::Level LogRecord::GetLevel()
    {
        return m_Level;
    };

    void LogRecord::SetName(std::string name)
    {
        m_Name = name;
    };

    void LogRecord::SetLevel(JeLog::Level level)
    {
        m_Level = level;
    };

    std::string LogRecord::GetMessage()
    {
        return m_Msg;
    };

    void LogRecord::SetMessage(std::string message)
    {
        m_Msg = message;
    };

    std::string LogRecord::GetFunction()
    {
        return m_SrcInfo.m_FuncName;
    };

    void LogRecord::SetFunction(std::string function)
    {
        m_SrcInfo.m_FuncName = function;
    };

    std::string LogRecord::GetFileName()
    {
        return m_SrcInfo.m_FileName;
    };

    void LogRecord::SetFileName(std::string filename)
    {
        m_SrcInfo.m_FileName = filename;
    };

    size_t LogRecord::GetLineNo()
    {
        return m_SrcInfo.m_Line;
    };

    void LogRecord::SetLineNo(size_t line)
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

    std::string LogRecord::GetThreadName()
    {
        return m_ThdInfo.m_ThreadName;
    };

    void LogRecord::SetThreadName(std::string threadName)
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

/**
 * LICENSE: MIT License
 *
 * Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */