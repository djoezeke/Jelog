#pragma once

#include <Jelog/Handler.h>

#pragma region Declarations

namespace JeLog
{

#pragma region FileHandler
#if !defined(JE_LOG_LOG_FILE_HANDLER)

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief A handler class which writes formatted logging records to disk files.
    ///
    /////////////////////////////////////////////////////////////////////////
    class FileHandler : public Handler
    {
    private:
        char *m_FileName;

    private:
        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Open the current base file with the (original) mode and encoding.
        /// Return the resulting stream.
        ///
        /////////////////////////////////////////////////////////////////////////
        void Open();

    public:
        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Open the specified file and use it as the stream for logging.
        ///
        /// \param filename
        ///
        /////////////////////////////////////////////////////////////////////////
        FileHandler(char *filename);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Open the specified file and use it as the stream for logging.
        ///
        /// \param level
        /// \param filename
        ///
        /////////////////////////////////////////////////////////////////////////
        FileHandler();

        ~FileHandler();

        virtual void Log(LogRecord &) override;
    };

#define JE_LOG_LOG_FILE_HANDLER
#endif // JE_LOG_LOG_FILE_HANDLER

#pragma endregion // FileHandler

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region FileHandler
    // #if !defined(JE_LOG_LOG_FILE_HANDLER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::FileHandler
    //-----------------------------------------------------------------------------
    // - FileHandler()
    // - ~FileHandler()
    // - Handle()
    //-----------------------------------------------------------------------------

    FileHandler::FileHandler(char *filename)
    {
        m_Name = "FileHandler";
        m_FileName = filename;
        // TextFormatter textFormatter;
        // m_Formatter = textFormatter;
    };

    FileHandler::FileHandler()
    {
        m_Name = "FileHandler";
        // m_Level = 1;
        m_FileName = "Je-Log.log";
        // TextFormatter textFormatter;
        // m_Formatter = textFormatter;
    };

    FileHandler::~FileHandler() {};

    void FileHandler::Log(LogRecord &logRecord) {};

    // #define JE_LOG_LOG_FILE_HANDLER
    // #endif // JE_LOG_LOG_FILE_HANDLER

#pragma endregion // FileHandler

} // namespace JeLog

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