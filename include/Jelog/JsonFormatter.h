#pragma once

// #include <algorithm>
// #include <mutex>
// #include <thread>

#include <fstream>
#include <iostream>

#include <Jelog/Formatter.h>

#pragma region Declarations

namespace JeLog
{

#pragma region JsonFormatter
#if !defined(JE_LOG_JSON_FORMATTER)

    /////////////////////////////////////////////////////////////////////////
    ///  \brief  Check if Value is in Container.
    /// Formatter instances are used to convert a LogRecord to text.
    ///
    /// Formatters need to know how a LogRecord is constructed. They are
    /// responsible for converting a LogRecord to (usually) a string which can
    /// be interpreted by either a human or an external system. The base Formatter
    /// allows a formatting string to be specified. If none is supplied, the
    /// style-dependent default value, "%(message)s", "{message}", or
    /// "${message}", is used.
    ///
    /////////////////////////////////////////////////////////////////////////
    class JsonFormatter : JeLog::Formatter
    {

    private:
        std::ofstream m_OutputStream;
        char *m_Filename;
        char *m_MessageFormat;
        char *m_TimeFormat;
        int m_ProfileCount;
        // std::mutex m_lock;

    private: // Methods
        void BeginSession();

        void EndSession();

        void WriteHeader();

        void WriteFooter();

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the formatter with specified format strings.
        ///
        /// \param messageFormat
        /// \param timeFormat
        ///
        /////////////////////////////////////////////////////////////////////////
        JsonFormatter(char *messageFormat, char *timeFormat);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the formatter with unknown format strings.
        ///
        /////////////////////////////////////////////////////////////////////////
        JsonFormatter();

        ~JsonFormatter();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Format the specified record as text.
        ///
        /// The record's attribute dictionary is used as the operand to a
        /// string formatting operation which yields the returned string.
        /// Before formatting the dictionary, a couple of preparatory steps
        /// are carried out. The message attribute of the record is computed
        /// using LogRecord.getMessage(). If the formatting string uses the
        /// time (as determined by a call to usesTime(), formatTime() is
        /// called to format the event time. If there is exception information,
        /// it is formatted using formatException() and appended to the message.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::LogRecord Format(JeLog::LogRecord &logRecord) override;

        void SetPattern(char *messageFormat, char *timeFormat) override;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Return the creation time of the specified LogRecord as formatted text.
        ///
        /// This method should be called from format() by a formatter which
        /// wants to make use of a formatted time. This method can be overridden
        /// in formatters to provide for any specific requirement, but the
        /// basic behaviour is as follows: if datefmt (a string) is specified,
        /// it is used with time.strftime() to format the creation time of the
        /// record. Otherwise, an ISO8601-like (or RFC 3339-like) format is used.
        /// The resulting string is returned. This function uses a user-configurable
        /// function to convert the creation time to a tuple. By default,
        /// time.localtime() is used; to change this for a particular formatter
        /// instance, set the 'converter' attribute to a function with the same
        /// signature as time.localtime() or time.gmtime(). To change it for all
        /// formatters, for example if you want all logging times to be shown in GMT,
        /// set the 'converter' attribute in the Formatter class.
        ///
        /////////////////////////////////////////////////////////////////////////
        void TimeFormat(JeLog::LogRecord &logRecord, char *format);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        void MessageFormat(JeLog::LogRecord &logRecord, char *format);
    };

#define JE_LOG_JSON_FORMATTER
#endif // JE_LOG_JSON_FORMATTER

#pragma endregion // JsonFormatter

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region JsonFormatter

    // #if !defined(JE_LOG_JSON_FORMATTER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::JsonFormatter
    //-----------------------------------------------------------------------------
    // - JsonFormatter()
    // - ~JsonFormatter()
    // - SetPattern()
    // - Format()
    // - TimeFormat()
    // - MessageFormat()
    // - BeginSession()
    // - EndSession()
    // - WriteHeader()
    // - WriteFooter()
    //-----------------------------------------------------------------------------

    JsonFormatter::JsonFormatter() {};

    JsonFormatter::~JsonFormatter() {};

    LogRecord JsonFormatter::Format(LogRecord &logRecord)
    {
        // std::lock_guard<std::mutex> lock(m_lock);

        m_OutputStream << "{";
        m_OutputStream << "\"Name\":\"" << logRecord.GetName() << "\",";
        m_OutputStream << "\"Level\":\"" << logRecord.GetLevel() << "\",";
        m_OutputStream << "\"Message\":\"" << logRecord.GetMessage() << "\",";
        m_OutputStream << "\"LineNo\":\"" << logRecord.GetLineNo() << "\",";
        m_OutputStream << "\"Function\":\"" << logRecord.GetFunction() << "\",";
        m_OutputStream << "\"FileName\":\"" << logRecord.GetFileName() << "\",";
        m_OutputStream << "\"ThreadID\":\"" << logRecord.GetThreadID() << "\",";
        m_OutputStream << "\"ThreadName\":\"" << logRecord.GetThreadName() << "\",";
        m_OutputStream << "\"CreationTime\":\"" << logRecord.GetCreationTime()->MilliSecond();
        m_OutputStream << "}\n";

        m_OutputStream.flush();
        return logRecord;
    };

    void JsonFormatter::TimeFormat(JeLog::LogRecord &logRecord, char *format = "")
    {
        std::cout << "format: " << format << " logrecord [Name] : " << logRecord.GetName() << std::endl;
    };

    void JsonFormatter::MessageFormat(JeLog::LogRecord &logRecord, char *format = "")
    {
        std::cout << "format: " << format << " logrecord [Name] : " << logRecord.GetName() << std::endl;
    };

    void JsonFormatter::BeginSession()
    {
        m_OutputStream.open(m_Filename);
        WriteHeader();
    };

    void JsonFormatter::EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        m_ProfileCount = 0;
    };

    void JsonFormatter::WriteHeader() {
        // m_OutputStream << "{[";
        // m_OutputStream.flush();
    };

    void JsonFormatter::WriteFooter() {
        //     m_OutputStream << "]}";
        //     m_OutputStream.flush();
    };

    // #define JE_LOG_JSON_FORMATTER
    // #endif // JE_LOG_JSON_FORMATTER

#pragma endregion // JsonFormatter

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