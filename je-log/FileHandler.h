#pragma once

#include "Handler.h"

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
