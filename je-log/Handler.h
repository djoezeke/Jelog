#pragma once

#include "Formatter.h"
#include "Filterer.h"

#pragma region Declarations

namespace JeLog
{

#pragma region Handler
#if !defined(JE_LOG_HANDLER)

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Handler instances dispatch logging events to specific destinations.
    ///
    /// The base handler class. Acts as a placeholder which defines the Handler
    /// interface. Handlers can optionally use Formatter instances to format
    /// records as desired. By default, no formatter is specified; in this case,
    /// the 'raw' message as determined by record.message is logged.
    ///
    /////////////////////////////////////////////////////////////////////////
    class Handler
    {
    public: // Data
        // "class" : "jeLog::StreamHandler"

        char *m_Name;
        JeLog::Formatter *m_Formatter;
        JeLog::Filterer m_Filterer;

        // sink log level - default is all
        Level m_Level = Level::trace;

    public: // Methods
        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initializes the instance - basically setting the formatter to None
        /// and the filter list to empty.
        ///
        /////////////////////////////////////////////////////////////////////////
        // Handler();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initializes the instance - basically setting the formatter to None
        /// and the filter list to empty.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual ~Handler() = default;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Return `Name` of handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *Name();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Set the `name` of this Handler.
        /// Level must be an string.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetName(char *name);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Return `Level` of handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::Level Level();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Set the logging `level` of this Handler.
        /// Level must be an int.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetLevel(JeLog::Level level);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Return `Pattern` Used  to Format the handler Logs.
        ///
        /////////////////////////////////////////////////////////////////////////
        // char *Pattern();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Return `true` if handler's formatter is not NULL.
        ///
        /////////////////////////////////////////////////////////////////////////
        bool HasFormatter();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Return `true` if handler's filter is not NULL.
        ///
        /////////////////////////////////////////////////////////////////////////
        bool HasFilterer();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Set the logging `level` of this Handler.
        /// Level must be an int.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void Log(JeLog::LogRecord &logRecord) = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Ensure all logging output has been flushed.
        ///
        /// This version does nothing and is intended to be implemented by
        /// subclasses.
        ///
        /////////////////////////////////////////////////////////////////////////
        // virtual void Flush() = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Set the formatting Pattern for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        // virtual void SetPattern(const std::string &) = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Set the formatter for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFormatter(JeLog::Formatter *formatter);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Set the Filterer for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFilterer(JeLog::Filterer &filterer);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Get the formatter for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void GetFormatter();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Get the Filterer for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void GetFilterer();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Conditionally emit the specified logging record.
        ///
        /// would call log upon Handle
        ///
        /// Emission depends on filters which may have been added to the handler.
        /// Wrap the actual emission of the record with acquisition/release of
        /// the I/O thread lock.
        ///
        /// Returns an instance of the log record that was emitted
        /// if it passed all filters, otherwise a false value is returned.
        ///
        /// \param logRecord
        ///
        /////////////////////////////////////////////////////////////////////////
        // virtual void Handle(LogRecord &logRecord) = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Format the specified record.
        ///
        /// If a formatter is set, use it. Otherwise, use the default formatter
        /// for the module.
        /// format using the pattern seted.
        /// \param logRecord
        ///
        /////////////////////////////////////////////////////////////////////////
        // void Format(LogRecord &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Acquire a thread lock for serializing access to the underlying I/O.
        ///
        /////////////////////////////////////////////////////////////////////////
        // void CreateLock();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Acquire the I/O thread lock.
        ///
        /////////////////////////////////////////////////////////////////////////
        // void Acquire();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Release the I/O thread lock.
        ///
        /////////////////////////////////////////////////////////////////////////
        // void Release();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Do whatever it takes to actually log the specified logging record.
        ///
        /// This version is intended to be implemented by subclasses and so
        /// raises a NotImplementedError.
        ///
        /// \param logRecord
        ///
        /////////////////////////////////////////////////////////////////////////
        // virtual void Emit(LogRecord);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Tidy up any resources used by the handler.
        ///
        /// This version removes the handler from an internal map of handlers,
        /// _handlers, which is used for handler lookup by name. Subclasses
        /// should ensure that this gets called from overridden close()
        /// methods.
        ///
        /////////////////////////////////////////////////////////////////////////
        // virtual void Close();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Handle errors which occur during an emit() call.
        ///
        /// This method should be called from handlers when an exception is
        /// encountered during an emit() call. If raiseExceptions is false,
        /// exceptions get silently ignored. This is what is mostly wanted
        /// for a logging system - most users will not care about errors in
        /// the logging system, they are more interested in application errors.
        /// You could, however, replace this with a custom handler if you wish.
        /// The record which was being processed is passed in to this method.
        ///
        /////////////////////////////////////////////////////////////////////////
        // void HandleError(LogRecord);
    };

#define JE_LOG_HANDLER
#endif // JE_LOG_HANDLER

#pragma endregion // Handler

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region Handler
    // #if !defined(JE_LOG_HANDLER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Handler
    //-----------------------------------------------------------------------------
    // - Handler()
    // - ~Handler()
    // - GetName()
    // - SetName()
    // - CreateLock()
    // - Acquire()
    // - Release()
    // - SetLevel()
    // - Format()
    // - Emit()
    // - Handle()
    // - SetFormatter()
    // - Flush()
    // - Close()
    // - HandleError()
    //-----------------------------------------------------------------------------

    Handler::Handler()
    {
        m_Formatter = 0;
        // m_Filterer = 0;
    };

    // Handler::~Handler() {};

    char *Handler::Name()
    {
        return m_Name;
    };

    // bool Handler::formatter()
    // {
    //     bool hasFormatter = false;

    //     if (&m_Formatter != NULL)
    //     {
    //         hasFormatter = true;
    //     }

    //     return hasFormatter;
    // };

    // #define JE_LOG_HANDLER
    // #endif // JE_LOG_HANDLER

#pragma endregion // Handler

} // namespace JeLog

#pragma endregion // Definitions
