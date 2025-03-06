#pragma once

#include "je-log/Level.h"
#include "je-log/Formatter.h"
#include "je-log/Handler.h"
#include "je-log/SourceInfo.h"
#include "je-log/LogRecord.h"
#include "je-log/StreamHandler.h"
#include "je-log/StringFormatter.h"
#include "je-log/Filter.h"
#include "je-log/Filterer.h"
#include "je-log/JeTime.h"
#include "je-log/Logger.h"

#pragma region Declarations

namespace JeLog
{

#pragma region Basics

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Do basic configuration for the logging system.
    ///
    /// This function does nothing if the Default logger already has handlers
    /// configured, unless the keyword argument *force* is set to ``True``.
    /// It is a convenience method intended for use by simple scripts
    /// to do one-shot configuration of the logging package.
    ///
    /// The default behaviour is to create a StreamHandler which writes to
    /// sys.stderr, set a formatter using the BASIC_FORMAT format string, and
    /// add the handler to the Default logger.
    ///
    /// A number of optional keyword arguments may be specified, which can alter
    /// the default behaviour.
    ///
    /// filename  Specifies that a FileHandler be created, using the specified
    ///          filename, rather than a StreamHandler.
    /// filemode  Specifies the mode to open the file, if filename is specified
    ///          (if filemode is unspecified, it defaults to 'a').
    /// format    Use the specified format string for the handler.
    /// datefmt   Use the specified date/time format.
    /// style     If a format string is specified, use this to specify the
    ///         type of format string (possible values '%', '{', '$', for
    ///          %-formatting, :meth:`str.format` and :class:`string.Template`
    ///          - defaults to '%').
    /// level     Set the Default logger level to the specified level.
    /// stream    Use the specified stream to initialize the StreamHandler. Note
    ///          that this argument is incompatible with 'filename' - if both
    ///          are present, 'stream' is ignored.
    /// handlers  If specified, this should be an iterable of already created
    ///          handlers, which will be added to the Default logger. Any handler
    ///         in the list which does not have a formatter assigned will be
    ///         assigned the formatter created in this function.
    /// force     If this keyword  is specified as true, any existing handlers
    ///          attached to the Default logger are removed and closed, before
    ///          carrying out the configuration as specified by the other
    ///          arguments.
    /// encoding  If specified together with a filename, this encoding is passed to
    ///         the created FileHandler, causing it to be used when the file is
    ///         opened.
    /// errors    If specified together with a filename, this value is passed to the
    ///          created FileHandler, causing it to be used when the file is
    ///          opened in text mode. If not specified, the default value is
    ///          `backslashreplace`.
    ///
    /// Note that you could specify a stream created using open(filename, mode)
    /// rather than passing the filename and mode in. However, it should be
    /// remembered that StreamHandler does not close its stream (since it may be
    /// using sys.stdout or sys.stderr), whereas FileHandler closes its stream
    /// when the handler is closed.
    ///
    /// .. versionchanged:: 3.2
    ///   Added the ``style`` parameter.
    ///
    /// .. versionchanged:: 3.3
    ///   Added the ``handlers`` parameter. A ``ValueError`` is now thrown for
    ///   incompatible arguments (e.g. ``handlers`` specified together with
    ///   ``filename``/``filemode``, or ``filename``/``filemode`` specified
    ///   together with ``stream``, or ``handlers`` specified together with
    ///   ``stream``.
    ///
    /// .. versionchanged:: 3.8
    ///   Added the ``force`` parameter.
    ///
    /// .. versionchanged:: 3.9
    ///   Added the ``encoding`` and ``errors`` parameters.
    ///
    /////////////////////////////////////////////////////////////////////////
    void BasicConfig(...);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Return a logger with the specified name, creating it if necessary.
    ///
    /// If no name is specified, return the Default logger.
    ///
    /////////////////////////////////////////////////////////////////////////
    Logger GetLogger(char *name);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Associate 'levelName' with 'level'.
    ///
    /// This is used when converting levels to text during message formatting.
    ///
    /////////////////////////////////////////////////////////////////////////
    void AddLevelName(JeLog::Level level, char *levelName);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Make a Log Record.
    ///
    /// Make a LogRecord whose attributes are defined by the specified dictionary,
    /// This function is useful for converting a logging event received over
    /// a socket connection (which is sent as a dictionary) into a LogRecord
    /// instance.
    ///
    /////////////////////////////////////////////////////////////////////////
    LogRecord MakeLogRecord(char *name, JeLog::Level level, JeLog::SourceInfo srcLoc,
                            JeLog::Time creationTime, char *message, int threadID);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Return the textual or numeric representation of logging level 'level'.
    ///
    /// If the level is one of the predefined levels (CRITICAL, ERROR, WARNING,
    /// INFO, DEBUG) then you get the corresponding string. If you have
    /// associated levels with names using addLevelName then the name you have
    /// associated with 'level' is returned.
    ///
    /// If a numeric value corresponding to one of the defined levels is passed
    /// in, the corresponding string representation is returned.
    ///
    /// If a string representation of the level is passed in, the corresponding
    /// numeric value is returned.
    ///
    /// If no matching numeric or string value is passed in, the string
    /// 'Level %s' % level is returned.
    ///
    /////////////////////////////////////////////////////////////////////////
    char *GetLevelName(JeLog::Level level);

    /////////// Log

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with default severity.
    ///
    /// \param message message to Log.
    ///
    /// logger.Log("Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Log(T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with default severity.
    ///
    /// \param format log format.
    /// \param ...args  Argument to Log.
    ///
    /// logger.Log("Hello %s !", name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Log(char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "level" severity.
    ///
    /// \param level severity of Log.
    /// \param message message to Log.
    ///
    /// logger.Log(Level::trace,"Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Log(JeLog::Level level, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '...args' with "level" severity.
    ///
    /// \param level severity of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Log(Level::trace,"Hello %s !",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Log(JeLog::Level level, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "level" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param level severity of Log.
    /// \param message message to Log.
    ///
    /// logger.Log(loc,Level::trace,"Hello Zeke!");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Log(SourceInfo loc, JeLog::Level level, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "level" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param level severity of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Log(loc,Level::trace,"Hello %s!",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Log(SourceInfo loc, JeLog::Level level, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "level" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param level severity of Log.
    /// \param message message to Log.
    ///
    /// logger.Log(time,loc,Level::trace,"Hello Zeke");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Log(clock::time_point log_time, SourceInfo loc, JeLog::Level level, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "level" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param level severity of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Log(time,loc,Level::trace,"Hello %s",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Log(clock::time_point log_time, SourceInfo loc, JeLog::Level level, char *format, Args... args);

    ////// Trace

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "TRACE" severity.
    ///
    /// \param message message to Log.
    ///
    /// logger.Trace("Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Trace(T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "TRACE" severity.
    ///
    /// \param format log format.
    /// \param ...args  Argument to Log.
    ///
    /// logger.Trace("Hello %s !", name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Trace(char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "TRACE" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Trace(loc,"Hello Zeke!");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Trace(SourceInfo loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "TRACE" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Trace(loc,"Hello %s!",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Trace(SourceInfo loc, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "TRACE" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Trace(time,loc,"Hello Zeke");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Trace(clock::time_point log_time, SourceInfo loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "TRACE" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Trace(time,loc,"Hello %s",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Trace(clock::time_point log_time, SourceInfo loc, char *format, Args... args);

#pragma endregion // Basics

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region Basics

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::*
    //-----------------------------------------------------------------------------
    // - BasicConfig()
    // - GetLogger()
    // - AddLevelName()
    // - GetLevelName()
    // - MakeLogRecord()
    // - Log()
    // - Trace()
    // - Error()
    // - Warning()
    // - Critical()
    // - Info()
    // - Debug()
    //-----------------------------------------------------------------------------

    void BasicConfig(...) {};

    Logger GetLogger(char *name) {};

    LogRecord MakeLogRecord(char *name, JeLog::Level level, JeLog::SourceInfo srcLoc,
                            JeLog::Time *creationTime, char *message, int threadID) {

    };

    void AddLevelName(JeLog::Level level, char *levelName) {};

    char *GetLevelName(JeLog::Level level) {};

    /////////// Log

    template <typename T>
    LogRecord Log(T message) {};

    template <typename... Args>
    LogRecord Log(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Log(JeLog::Level level, T message) {};

    template <typename... Args>
    LogRecord Log(JeLog::Level level, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Log(SourceInfo loc, JeLog::Level level, T message) {};

    template <typename... Args>
    LogRecord Log(SourceInfo loc, JeLog::Level level, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Log(clock::time_point log_time, SourceInfo loc, JeLog::Level level, T message) {};

    template <typename... Args>
    LogRecord Log(clock::time_point log_time, SourceInfo loc, JeLog::Level level, char *format, Args... args) {};

    ////// Trace

    template <typename T>
    LogRecord Trace(T message) {};

    template <typename... Args>
    LogRecord Trace(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Trace(SourceInfo loc, T message) {};

    template <typename... Args>
    LogRecord Trace(SourceInfo loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Trace(clock::time_point log_time, SourceInfo loc, T message) {};

    template <typename... Args>
    LogRecord Trace(clock::time_point log_time, SourceInfo loc, char *format, Args... args) {};

#pragma endregion // Basics

} // namespace JeLog

#pragma endregion // Definitions
