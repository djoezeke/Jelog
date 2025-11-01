#pragma once

#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

#include <Jelog/Formatter.h>
#include <Jelog/Handler.h>
#include <Jelog/Level.h>
#include <Jelog/LogRecord.h>
#include <Jelog/StreamHandler.h>

#pragma region Declarations

namespace JeLog
{

#pragma region Logger
#if !defined(JE_LOG_LOG_LOGGER)

    /////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Instances of the Logger class represent a single logging channel. A
    /// "logging channel" indicates an area of an application. Exactly how an
    /// "area" is defined is up to the application developer. Since an
    /// application can have any number of areas, logging channels are identified
    /// by a unique string. Application areas can be nested (e.g. an area
    /// of "input processing" might include sub-areas "read CSV files", "read
    /// XLS files" and "read Gnumeric files"). To cater for this natural nesting,
    /// channel names are organized into a namespace hierarchy where levels are
    /// separated by periods, much like the Java or Python package namespace. So
    /// in the instance given above, channel names might be "input" for the upper
    /// level, and "input.csv", "input.xls" and "input.gnu" for the sub-levels.
    /// There is no arbitrary limit to the depth of nesting.
    ///
    /////////////////////////////////////////////////////////////////////////
    class Logger
    {
    private:
        std::string m_Name;
        JeLog::Level m_Level;
        std::vector<JeLog::Handler> m_Handlers;
        std::mutex m_Lock;
        std::chrono::time_point<std::chrono::high_resolution_clock> Timepoint;
        using clock = std::chrono::steady_clock;

    public:
        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        Logger();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        Logger(T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        Logger(Args &&...args);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        Logger(const Logger &logger);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        Logger(Logger &&logger);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        Logger(T, JeLog::Handler &handler);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        Logger(T, std::vector<JeLog::Handler> &handlers);

        // template <typename It>
        // Logger(std::string name, It begin, It end);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual ~Logger() = default;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        Logger &operator=(Logger logger);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Name the Logger.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetName(std::string name);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Get the current log severity.
        ///
        /////////////////////////////////////////////////////////////////////////
        std::string Name() const;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set a New log severity.
        ///
        /// \param level
        /////////////////////////////////////////////////////////////////////////
        void SetLevel(JeLog::Level level);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Get the current log severity.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::Level Level() const;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Get the current log severity.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::Level GetLevel() const;

        // set formatting for the sinks in this logger.
        // each sink will get a separate instance of the formatter object.
        void SetFormatter(JeLog::Formatter *formatter);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Is this logger enabled for level 'level'?
        /// \return return true logging is enabled for the given level.
        /// \param level
        /////////////////////////////////////////////////////////////////////////
        bool IsEnabledFor(JeLog::Level level);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Is this logger enabled for level 'level'?
        /// \return return Vector Handlers used by Logger
        /////////////////////////////////////////////////////////////////////////
        const std::vector<JeLog::Handler> &Handlers() const;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Is this logger enabled for level 'level'?
        /// \return return Vector Handlers used by Logger
        /// \param level
        /////////////////////////////////////////////////////////////////////////
        std::vector<JeLog::Handler> &Handlers(); // handler ptr

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Low-level logging routine which creates a LogRecord and then calls
        // all the handlers of this logger to handle the record.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        void _Log(JeLog::Time *creationTime, SourceInfo srcInfo, JeLog::Level level, char *format, Args &&...args);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Low-level logging routine which creates a LogRecord and then calls
        // all the handlers of this logger to handle the record.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        void _Log(JeLog::Time *time, JeLog::SourceInfo srcInfo, JeLog::Level level, T message);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Call the handlers for the specified record.
        ///
        /// This method is used for unpickled records received from a socket, as
        /// well as those created locally. Logger-level filtering is applied.
        ///
        /////////////////////////////////////////////////////////////////////////
        void Handle(JeLog::LogRecord &logRecord);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Add the specified handler to this logger.
        ///
        /////////////////////////////////////////////////////////////////////////
        void AddHandler(JeLog::Handler &handler);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Remove the specified handler to this logger.
        ///
        /////////////////////////////////////////////////////////////////////////
        void RemoveHandler(JeLog::Handler &handler);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief See if this logger has any handlers configured.
        ///
        /// Loop through all handlers for this logger and its parents in the
        /// logger hierarchy. Return True if a handler was found, else False.
        /// Stop searching up the hierarchy whenever a logger with the "propagate"
        /// attribute set to zero is found - that will be the last logger which
        /// is checked for the existence of handlers.
        ///
        /////////////////////////////////////////////////////////////////////////
        bool HasHandlers();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief create new logger with same sinks and configuration.
        ///
        /// Loop through all handlers for this logger and its parents in the
        /// logger hierarchy. Return True if a handler was found, else False.
        /// Stop searching up the hierarchy whenever a logger with the "propagate"
        /// attribute set to zero is found - that will be the last logger which
        /// is checked for the existence of handlers.
        ///
        /////////////////////////////////////////////////////////////////////////
        inline Logger Clone(char *);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Make a Log Record from Logger.
        ///
        /// Make a LogRecord whose attributes are defined by `Logger`,
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord Record();

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
        LogRecord Log(T);

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
        LogRecord Log(char *, Args &&...);

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
        LogRecord Log(JeLog::Level, T);

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
        LogRecord Log(JeLog::Level, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "level" severity with source location info.
        ///
        /// \param srcInfo source location of Log.
        /// \param level severity of Log.
        /// \param message message to Log.
        ///
        /// logger.Log(loc,Level::trace,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Log(SourceInfo, JeLog::Level, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "level" severity with source location info.
        ///
        /// \param srcInfo source location of Log.
        /// \param level severity of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Log(loc,Level::trace,"Hello %s!",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Log(SourceInfo, JeLog::Level, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "level" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param srcInfo source location of Log.
        /// \param level severity of Log.
        /// \param message message to Log.
        ///
        /// logger.Log(time,loc,Level::trace,"Hello Zeke");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Log(clock::time_point, SourceInfo, JeLog::Level, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "level" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param srcInfo source location of Log.
        /// \param level severity of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Log(time,loc,Level::trace,"Hello %s",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Log(clock::time_point, SourceInfo, JeLog::Level, char *, Args...);

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
        LogRecord Trace(T);

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
        LogRecord Trace(char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "TRACE" severity with source location info.
        ///
        /// \param srcInfo source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Trace(loc,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Trace(SourceInfo, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "TRACE" severity with source location info.
        ///
        /// \param srcInfo source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Trace(loc,"Hello %s!",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Trace(SourceInfo, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "TRACE" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param srcInfo source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Trace(time,loc,"Hello Zeke");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Trace(clock::time_point, SourceInfo, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "TRACE" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param srcInfo source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Trace(time,loc,"Hello %s",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Trace(clock::time_point, SourceInfo, char *, Args...);

        // return true if backtrace logging is enabled.
        // bool should_backtrace() const { return tracer_.enabled(); }
    };

#define JE_LOG_LOG_LOGGER
#endif // JE_LOG_LOG_LOGGER

#pragma endregion // Logger

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region Logger

    // #if !defined(JE_LOG_LOG_LOGGER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Logger
    //-----------------------------------------------------------------------------
    // - Logger()
    // - ~Logger()
    // - SetLevel()
    // - GetLevel()
    // - IsEnabledFor()
    // - Debug()
    // - Warning()
    // - Error()
    // - Critical()
    // - Log()
    // - _Log()
    // - Handle()
    // - AddHandler()
    // - RemoveHandler()
    // - HasHandlers()
    //-----------------------------------------------------------------------------

    Logger::Logger()
    {

        // m_Name;
        // m_Level;
        // m_Handlers;

        m_Handlers.push_back(StreamHandler());

        // FileHandler fileHandler;
        // m_Handlers.push_back(fileHandler);
    };

    template <typename T>
    Logger::Logger(T name)
    {
        m_Name = name;
        // m_Level;
        // m_Handlers;
    };

    template <typename... Args>
    Logger::Logger(Args &&...args){};

    Logger::Logger(const Logger &other) {};

    Logger::Logger(Logger &&other) {};

    template <typename T>
    Logger::Logger(T name, Handler &handler)
    {
        m_Name = name;
        m_Handlers.push_back(handler);
    };

    template <typename T>
    Logger::Logger(T name, std::vector<Handler> &handlers)
    {
        m_Name = name;
        // m_Level;
        m_Handlers = handlers;
    };

    Logger &Logger::operator=(Logger other) {};

    void Logger::SetName(std::string name)
    {
        m_Name = name;
    };

    std::string Logger::Name() const
    {
        return m_Name;
    };

    void Logger::SetLevel(JeLog::Level level)
    {
        m_Level = level;
    };

    JeLog::Level Logger::Level() const
    {
        return m_Level;
    };

    JeLog::Level Logger::GetLevel() const
    {
        return m_Level;
    };

    void Logger::SetFormatter(Formatter *formatter)
    {
        for (auto &handler : m_Handlers)
        {
            handler.m_Formatter = formatter;
        }
    };

    bool Logger::IsEnabledFor(JeLog::Level level)
    {
        bool isEnabled = false;

        if (level >= m_Level)
        {
            isEnabled = true;
        }

        return isEnabled;
    };

    const std::vector<Handler> &Logger::Handlers() const
    {
        return m_Handlers;
    };

    std::vector<Handler> &Logger::Handlers()
    {
        return m_Handlers;
    };

    template <typename... Args>
    void Logger::_Log(Time *creationTime, SourceInfo srcInfo, JeLog::Level level, char *format, Args &&...args)
    {
        std::string message;

        // long long createdTime = std::chrono::time_point_cast<std::chrono::microseconds>(Timepoint).time_since_epoch().count();

        bool isEnabled = IsEnabledFor(level);

        if (!isEnabled)
        {
            return;
        }

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        ThreadInfo threadInfo(threadID, std::string(""));
        LogRecord logRecord = LogRecord(m_Name, level, srcInfo, creationTime, message, threadInfo);

        for (auto &handler : m_Handlers)
        {
            handler.Log(logRecord);
        }
    };

    template <typename T>
    void Logger::_Log(JeLog::Time *time, JeLog::SourceInfo srcInfo, JeLog::Level level, T message)
    {
        // long long createdTime = std::chrono::time_point_cast<std::chrono::microseconds>(Timepoint).time_since_epoch().count();

        bool isEnabled = IsEnabledFor(level);

        if (!isEnabled)
        {
            return;
        }

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        ThreadInfo threadInfo(threadID, "");

        LogRecord logRecord = LogRecord(m_Name, level, srcInfo, time, message, threadInfo);

        for (auto &handler : m_Handlers)
        {
            handler.Log(logRecord);
        }
    };

    // void Logger::AddHandler(Handler &handler)
    // {
    //     m_Handlers.push_back(handler);
    // };

    bool Logger::HasHandlers()
    {
        bool hasHanlders = false;

        if (!m_Handlers.empty())
        {
            hasHanlders = true;
        }

        return hasHanlders;
    };

    LogRecord Logger::Record() {
        // JeLog::Time *creationTime;
        // JeLog::SourceInfo srcInfo(__FILE__, __LINE__, "__FUNCSIG__");

        // long long createdTime = std::chrono::time_point_cast<std::chrono::microseconds>(Timepoint).time_since_epoch().count();
        // uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        // LogRecord logRecord = LogRecord(m_Name, m_Level, srcInfo, creationTime, "", threadID);

        // return logRecord;
    };

    void Logger::Handle(LogRecord &logRecord) {};

    void Logger::RemoveHandler(Handler &handler) {

    };

    Logger Logger::Clone(char *logger_name)
    {
        // auto cloned = std::make_shared<Logger>(*this);

        auto cloned = (*this);
        cloned.m_Name = std::move(logger_name);
        return cloned;
    };

    using clock = std::chrono::steady_clock;

    // return true if backtrace logging is enabled.
    // bool should_backtrace() const { return tracer_.enabled(); }

    // create new logger with same sinks and configuration.
    // inline Logger Logger::Clone(std::string logger_name) {
    // auto cloned = std::make_shared<logger>(*this);
    // cloned->name_ = std::move(logger_name);
    // return cloned;
    // };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    /////////// Log

    template <typename T>
    LogRecord Logger::Log(T message)
    {
        _Log({}, {}, m_Level, message);
    };

    template <typename... Args>
    LogRecord Logger::Log(char *format, Args &&...args)
    {
        _Log({}, {}, m_Level, format, std::forward<Args>(args)...);
    };

    template <typename T>
    LogRecord Logger::Log(JeLog::Level level, T message)
    {
        _Log({}, {}, level, message);
    };

    template <typename... Args>
    LogRecord Logger::Log(JeLog::Level level, char *format, Args &&...args)
    {
        _Log({}, {}, level, format, std::forward<Args>(args)...);
    };

    template <typename T>
    LogRecord Logger::Log(SourceInfo srcInfo, JeLog::Level level, T message)
    {
        _Log({}, srcInfo, level, message);
    };

    template <typename... Args>
    LogRecord Logger::Log(SourceInfo srcInfo, JeLog::Level level, char *format, Args &&...args)
    {
        _Log({}, srcInfo, level, format, std::forward<Args>(args)...);
    };

    template <typename T>
    LogRecord Logger::Log(clock::time_point creationTime, SourceInfo srcInfo, JeLog::Level level, T message)
    {
        _Log(creationTime, srcInfo, level, message);
    };

    template <typename... Args>
    LogRecord Logger::Log(clock::time_point creationTime, SourceInfo srcInfo, JeLog::Level level, char *format, Args... args)
    {
        _Log(creationTime, srcInfo, level, format, std::forward<Args>(args)...);
    };

    ////// Trace

    template <typename T>
    LogRecord Logger::Trace(T message)
    {
        Log(JeLog::Level::trace, message);
    };

    template <typename... Args>
    LogRecord Logger::Trace(char *format, Args &&...args)
    {
        Log(JeLog::Level::trace, format, std::forward<Args>(args)...);
    };

    template <typename T>
    LogRecord Logger::Trace(SourceInfo srcInfo, T message)
    {
        Log(srcInfo, JeLog::Level::trace, message);
    };

    template <typename... Args>
    LogRecord Logger::Trace(SourceInfo srcInfo, char *format, Args &&...args)
    {
        Log({}, srcInfo, JeLog::Level::trace, format, std::forward<Args>(args)...);
    };

    template <typename T>
    LogRecord Logger::Trace(clock::time_point creationTime, SourceInfo srcInfo, T message)
    {
        Log(creationTime, srcInfo, JeLog::Level::trace, message);
    };

    template <typename... Args>
    LogRecord Logger::Trace(clock::time_point creationTime, SourceInfo srcInfo, char *format, Args... args)
    {
        Log(creationTime, srcInfo, JeLog::Level::trace, format, std::forward<Args>(args)...);
    };

    // #define JE_LOG_LOG_LOGGER
    // #endif // JE_LOG_LOG_LOGGER

#pragma endregion // Logger

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