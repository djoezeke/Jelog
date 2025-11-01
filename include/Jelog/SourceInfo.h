#pragma once

#include <string>

// O------------------------------------------------------------------------------O
// | Je-Log Declarations                                                          |
// O------------------------------------------------------------------------------O
#pragma region Declarations

namespace JeLog
{

#pragma region SourceInfo
#if !defined(JE_LOG_SOURCE_INFO)

    /////////////////////////////////////////////////////////////////////////
    ///  \brief A SourceInfo instance represents Source Location Infomation of Log.
    ///
    /// SourceInfo instances are created every time something is logged. They
    /// contain Location information pertinent to the event being logged. The
    /// main information are Filename, Line Number and Function Name, which
    /// are combined to provide Source Location Information of Logs.
    ///
    /////////////////////////////////////////////////////////////////////////
    struct SourceInfo
    {
    public:                     // Data
        std::string m_FileName; // File Name of Location of Log.
        size_t m_Line;          // Line Number of Location of Log.
        std::string m_FuncName; // Function Name of Location of Log.

    public: // Methods
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize an empty Log Source Info.
        ///
        /////////////////////////////////////////////////////////////////////////
        SourceInfo();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize a Log Source Info with Interesting information.
        ///
        /// \param filename  File Name of Location of Log.
        /// \param line Line Number of Location of Log.
        /// \param funcname Function Name of Location of Log.
        ///
        /////////////////////////////////////////////////////////////////////////
        SourceInfo(std::string filename, size_t line, std::string funcname);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Check if a Log Source Info is Unknown.
        ///
        /// \return true if Source Info is Unknown.
        ///
        /////////////////////////////////////////////////////////////////////////
        bool UnKnown() const;
    };

#define JE_LOG_SOURCE_INFO
#endif // JE_LOG_SOURCE_INFO

#pragma endregion // SourceInfo

}; // namespace JeLog

// O------------------------------------------------------------------------------O
// | Je-Log Definitions                                                          |
// O------------------------------------------------------------------------------O
#pragma region Definitions
namespace JeLog
{
#pragma region SourceInfo

    // #if !defined(JE_LOG_SOURCE_INFO)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::SourceInfo
    //-----------------------------------------------------------------------------
    // - SourceInfo()
    // - UnKnown()
    //-----------------------------------------------------------------------------

    SourceInfo::SourceInfo()
    {
        m_FileName = "";
        m_Line = 0;
        m_FuncName = "";
    };

    SourceInfo::SourceInfo(std::string filename, size_t line, std::string funcname)
    {
        m_FileName = filename;
        m_Line = line;
        m_FuncName = funcname;
    };

    bool SourceInfo::UnKnown() const
    {
        // First Time Using the Tenary Operator. [01/04/2025] [03:58 PM]
        bool isEmpty = m_FileName == "" || m_FuncName == "" || m_Line == 0 ? true : false;
        return isEmpty;
    };

    // #define JE_LOG_SOURCE_INFO
    // #endif // JE_LOG_SOURCE_INFO

#pragma endregion // SourceInfo

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