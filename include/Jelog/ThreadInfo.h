#pragma once

#include <cstdint>
#include <string>

// O------------------------------------------------------------------------------O
// | Je-Log Declarations                                                          |
// O------------------------------------------------------------------------------O
#pragma region Declarations

namespace JeLog
{

#pragma region ThreadInfo
#if !defined(JE_LOG_THREAD_INFO)

    /////////////////////////////////////////////////////////////////////////
    ///  \brief A ThreadInfo instance represents Thread Infomation of Log.
    ///
    /// SourceInfo instances are created every time something is logged. They
    /// contain Thread information pertinent to the event being logged. The
    /// main information are Thread ID and Thread Name, which
    /// are combined to provide Thread Information of Logs.
    ///
    /////////////////////////////////////////////////////////////////////////
    struct ThreadInfo
    {
    public:                       // Data
        uint32_t m_ThreadID;      //  Thread ID of Location of Log.
        std::string m_ThreadName; // Thread Name of Location of Log.

    public: // Methods
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize an empty Log Thread Info.
        ///
        /////////////////////////////////////////////////////////////////////////
        ThreadInfo();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize a Log Thread Info with Interesting information.
        ///
        /// \param threadID  Thread ID of Location of Log.
        /// \param threadName Thread Name of Location of Log.
        ///
        /////////////////////////////////////////////////////////////////////////
        ThreadInfo(uint32_t threadID, std::string threadName);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Check if a Log Thread ID is Unknown.
        ///
        /// \return true if Thread ID is Unknown.
        ///
        /////////////////////////////////////////////////////////////////////////
        bool UnKnown() const;
    };

#define JE_LOG_THREAD_INFO
#endif // JE_LOG_THREAD_INFO

#pragma endregion // ThreadInfo

}; // namespace JeLog

// O------------------------------------------------------------------------------O
// | Je-Log Definitions                                                          |
// O------------------------------------------------------------------------------O
#pragma region Definitions
namespace JeLog
{
#pragma region ThreadInfo

    // #if !defined(JE_LOG_THREAD_INFO)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::ThreadInfo
    //-----------------------------------------------------------------------------
    // - ThreadInfo()
    // - UnKnown()
    //-----------------------------------------------------------------------------

    ThreadInfo::ThreadInfo()
    {
        m_ThreadID = 0;
        m_ThreadName = "";
    };

    ThreadInfo::ThreadInfo(uint32_t threadID, std::string threadName)
    {
        m_ThreadID = threadID;
        m_ThreadName = threadName;
    };

    bool ThreadInfo::UnKnown() const
    {
        bool isEmpty = m_ThreadID == 0 ? true : false;
        return isEmpty;
    };

    // #define JE_LOG_THREAD_INFO
    // #endif // JE_LOG_THREAD_INFO

#pragma endregion // ThreadInfo

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