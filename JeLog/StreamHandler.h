#pragma once

#include "Handler.h"

#pragma region Declarations

namespace JeLog
{

#pragma region StreamHandler
#if !defined(JE_LOG_LOG_STREAM_HANDLER)

    /////////////////////////////////////////////////////////////////////////
    ///  \brief  Check if Value is in Container.
    ///
    /// A LogRecord instance represents an event being logged.
    ///
    /// LogRecord instances are created every time something is logged. They
    /// contain all the information pertinent to the event being logged. The
    /// main information passed in is in msg and args, which are combined
    /// using str(msg) % args to create the message field of the record. The
    /// record also includes information such as when the record was created,
    /// the source line where the logging call was made, and any exception
    /// information to be logged.
    ///
    /////////////////////////////////////////////////////////////////////////
    class StreamHandler : public Handler
    {
    private:
        char m_Terminator;

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the handler.
        ///
        /// If stream is not specified, sys.stderr is used.
        ///
        /// \param terminator
        ///
        /////////////////////////////////////////////////////////////////////////
        StreamHandler(char);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the handler.
        ///
        /// If stream is not specified, sys.stderr is used.
        ///
        /////////////////////////////////////////////////////////////////////////
        StreamHandler();

        ~StreamHandler();

        virtual void Log(LogRecord &) override;
    };

#define JE_LOG_LOG_STREAM_HANDLER
#endif // JE_LOG_LOG_STREAM_HANDLER

#pragma endregion // StreamHandler

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region StreamHandler
    // #if !defined(JE_LOG_LOG_STREAM_HANDLER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::StreamHandler
    //-----------------------------------------------------------------------------
    // - StreamHandler()
    // - ~StreamHandler()
    // - Handle()
    //-----------------------------------------------------------------------------

    StreamHandler::StreamHandler(char terminator)
    {
        m_Terminator = terminator;
        // TextFormatter textFormatter;
        // m_Formatter = textFormatter;
    };

    StreamHandler::StreamHandler()
    {
        m_Terminator = '\n';
        // TextFormatter textFormatter;
        // m_Formatter = textFormatter;
    };

    StreamHandler::~StreamHandler() {};

    void StreamHandler::Log(LogRecord &logRecord)
    {
        // logRecord = m_Formatter.Format(logRecord);
        // Filter filter;
        // m_Filterer.AddFilter(filter);
        // logRecord = m_Filterer.filter(filter, logRecord);

        std::cout << logRecord.Message();
    };

    // #define JE_LOG_LOG_STREAM_HANDLER
    // #endif // JE_LOG_LOG_STREAM_HANDLER

#pragma endregion // StreamHandler

} // namespace JeLog

#pragma endregion // Definitions
