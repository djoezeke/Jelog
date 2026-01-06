#pragma once

#include <Jelog/Filterer.h>
#include <Jelog/Formatter.h>
#include <Jelog/Level.h>
#include <string>

#pragma region Declarations

namespace JeLog {

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
class Handler {
   public:  // Data
    // Use std::string for automatic memory management instead of raw char*
    std::string m_Name;
    // Formatter is still a non-owning pointer; document ownership in SetFormatter
    JeLog::Formatter *m_Formatter;
    JeLog::Filterer m_Filterer;

    // sink log level - default is all
    Level m_Level = Level::trace;

   public:  // Methods
    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Initializes the instance - basically setting the formatter to None
    /// and the filter list to empty.
    ///
    /////////////////////////////////////////////////////////////////////////
    Handler();

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
    // Return the name of the handler as a std::string reference
    const std::string &Name() const;

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Set the `name` of this Handler.
    /// Level must be an string.
    ///
    /////////////////////////////////////////////////////////////////////////
    // Set the name of this handler. Copies the provided string.
    void SetName(const std::string &name);

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
#endif  // JE_LOG_HANDLER

#pragma endregion  // Handler

}  // namespace JeLog

#pragma endregion  // Declarations

#pragma region Definitions

namespace JeLog {

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

Handler::Handler() {
    m_Formatter = nullptr;  // explicit null
    m_Name.clear();
    // m_Filterer default constructed
};

// Handler::~Handler() {};

const std::string &Handler::Name() const { return m_Name; };

void Handler::SetName(const std::string &name) { m_Name = name; };

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

#pragma endregion  // Handler

}  // namespace JeLog

#pragma endregion  // Definitions

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