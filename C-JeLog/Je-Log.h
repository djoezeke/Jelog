
#ifndef JE_LOG_H
#define JE_LOG_H

#pragma region Defines
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <mutex>
#include <thread>
#include <map>


void VLOG(FILE *stream, Cstr tag, Cstr fmt, va_list args)
{
    fprintf(stream, "[%s] ", tag);
    vfprintf(stream, fmt, args);
    fprintf(stream, "\n");
}

void INFO(Cstr fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    VLOG(stderr, "INFO", fmt, args);
    va_end(args);
};

#pragma endregion // Defines

#pragma region Declarations
namespace JeLog
{
#pragma region Level

#define JELOG_LEVEL_UNKNOW -1
#define JELOG_LEVEL_TRACE 0
#define JELOG_LEVEL_DEBUG 1
#define JELOG_LEVEL_INFO 2
#define JELOG_LEVEL_WARN 3
#define JELOG_LEVEL_ERROR 4
#define JELOG_LEVEL_CRITICAL 5

    // Log level enum
    enum Level : int
    {
        unknown = JELOG_LEVEL_UNKNOW,
        trace = JELOG_LEVEL_TRACE,
        debug = JELOG_LEVEL_DEBUG,
        info = JELOG_LEVEL_INFO,
        warn = JELOG_LEVEL_WARN,
        error = JELOG_LEVEL_ERROR,
        critical = JELOG_LEVEL_CRITICAL,
        n_levels
    };

#define JELOG_LEVEL_NAME_TRACE "TRACE"
#define JELOG_LEVEL_NAME_DEBUG "DEBUG"
#define JELOG_LEVEL_NAME_INFO "INFO"
#define JELOG_LEVEL_NAME_WARNING "WARNING"
#define JELOG_LEVEL_NAME_ERROR "ERROR"
#define JELOG_LEVEL_NAME_CRITICAL "CRITICAL"
#define JELOG_LEVEL_NAME_UNKNOWN "UNKNOWN"

#if !defined(JELOG_LEVEL_NAMES)
#define JELOG_LEVEL_NAMES          \
    {                              \
        JELOG_LEVEL_NAME_TRACE,    \
        JELOG_LEVEL_NAME_DEBUG,    \
        JELOG_LEVEL_NAME_INFO,     \
        JELOG_LEVEL_NAME_WARNING,  \
        JELOG_LEVEL_NAME_ERROR,    \
        JELOG_LEVEL_NAME_CRITICAL, \
        JELOG_LEVEL_NAME_UNKNOWN,  \
    }

#endif // JELOG_LEVEL_NAMES

#if !defined(JELOG_SHORT_LEVEL_NAMES)

#define JELOG_SHORT_LEVEL_NAMES \
    {"T", "D", "I", "W", "E", "C", "U"}

#endif // JELOG_SHORT_LEVEL_NAMES

    char *NameFromLevel(JeLog::Level level);

    JeLog::Level LevelFromName(char *levelname);

#pragma endregion // Level

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
    public:               // Data
        char *m_FileName; // File Name of Location of Log.
        int m_Line;       // Line Number of Location of Log.
        char *m_FuncName; // Function Name of Location of Log.

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
        SourceInfo(char *filename, int line, char *funcname);

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
    public:                  // Data
        uint32_t m_ThreadID; //  Thread ID of Location of Log.
        char *m_ThreadName;  // Thread Name of Location of Log.

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
        ThreadInfo(uint32_t threadID, char *threadName);

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

#pragma region JeTime
#if !defined(JE_LOG_JE_TIME)

    class Time
    {
    public:
        virtual int64_t MilliSecond() = 0;
    };

    class CTime : Time
    {
    private:
        struct tm m_Time;

        int m_Year;
        int m_Month;
        int m_Day;
        int m_Hour;
        int m_Minute;
        int m_Second;

    protected:
        // First Time Using mutable Keyword. [01/04/2025] [04:06 PM]
        mutable int64_t m_MilliSeconds;

    public:
        CTime();

        int64_t MilliSecond() override;

        int year();
        int month();
        int day();
        int hour();
        int min();
        int sec();
    };

    class StopWatch : Time
    {
        using clock = std::chrono::steady_clock;
        std::chrono::time_point<clock> m_Start;

    protected:
        // First Time Using mutable Keyword.
        mutable int64_t m_MilliSeconds;

    public:
        StopWatch();

        int64_t MilliSecond() override;

        std::chrono::duration<double> Elapsed() const;

        std::chrono::milliseconds ElapsedMS();

        void Reset();
    };

#define JE_LOG_JE_TIME
#endif // JE_LOG_JE_TIME

#pragma endregion // JeTime

#pragma region LogRecord
#if !defined(JE_LOG_LOG_RECORD)

    /////////////////////////////////////////////////////////////////////////
    ///  \brief A LogRecord instance represents an event being Logged.
    ///
    /// LogRecord instances are created every time something is logged. They
    /// contain all the information pertinent to the event being logged. The
    /// main information passed in is in msg and args, which are combined
    /// using str(msg) % args to create the message field of the record. The
    /// record also includes information such as when the record was created,
    /// the source line where the logging call was made, and thread
    /// information to be logged.
    ///
    /////////////////////////////////////////////////////////////////////////
    class LogRecord
    {
    public:
        char *m_Name;
        char *m_Msg;
        JeLog::Level m_Level;
        JeLog::SourceInfo m_SrcInfo;
        JeLog::ThreadInfo m_ThdInfo;
        JeLog::Time *m_CreatedTime;

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize an empty Logging Record.
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize a Logging Record with provided Information.
        ///
        /// \param name
        /// \param message
        /// \param level
        /// \param sourceInfo
        /// \param creationTime
        /// \param threadID
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord(char *name, char *message, JeLog::Level level, JeLog::SourceInfo sourceInfo, JeLog::Time *creationTime, JeLog::ThreadInfo threadInfo);
    };

#define JE_LOG_LOG_RECORD
#endif // JE_LOG_LOG_RECORD

#pragma endregion // LogRecord

#pragma region Formatter
#if !defined(JE_LOG_FORMATTER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Formatter
    //-----------------------------------------------------------------------------
    // - Format()
    //-----------------------------------------------------------------------------

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
    /// The Formatter can be initialized with a format string which makes use of
    /// knowledge of the LogRecord attributes - e.g. the default value mentioned
    /// above makes use of the fact that the user's message and arguments are pre-
    /// formatted into a LogRecord's message attribute. Currently, the useful
    /// attributes in a LogRecord are described by:
    ///
    /// %(name)s            Name of the logger (logging channel)
    /// %(levelno)s         Numeric logging level for the message (DEBUG, INFO,
    ///                     WARNING, ERROR, CRITICAL)
    ///
    /// %(levelname)s       Text logging level for the message ("DEBUG", "INFO",
    ///                     "WARNING", "ERROR", "CRITICAL")
    ///
    /// %(pathname)s        Full pathname of the source file where the logging
    ///                     call was issued (if available)
    ///
    /// %(filename)s        Filename portion of pathname
    ///
    /// %(module)s          Module (name portion of filename)
    ///
    /// %(lineno)d          Source line number where the logging call was issued
    ///                     (if available)
    ///
    /// %(funcName)s        Function name
    ///
    /// %(created)f         Time when the LogRecord was created (time.time_ns() / 1e9
    ///                     return value)
    ///
    /// %(asctime)s         Textual time when the LogRecord was created
    ///
    /// %(msecs)d           Millisecond portion of the creation time
    ///
    /// %(relativeCreated)d Time in milliseconds when the LogRecord was created,
    ///                     relative to the time the logging module was loaded
    ///                     (typically at application startup time)
    ///
    /// %(thread)d          Thread ID (if available)
    ///
    /// %(threadName)s      Thread name (if available)
    ///
    /// %(taskName)s        Task name (if available)
    ///
    /// %(process)d         Process ID (if available)
    ///
    /// %(message)s         The result of record.getMessage(), computed just as
    ///                     the record is emitted
    ///
    /////////////////////////////////////////////////////////////////////////
    class Formatter
    {
        // class JsonFormatter;
        // class YamlFormatter;
        // class XmlFormatter;
        // class TextFormatter;

    public:
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
        virtual JeLog::LogRecord Format(JeLog::LogRecord &logRecord) = 0;
    };

#define JE_LOG_FORMATTER
#endif // JE_LOG_FORMATTER

#pragma endregion // Formatter

#pragma region TextFormatter

#if !defined(JE_LOG_TEXT_FORMATTER)

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
    class TextFormatter : JeLog::Formatter
    {
        // class YamlFormatter;
        // class XmlFormatter;

    private:
        char *m_MessageFormat;
        char *m_TimeFormat;
        int m_ProfileCount;
        // std::mutex m_lock;
    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the formatter with specified format strings.
        ///
        /// \param messageFormat
        /// \param timeFormat
        ///
        /////////////////////////////////////////////////////////////////////////
        TextFormatter(char *messageFormat, char *timeFormat);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the formatter with unknown format strings.
        ///
        /////////////////////////////////////////////////////////////////////////
        TextFormatter();

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
    };

#define JE_LOG_TEXT_FORMATTER
#endif // JE_LOG_TEXT_FORMATTER

#pragma endregion // TextFormatter

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
    };

#define JE_LOG_JSON_FORMATTER
#endif // JE_LOG_JSON_FORMATTER

#pragma endregion // JsonFormatter

#pragma region Filter
#if !defined(JE_LOG_FILTER)

    /////////////////////////////////////////////////////////////////////////
    /// \brief Filter instances are used to perform arbitrary filtering of LogRecords.
    ///
    /// Loggers and Handlers can optionally use Filter instances to filter
    /// records as desired. The base filter class only allows events which are
    /// below a certain point in the logger hierarchy. For example, a filter
    /// initialized with "A.B" will allow events logged by loggers "A.B",
    /// "A.B.C", "A.B.C.D", "A.B.D" etc. but not "A.BB", "B.A.B" etc. If
    /// initialized with the empty string, all events are passed.
    ///
    /////////////////////////////////////////////////////////////////////////
    class Filter
    {

    public:
        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Determine if a record is loggable by consulting all the filters.
        ///
        /// The default is to allow the record to be logged; any filter can veto
        /// this by returning a false value.
        /// If a filter attached to a handler returns a log record instance,
        /// then that instance is used in place of the original log record in
        /// any further processing of the event by that handler.
        /// If a filter returns any other true value, the original log record
        /// is used in any further processing of the event by that handler.
        ///
        /// If none of the filters return false values, this method returns
        /// a log record.
        /// If any of the filters return a false value, this method returns
        /// a false value.
        ///
        /// Allow filters to return a LogRecord instead of
        /// modifying it in place.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual JeLog::LogRecord filter(JeLog::LogRecord &logRecord) = 0;
    };

#define JE_LOG_FILTER
#endif // JE_LOG_FILTER

#pragma endregion // Filter

#pragma region Filterer
#if !defined(JE_LOG_FILTERER)

    /////////////////////////////////////////////////////////////////////////
    /// \brief Filterer : list of of Filters.
    ///
    /// A base class for loggers and handlers which allows them to share
    /// common code.
    ///
    /////////////////////////////////////////////////////////////////////////
    class Filterer
    {
    private:
        // change it to map [name , Filter]
        std::map<const char *, JeLog::Filter *> m_Filterss;

    public:
        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Add the specified filter to this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void AddFilter(JeLog::Filter *filter);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Remove the specified filter to this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void RemoveFilter(JeLog::Filter *filter);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Determine if the specified record is to be logged.
        ///
        /// Returns True if the record should be logged, or False otherwise.
        /// If deemed appropriate, the record may be modified in-place.
        /// it is formatted using formatException() and appended to the message.
        ///
        /// \param
        /// \param
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::LogRecord Filter(JeLog::Filter *filter, JeLog::LogRecord &logRecord);

        JeLog::LogRecord Filter(char *filtername, JeLog::LogRecord &logRecord);
    };

#define JE_LOG_FILTERER
#endif // JE_LOG_FILTERER

#pragma endregion // Filterer

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
    };

#define JE_LOG_HANDLER
#endif // JE_LOG_HANDLER

#pragma endregion // Handler

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

        virtual void Log(LogRecord &) override;
    };

#define JE_LOG_LOG_STREAM_HANDLER
#endif // JE_LOG_LOG_STREAM_HANDLER

#pragma endregion // StreamHandler

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

}; // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region Level

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::CTime
    //-----------------------------------------------------------------------------
    // - NameFromLevel()
    // - LevelFromName()
    //-----------------------------------------------------------------------------

    char *NameFromLevel(JeLog::Level level)
    {
        if (level == JeLog::Level::trace)
        {
            return JELOG_LEVEL_NAME_TRACE;
        }
        else if (level == JeLog::Level::warn)
        {
            return JELOG_LEVEL_NAME_WARNING;
        }
        else if (level == JeLog::Level::error)
        {
            return JELOG_LEVEL_NAME_ERROR;
        }
        else if (level == JeLog::Level::critical)
        {
            return JELOG_LEVEL_NAME_CRITICAL;
        }
        else if (level == JeLog::Level::debug)
        {
            return JELOG_LEVEL_NAME_DEBUG;
        }
        else
        {
            return JELOG_LEVEL_NAME_UNKNOWN;
        }
    };

    JeLog::Level LevelFromName(char *levelname)
    {
        if (levelname == JELOG_LEVEL_NAME_TRACE)
        {
            return JeLog::Level::trace;
        }
        else if (levelname == JELOG_LEVEL_NAME_WARNING)
        {
            return JeLog::Level::warn;
        }
        else if (levelname == JELOG_LEVEL_NAME_DEBUG)
        {
            return JeLog::Level::debug;
        }
        else if (levelname == JELOG_LEVEL_NAME_ERROR)
        {
            return JeLog::Level::error;
        }
        else if (levelname == JELOG_LEVEL_NAME_CRITICAL)
        {
            return JeLog::Level::critical;
        }
        else
        {
            return JeLog::Level::unknown;
        }
    };

#pragma endregion // Level

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

    SourceInfo::SourceInfo(char *filename, int line, char *funcname)
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

    ThreadInfo::ThreadInfo(uint32_t threadID, char *threadName)
    {
        m_ThreadID = threadID;
        m_ThreadName = threadName;
    };

    bool ThreadInfo::UnKnown() const
    {
        // First Time Using the Tenary Operator. [01/04/2025] [03:58 PM]
        bool isEmpty = m_ThreadID == 0 ? true : false;
        return isEmpty;
    };

    // #define JE_LOG_THREAD_INFO
    // #endif // JE_LOG_THREAD_INFO

#pragma endregion // ThreadInfo

#pragma region JeTime

    // #if !defined(JE_LOG_JE_TIME)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::CTime
    //-----------------------------------------------------------------------------
    // - CTime()
    // - ~CTime()
    // - year()
    // - month()
    // - day()
    // - hour()
    // - min()
    // - sec()
    //-----------------------------------------------------------------------------

    CTime::CTime()
    {
        time_t tim = time(NULL);
        m_Time = *localtime(&tim);
        m_Year = m_Time.tm_year + 1900;
        m_Month = m_Time.tm_mon + 1;
        m_Day = m_Time.tm_mday;
        m_Hour = m_Time.tm_hour;
        m_Minute = m_Time.tm_min;
        m_Second = m_Time.tm_sec;
    };

    int CTime::year()
    {
        return m_Year;
    };

    int CTime::month()
    {
        return m_Month;
    };

    int CTime::day()
    {
        return m_Day;
    };

    int CTime::hour()
    {
        return m_Hour;
    };

    int CTime::min()
    {
        return m_Minute;
    };

    int CTime::sec()
    {
        return m_Second;
    };

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::StopWatch
    //-----------------------------------------------------------------------------
    // - StopWatch()
    // - ~StopWatch()
    // - Elapsed()
    // - ElapsedMS()
    // - Reset()
    //-----------------------------------------------------------------------------

    StopWatch::StopWatch()
    {
        m_Start = clock::now();
        m_MilliSeconds = 0;
    };

    std::chrono::duration<double> StopWatch::Elapsed() const
    {
        auto milliseconds = std::chrono::duration<double>(clock::now() - m_Start);
        m_MilliSeconds = milliseconds.count();
        return milliseconds;
    };

    std::chrono::milliseconds StopWatch::ElapsedMS()
    {
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_Start);
        m_MilliSeconds = milliseconds.count();
        return milliseconds;
    };

    void StopWatch::Reset()
    {
        m_Start = clock::now();
    };

    // #define JE_LOG_JE_TIME
    // #endif // JE_LOG_JE_TIME

#pragma endregion // JeTime

#pragma region LogRecord

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::LogRecord
    //-----------------------------------------------------------------------------
    // - LogRecord()
    //-----------------------------------------------------------------------------

    // #if !defined(JE_LOG_LOG_RECORD)

    LogRecord::LogRecord()
    {
        m_Name = "";
        m_Msg = "";
        m_Level = JeLog::Level::unknown;
        m_SrcInfo = JeLog::SourceInfo();
        m_CreatedTime = nullptr;
        m_ThdInfo = JeLog::ThreadInfo();
    };

    LogRecord::LogRecord(char *name, char *message, JeLog::Level level, JeLog::SourceInfo sourceInfo, JeLog::Time *creationTime, JeLog::ThreadInfo threadInfo)
    {
        m_Name = name;
        m_Msg = message;
        m_Level = level;
        m_SrcInfo = sourceInfo;
        m_CreatedTime = creationTime;
        m_ThdInfo = threadInfo;
    };

    // #define JE_LOG_LOG_RECORD
    // #endif // JE_LOG_LOG_RECORD

#pragma endregion // LogRecord

#pragma region TextFormatter

    // #if !defined(JE_LOG_TEXT_FORMATTER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::TextFormatter
    //-----------------------------------------------------------------------------
    // - TextFormatter()
    // - Format()
    //-----------------------------------------------------------------------------

    TextFormatter::TextFormatter(char *messageFormat, char *timeFormat)
    {
        m_MessageFormat = messageFormat;
        m_TimeFormat = timeFormat;
    };

    TextFormatter::TextFormatter()
    {
        m_MessageFormat = "";
        m_TimeFormat = "";
    };

    JeLog::LogRecord TextFormatter::Format(JeLog::LogRecord &logRecord)
    {
        std::cout << " logrecord [Message] : " << logRecord.m_Msg << std::endl;
        return logRecord;
    };

    // #define JE_LOG_TEXT_FORMATTER
    // #endif // JE_LOG_TEXT_FORMATTER

#pragma endregion // TextFormatter

#pragma region JsonFormatter

    // #if !defined(JE_LOG_JSON_FORMATTER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::JsonFormatter
    //-----------------------------------------------------------------------------
    // - JsonFormatter()
    // - ~JsonFormatter()
    // - SetPattern()
    // - Format()
    // - BeginSession()
    // - EndSession()
    // - WriteHeader()
    // - WriteFooter()
    //-----------------------------------------------------------------------------

    JsonFormatter::JsonFormatter() {};

    JsonFormatter::JsonFormatter() {};

    JsonFormatter::~JsonFormatter() {};

    LogRecord JsonFormatter::Format(LogRecord &logRecord)
    {
        // std::lock_guard<std::mutex> lock(m_lock);

        m_OutputStream << "{";
        m_OutputStream << "\"Name\":\"" << logRecord.m_Name << "\",";
        m_OutputStream << "\"Level\":\"" << logRecord.m_Level << "\",";
        m_OutputStream << "\"Message\":\"" << logRecord.m_Msg << "\",";
        m_OutputStream << "\"LineNo\":\"" << logRecord.m_SrcInfo.m_Line << "\",";
        m_OutputStream << "\"Function\":\"" << logRecord.m_SrcInfo.m_Line << "\",";
        m_OutputStream << "\"FileName\":\"" << logRecord.m_SrcInfo.m_FuncName << "\",";
        m_OutputStream << "\"ThreadID\":\"" << logRecord.m_ThdInfo.m_ThreadID << "\",";
        m_OutputStream << "\"ThreadName\":\"" << logRecord.m_ThdInfo.m_ThreadName << "\",";
        m_OutputStream << "\"CreationTime\":\"" << logRecord.m_CreatedTime->MilliSecond();
        m_OutputStream << "}\n";

        m_OutputStream.flush();
        return logRecord;
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
#pragma region Filterer
    // #if !defined(JE_LOG_FILTERER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Filterer
    //-----------------------------------------------------------------------------
    // - AddFilter()
    // - RemoveFilter()
    // - Filter()
    //-----------------------------------------------------------------------------

    void Filterer::AddFilter(JeLog::Filter *filter)
    {
        filter->Name();
        m_Filterss.emplace(filter->Name(), filter);
    };

    void Filterer::RemoveFilter(JeLog::Filter *filter)
    {
        m_Filterss.erase(filter->Name());
    };

    JeLog::LogRecord Filterer::Filter(JeLog::Filter *filter, JeLog::LogRecord &logRecord)
    {
        filter->filter(logRecord);
    };

    JeLog::LogRecord Filterer::Filter(char *filtername, JeLog::LogRecord &logRecord)
    {
        auto &filter = m_Filterss[filtername];
        filter->filter(logRecord);
    };

    // #define JE_LOG_FILTERER
    // #endif // JE_LOG_FILTERER

#pragma endregion // Filterer

#pragma region Handler
    // #if !defined(JE_LOG_HANDLER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Handler
    //-----------------------------------------------------------------------------
    // - Handler()
    // - ~Handler()
    // - GetName()
    // - SetName()
    // - SetLevel()
    // - Format()
    // - SetFormatter()
    //-----------------------------------------------------------------------------

    Handler::Handler()
    {
        m_Formatter = 0;
        // m_Filterer = 0;
    };

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

    void FileHandler::Log(LogRecord &logRecord) {};

    // #define JE_LOG_LOG_FILE_HANDLER
    // #endif // JE_LOG_LOG_FILE_HANDLER

#pragma endregion // FileHandler

}; // namespace JeLog

#pragma endregion // Definitions

#endif // JE_LOG_H
