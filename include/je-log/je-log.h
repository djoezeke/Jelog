#ifndef JE_LOG_JE_LOG_H
#define JE_LOG_JE_LOG_H

// O------------------------------------------------------------------------------O
// | Je-Log STANDARD INCLUDES                                                     |
// O------------------------------------------------------------------------------O
#pragma region Includes

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <mutex>
#include <thread>

#pragma endregion // Includes

#pragma region registry

// class registry
// {
// public:
//     using log_levels = std::unordered_map<std::string, level::level_enum>;
//     registry(const registry &) = delete;
//     registry &operator=(const registry &) = delete;

//     void register_logger(std::shared_ptr<logger> new_logger);
//     void initialize_logger(std::shared_ptr<logger> new_logger);
//     std::shared_ptr<logger> get(const std::string &logger_name);
//     std::shared_ptr<logger> default_logger();

//     // Return raw ptr to the default logger.
//     // To be used directly by the spdlog default api (e.g. spdlog::info)
//     // This make the default API faster, but cannot be used concurrently with set_default_logger().
//     // e.g do not call set_default_logger() from one thread while calling spdlog::info() from
//     // another.
//     logger *get_default_raw();

//     // set default logger and add it to the registry if not registered already.
//     // default logger is stored in default_logger_ (for faster retrieval) and in the loggers_ map.
//     // Note: Make sure to unregister it when no longer needed or before calling again with a new
//     // logger.
//     void set_default_logger(std::shared_ptr<logger> new_default_logger);

//     void set_tp(std::shared_ptr<thread_pool> tp);

//     std::shared_ptr<thread_pool> get_tp();

//     // Set global formatter. Each sink in each logger will get a clone of this object
//     void set_formatter(std::unique_ptr<formatter> formatter);

//     void enable_backtrace(size_t n_messages);

//     void disable_backtrace();

//     void set_level(Level log_level);

//     void flush_on(Level log_level);

//     template <typename Rep, typename Period>
//     void flush_every(std::chrono::duration<Rep, Period> interval)
//     {
//         std::lock_guard<std::mutex> lock(flusher_mutex_);
//         auto clbk = [this]()
//         { this->flush_all(); };
//         periodic_flusher_ = details::make_unique<periodic_worker>(clbk, interval);
//     };

//     std::unique_ptr<periodic_worker> &get_flusher()
//     {
//         std::lock_guard<std::mutex> lock(flusher_mutex_);
//         return periodic_flusher_;
//     };

//     void set_error_handler(err_handler handler);

//     void apply_all(const std::function<void(const std::shared_ptr<logger>)> &fun);

//     void flush_all();

//     void drop(const std::string &logger_name);

//     void drop_all();

//     // clean all resources and threads started by the registry
//     void shutdown();

//     std::recursive_mutex &tp_mutex();

//     void set_automatic_registration(bool automatic_registration);

//     // set levels for all existing/future loggers. global_level can be null if should not set.
//     void set_levels(log_levels levels, level::level_enum *global_level);

//     static registry &instance();

//     void apply_logger_env_levels(std::shared_ptr<logger> new_logger);

// private:
//     registry();
//     ~registry();

//     void throw_if_exists_(const std::string &logger_name);
//     void register_logger_(std::shared_ptr<logger> new_logger);
//     bool set_level_from_cfg_(logger *logger);
//     std::mutex logger_map_mutex_, flusher_mutex_;
//     std::recursive_mutex tp_mutex_;
//     std::unordered_map<std::string, std::shared_ptr<logger>> loggers_;
//     log_levels log_levels_;
//     std::unique_ptr<formatter> formatter_;
//     spdlog::level::level_enum global_log_level_ = level::info;
//     level::level_enum flush_level_ = level::off;
//     err_handler err_handler_;
//     std::shared_ptr<thread_pool> tp_;
//     std::unique_ptr<periodic_worker> periodic_flusher_;
//     std::shared_ptr<logger> default_logger_;
//     bool automatic_registration_ = true;
//     size_t backtrace_n_messages_ = 0;
// };

// inline registry::~registry() = default;

// inline void registry::register_logger(std::shared_ptr<logger> new_logger)
// {
//     std::lock_guard<std::mutex> lock(logger_map_mutex_);
//     register_logger_(std::move(new_logger));
// };

// inline void registry::initialize_logger(std::shared_ptr<logger> new_logger)
// {
//     std::lock_guard<std::mutex> lock(logger_map_mutex_);
//     new_logger->set_formatter(formatter_->clone());

//     if (err_handler_)
//     {
//         new_logger->set_error_handler(err_handler_);
//     }

//     // set new level according to previously configured level or default level
//     auto it = log_levels_.find(new_logger->name());
//     auto new_level = it != log_levels_.end() ? it->second : global_log_level_;
//     new_logger->set_level(new_level);

//     new_logger->flush_on(flush_level_);

//     if (backtrace_n_messages_ > 0)
//     {
//         new_logger->enable_backtrace(backtrace_n_messages_);
//     }

//     if (automatic_registration_)
//     {
//         register_logger_(std::move(new_logger));
//     }
// };

// inline std::shared_ptr<logger> registry::get(const std::string &logger_name)
// {
//     std::lock_guard<std::mutex> lock(logger_map_mutex_);
//     auto found = loggers_.find(logger_name);
//     return found == loggers_.end() ? nullptr : found->second;
// };

#pragma endregion // registry

// O------------------------------------------------------------------------------O
// | Je-Log Declarations                                                          |
// O------------------------------------------------------------------------------O
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

    const char *NameFromLevel(Level);

    Level LevelFromName(const char *);

#pragma endregion // Level

#pragma region JeTime
#if !defined(JE_LOG_JE_TIME)

    class Time
    {
    protected:
        int64_t m_MilliSeconds;

    public:
        virtual int64_t MSec();
        virtual int64_t Sec();
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

    public:
        CTime();

        virtual int64_t MSec() override;

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

    public:
        StopWatch();

        virtual int64_t MSec() override;

        std::chrono::duration<double> Elapsed() const;

        std::chrono::milliseconds ElapsedMS() const;

        void Reset();
    };

#define JE_LOG_JE_TIME
#endif // JE_LOG_JE_TIME

#pragma endregion // JeTime

#pragma region SourceLocation
#if !defined(JE_LOG_SOURCE_LOCATION)

    struct Src_Loc
    {
    public: // Data
        char *m_FileName;
        int m_Line;
        char *m_FuncName;

    public: // Methods
        Src_Loc();

        Src_Loc(char *filename, int line, char *funcname);

        constexpr bool Empty() const noexcept;
    };

#define JE_LOG_SOURCE_LOCATION
#endif // JE_LOG_SOURCE_LOCATION

#pragma endregion // SourceLocation

#pragma region LogRecord
#if !defined(JE_LOG_LOG_RECORD)

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
    class LogRecord
    {
    private:
        char *m_Name;
        JeLog::Level m_Level;
        JeLog::Src_Loc m_SrcLoc;
        int m_ThreadID;
        char *m_Msg;
        char *m_ThreadName;
        JeLog::Time m_CreatedTime;

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize a logging record with interesting information.
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize a logging record with interesting information.
        ///
        /// \param name
        /// \param level
        /// \param srcLoc
        /// \param creationTime
        /// \param message
        /// \param threadID
        ///
        /////////////////////////////////////////////////////////////////////////
        LogRecord(char *name, JeLog::Level level, JeLog::Src_Loc srcLoc, JeLog::Time creationTime, char *message, uint32_t threadID);

        ~LogRecord();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *Name();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Level for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::Level Level();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the message for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *Message();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name of the Function in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *Function();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the File Name in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *FileName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Line Number for which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        int LineNo();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Thread ID for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        int ThreadID();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Thread Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *ThreadName();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Time of Creation for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        JeLog::Time CreationTime();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetName(char *name);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Level for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetLevel(JeLog::Level level);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the message for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetMessage(char *message);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name of the Function in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFunction(char *name);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the File Name in which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetFileName(char *filename);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Line Number for which this LogRecord was Created.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetLineNo(int lineno);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Thread ID for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetThreadID(int threadID);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Thread Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetThreadName(char *threadName);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Time of Creation for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetCreationTime(JeLog::Time creationTime);
    };

#define JE_LOG_LOG_RECORD
#endif // JE_LOG_LOG_RECORD

#pragma endregion // LogRecord

#pragma region Formatter
#if !defined(JE_LOG_FORMATTER)

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
        /// \brief Initialize the formatter with specified format strings.
        ///
        ///  Initialize the formatter either with the specified format string, or a
        ///  default as described above. Allow for specialized date formatting with
        ///  the optional datefmt argument. If datefmt is omitted, you get an
        ///  ISO8601-like (or RFC 3339-like) format.
        ///
        ///  Use a style parameter of '%', '{' or '$' to specify that you want to
        ///  use one of %-formatting, :meth:`str.format` (``{}``) formatting or
        ///  :class:`string.Template` formatting in your format string.
        ///
        /// \param fmt
        /// \param datefmt
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void SetPattern(char *fmt, char *datefmt) = 0;

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
        virtual LogRecord Format(LogRecord &logRecord) = 0;

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
        virtual void TimeFormat(LogRecord &logRecord, char *format) = 0;
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
    class TextFormatter : Formatter
    {
        // class YamlFormatter;
        // class XmlFormatter;

    private:
        int m_ProfileCount;
        std::mutex m_lock;

    private: // Methods
        void BeginSession();

        void EndSession();

        void WriteHead();

        void WriteFoot();

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the formatter with specified format strings.
        ///
        /// \param fmt
        /// \param datefmt
        ///
        /////////////////////////////////////////////////////////////////////////
        TextFormatter(char *fmt, char *datefmt);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the formatter with specified format strings.
        ///
        /////////////////////////////////////////////////////////////////////////
        TextFormatter();

        ~TextFormatter();

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
        virtual LogRecord Format(LogRecord &logRecord) override;

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
        virtual void TimeFormat(LogRecord &logRecord, char *format) override;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /*
         */
        /////////////////////////////////////////////////////////////////////////
        virtual void MessageFormat(LogRecord &logRecord, char *format);
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
    class JsonFormatter : Formatter
    {

    private:
        std::ofstream m_OutputStream;
        char *m_Filename;
        int m_ProfileCount;
        std::mutex m_lock;

    private: // Methods
        void BeginSession();

        void EndSession();

        void WriteHeader();

        void WriteFooter();

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the formatter with specified format strings.
        ///
        /// \param defaults
        ///
        /////////////////////////////////////////////////////////////////////////
        JsonFormatter(char *, char *);

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
        virtual LogRecord Format(LogRecord &) override;

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
        virtual char *TimeFormat(LogRecord &, char *);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual char *MessageFormat(LogRecord &, char *);
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
    private:
        char *m_Name;

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Filter instances are used to perform arbitrary filtering of LogRecords.
        ///
        /// Loggers and Handlers can optionally use Filter instances to filter
        /// records as desired. The base filter class only allows events which are
        /// below a certain point in the logger hierarchy. For example, a filter
        /// initialized with "A.B" will allow events logged by loggers "A.B",
        ///"A.B.C", "A.B.C.D", "A.B.D" etc. but not "A.BB", "B.A.B" etc. If
        /// initialized with the empty string, all events are passed.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        Filter(char *);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *Name();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name Log which the LogRecord was Created.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void Name(char *);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Filter instances are used to perform arbitrary filtering of LogRecords.
        ///
        /// Loggers and Handlers can optionally use Filter instances to filter
        /// records as desired. The base filter class only allows events which are
        /// below a certain point in the logger hierarchy. For example, a filter
        /// initialized with "A.B" will allow events logged by loggers "A.B",
        ///"A.B.C", "A.B.C.D", "A.B.D" etc. but not "A.BB", "B.A.B" etc. If
        /// initialized with the empty string, all events are passed.
        ///
        /////////////////////////////////////////////////////////////////////////
        Filter();

        ~Filter();

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
        LogRecord filter(LogRecord &);
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
        // change it to map [name , Filterer]
        std::vector<Filter> m_Filters;

    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the list of filters to be an empty list.
        ///
        /////////////////////////////////////////////////////////////////////////
        Filterer();

        ~Filterer();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Add the specified filter to this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void AddFilter(Filter &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Remove the specified filter to this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        void RemoveFilter(Filter &);

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
        LogRecord filter(Filter &, LogRecord &);
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
        Formatter m_Formatter;
        Filterer m_Filterer;

    protected:
        // sink log level - default is all
        Level m_Level = Level::trace;

    public: // Methods
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
        virtual void Log(LogRecord &logRecord) = 0;

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
        virtual void SetFormatter(Formatter &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Set the Filterer for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void SetFilterer(Filterer &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Get the formatter for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void GetFormatter();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Get the Filterer for this handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void SetFilterer();

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
        char *m_Name;
        JeLog::Level m_Level;
        std::vector<Handler> m_Handlers;
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
        Logger(Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        Logger(const Logger &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        Logger(Logger &&) noexcept;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        Logger(T, Handler &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Initialize the logger with a name and an optional level.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        Logger(T, std::vector<Handler> &);

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
        Logger &operator=(Logger) noexcept;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Name the Logger.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void SetName(char *);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Get the current log severity.
        ///
        /////////////////////////////////////////////////////////////////////////
        char *Name() const;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set a New log severity.
        ///
        /// \param level
        /////////////////////////////////////////////////////////////////////////
        void SetLevel(JeLog::Level);

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
        void SetFormatter(Formatter &);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Is this logger enabled for level 'level'?
        /// \return return true logging is enabled for the given level.
        /// \param level
        /////////////////////////////////////////////////////////////////////////
        bool IsEnabledFor(JeLog::Level);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Is this logger enabled for level 'level'?
        /// \return return Vector Handlers used by Logger
        /////////////////////////////////////////////////////////////////////////
        const std::vector<Handler> &Handlers() const;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Is this logger enabled for level 'level'?
        /// \return return Vector Handlers used by Logger
        /// \param level
        /////////////////////////////////////////////////////////////////////////
        std::vector<Handler> &Handlers(); // handler ptr

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Low-level logging routine which creates a LogRecord and then calls
        // all the handlers of this logger to handle the record.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        void _Log(clock::time_point, Src_Loc, JeLog::Level, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Low-level logging routine which creates a LogRecord and then calls
        // all the handlers of this logger to handle the record.
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        void _Log(clock::time_point, Src_Loc, JeLog::Level, T);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Call the handlers for the specified record.
        ///
        /// This method is used for unpickled records received from a socket, as
        /// well as those created locally. Logger-level filtering is applied.
        ///
        /////////////////////////////////////////////////////////////////////////
        void Handle(LogRecord &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Add the specified handler to this logger.
        ///
        /////////////////////////////////////////////////////////////////////////
        void AddHandler(Handler &);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Remove the specified handler to this logger.
        ///
        /////////////////////////////////////////////////////////////////////////
        void RemoveHandler(Handler &);

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
        /// \param src_loc source location of Log.
        /// \param level severity of Log.
        /// \param message message to Log.
        ///
        /// logger.Log(loc,Level::trace,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Log(Src_Loc, JeLog::Level, T);

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
        LogRecord Log(Src_Loc, JeLog::Level, char *, Args &&...);

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
        LogRecord Log(clock::time_point, Src_Loc, JeLog::Level, T);

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
        LogRecord Log(clock::time_point, Src_Loc, JeLog::Level, char *, Args...);

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
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Trace(loc,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Trace(Src_Loc, T);

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
        LogRecord Trace(Src_Loc, char *, Args &&...);

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
        LogRecord Trace(clock::time_point, Src_Loc, T);

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
        LogRecord Trace(clock::time_point, Src_Loc, char *, Args...);

        ///// Error

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "ERROR" severity.
        ///
        /// \param message message to Log.
        ///
        /// logger.Error("Hello World");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Error(T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "ERROR" severity.
        ///
        /// \param format log format.
        /// \param ...args  Argument to Log.
        ///
        /// logger.Error("Hello %s !", name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Error(char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "ERROR" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Error(loc,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Error(Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "ERROR" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Error(loc,"Hello %s!",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Error(Src_Loc, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "ERROR" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Error(time,loc,"Hello Zeke");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Error(clock::time_point, Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "ERROR" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Error(time,loc,"Hello %s",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Error(clock::time_point, Src_Loc, char *, Args...);

        //// Warning

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "WARNING" severity.
        ///
        /// \param message message to Log.
        ///
        /// logger.Warning("Hello World");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Warning(T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "WARNING" severity.
        ///
        /// \param format log format.
        /// \param ...args  Argument to Log.
        ///
        /// logger.Warning("Hello %s !", name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Warning(char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "WARNING" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Warning(loc,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Warning(Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "WARNING" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Warning(loc,"Hello %s!",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Warning(Src_Loc, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "WARNING" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Warning(time,loc,"Hello Zeke");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Warning(clock::time_point, Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "WARNING" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Warning(time,loc,"Hello %s",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Warning(clock::time_point, Src_Loc, char *, Args...);

        //// Critical

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "CRITICAL" severity.
        ///
        /// \param message message to Log.
        ///
        /// logger.Critical("Hello World");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Critical(T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "CRITICAL" severity.
        ///
        /// \param format log format.
        /// \param ...args  Argument to Log.
        ///
        /// logger.Critical("Hello %s !", name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Critical(char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "CRITICAL" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Critical(loc,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Critical(Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "CRITICAL" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Critical(loc,"Hello %s!",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Critical(Src_Loc, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "CRITICAL" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Critical(time,loc,"Hello Zeke");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Critical(clock::time_point, Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "CRITICAL" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Critical(time,loc,"Hello %s",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Critical(clock::time_point, Src_Loc, char *, Args...);

        ////// Info

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "INFO" severity.
        ///
        /// \param message message to Log.
        ///
        /// logger.Info("Hello World");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Info(T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "INFO" severity.
        ///
        /// \param format log format.
        /// \param ...args  Argument to Log.
        ///
        /// logger.Info("Hello %s !", name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Info(char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "INFO" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Info(loc,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Info(Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "INFO" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Info(loc,"Hello %s!",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Info(Src_Loc, char *, Args &&...);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "INFO" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Info(time,loc,"Hello Zeke");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Info(clock::time_point, Src_Loc, T);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "INFO" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Info(time,loc,"Hello %s",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Info(clock::time_point log_time, Src_Loc loc, char *format, Args... args);

        ///// Debug

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "DEBUG" severity.
        ///
        /// \param message message to Log.
        ///
        /// logger.Debug("Hello World");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Debug(T message);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "DEBUG" severity.
        ///
        /// \param format log format.
        /// \param ...args  Argument to Log.
        ///
        /// logger.Debug("Hello %s !", name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Debug(char *format, Args &&...args);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "DEBUG" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Debug(loc,"Hello Zeke!");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Debug(Src_Loc loc, T message);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "DEBUG" severity with source location info.
        ///
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Debug(loc,"Hello %s!",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Debug(Src_Loc loc, char *format, Args &&...args);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log 'message' with "DEBUG" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param message message to Log.
        ///
        /// logger.Debug(time,loc,"Hello Zeke");
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename T>
        LogRecord Debug(clock::time_point log_time, Src_Loc loc, T message);

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Log '..args' with "DEBUG" severity with source and time info.
        ///
        /// \param log_time time of Logging.
        /// \param src_loc source location of Log.
        /// \param format log format.
        /// \param ...args  Arguments to Log.
        ///
        /// logger.Debug(time,loc,"Hello %s",name);
        ///
        /////////////////////////////////////////////////////////////////////////
        template <typename... Args>
        LogRecord Debug(clock::time_point log_time, Src_Loc loc, char *format, Args... args);

        // return true if backtrace logging is enabled.
        // bool should_backtrace() const { return tracer_.enabled(); }
    };

#define JE_LOG_LOG_LOGGER
#endif // JE_LOG_LOG_LOGGER

#pragma endregion // Logger

#pragma region Configurator
#if !defined(JE_LOG_CONFIGURATOR)

    /////////////////////////////////////////////////////////////////////////
    /// \brief Logging Configurator
    ///
    /// The configurator which defines some useful defaults and options.
    ///
    /// Configure logging using a Data type or Data Structure to describe the
    /// configuration , options and defaults.
    ///
    /////////////////////////////////////////////////////////////////////////
    class Configurator
    {
    private:
    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the list of filters to be an empty list.
        ///
        /////////////////////////////////////////////////////////////////////////
        Configurator();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Virtual Destructor
        /////////////////////////////////////////////////////////////////////////
        virtual ~Configurator();

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Configure a filter.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void FilterConfig() = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Configure a Handler.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void HandlerConfig() = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Configure a Logger.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void LoggerConfig() = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Configure a Logger.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void FilterConfig() = 0;

        /////////////////////////////////////////////////////////////////////////
        ///
        /// \brief Configure a Logger.
        ///
        /////////////////////////////////////////////////////////////////////////
        virtual void FormatterConfig() = 0;
    };

#define JE_LOG_CONFIGURATOR
#endif // JE_LOG_CONFIGURATOR

#pragma endregion // Configurator

#pragma region DefaultLogger
#if !defined(JE_LOG_DEFAULT_LOGGER)

    /////////////////////////////////////////////////////////////////////////
    /// \brief Logging Configurator
    ///
    /// The configurator which defines some useful defaults and options.
    ///
    /// Configure logging using a Data type or Data Structure to describe the
    /// configuration , options and defaults.
    ///
    /////////////////////////////////////////////////////////////////////////
    class DefaultLogger
    {
    private:
    public:
        /////////////////////////////////////////////////////////////////////////
        /// \brief Initialize the list of filters to be an empty list.
        ///
        /////////////////////////////////////////////////////////////////////////
        DefaultLogger() = delete;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Delete The Copy Constructor.
        ///
        /////////////////////////////////////////////////////////////////////////
        DefaultLogger(const DefaultLogger &) = delete;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Delete The Copy Asignment Operator.
        ///
        /////////////////////////////////////////////////////////////////////////
        DefaultLogger &operator=(const DefaultLogger &) = delete;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Virtual Destructor
        /////////////////////////////////////////////////////////////////////////
        ~DefaultLogger() = delete;

        static Logger &Get();
    };

#define JE_LOG_DEFAULT_LOGGER
#endif // JE_LOG_DEFAULT_LOGGER

#pragma endregion // DefaultLogger

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
    LogRecord MakeLogRecord(char *name, JeLog::Level level, JeLog::Src_Loc srcLoc,
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
    LogRecord Log(Src_Loc loc, JeLog::Level level, T message);

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
    LogRecord Log(Src_Loc loc, JeLog::Level level, char *format, Args &&...args);

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
    LogRecord Log(clock::time_point log_time, Src_Loc loc, JeLog::Level level, T message);

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
    LogRecord Log(clock::time_point log_time, Src_Loc loc, JeLog::Level level, char *format, Args... args);

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
    LogRecord Trace(Src_Loc loc, T message);

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
    LogRecord Trace(Src_Loc loc, char *format, Args &&...args);

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
    LogRecord Trace(clock::time_point log_time, Src_Loc loc, T message);

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
    LogRecord Trace(clock::time_point log_time, Src_Loc loc, char *format, Args... args);

    ///// Error

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "ERROR" severity.
    ///
    /// \param message message to Log.
    ///
    /// logger.Error("Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Error(T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "ERROR" severity.
    ///
    /// \param format log format.
    /// \param ...args  Argument to Log.
    ///
    /// logger.Error("Hello %s !", name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Error(char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "ERROR" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Error(loc,"Hello Zeke!");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Error(Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "ERROR" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Error(loc,"Hello %s!",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Error(Src_Loc loc, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "ERROR" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Error(time,loc,"Hello Zeke");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Error(clock::time_point log_time, Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "ERROR" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Error(time,loc,"Hello %s",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Error(clock::time_point log_time, Src_Loc loc, char *format, Args... args);

    //// Warning

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "WARNING" severity.
    ///
    /// \param message message to Log.
    ///
    /// logger.Warning("Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Warning(T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "WARNING" severity.
    ///
    /// \param format log format.
    /// \param ...args  Argument to Log.
    ///
    /// logger.Warning("Hello %s !", name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Warning(char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "WARNING" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Warning(loc,"Hello Zeke!");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Warning(Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "WARNING" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Warning(loc,"Hello %s!",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Warning(Src_Loc loc, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "WARNING" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Warning(time,loc,"Hello Zeke");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Warning(clock::time_point log_time, Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "WARNING" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Warning(time,loc,"Hello %s",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Warning(clock::time_point log_time, Src_Loc loc, char *format, Args... args);

    //// Critical

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "CRITICAL" severity.
    ///
    /// \param message message to Log.
    ///
    /// logger.Critical("Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Critical(T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "CRITICAL" severity.
    ///
    /// \param format log format.
    /// \param ...args  Argument to Log.
    ///
    /// logger.Critical("Hello %s !", name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Critical(char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "CRITICAL" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Critical(loc,"Hello Zeke!");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Critical(Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "CRITICAL" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Critical(loc,"Hello %s!",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Critical(Src_Loc loc, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "CRITICAL" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Critical(time,loc,"Hello Zeke");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Critical(clock::time_point log_time, Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "CRITICAL" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Critical(time,loc,"Hello %s",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Critical(clock::time_point log_time, Src_Loc loc, char *format, Args... args);

    ////// Info

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "INFO" severity.
    ///
    /// \param message message to Log.
    ///
    /// logger.Info("Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Info(T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "INFO" severity.
    ///
    /// \param format log format.
    /// \param ...args  Argument to Log.
    ///
    /// logger.Info("Hello %s !", name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Info(char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "INFO" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Info(loc,"Hello Zeke!");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Info(Src_Loc, T);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "INFO" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Info(loc,"Hello %s!",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Info(Src_Loc loc, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "INFO" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Info(time,loc,"Hello Zeke");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Info(clock::time_point log_time, Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "INFO" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Info(time,loc,"Hello %s",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Info(clock::time_point log_time, Src_Loc loc, char *format, Args... args);

    ///// Debug

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "DEBUG" severity.
    ///
    /// \param message message to Log.
    ///
    /// logger.Debug("Hello World");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Debug(T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "DEBUG" severity.
    ///
    /// \param format log format.
    /// \param ...args  Argument to Log.
    ///
    /// logger.Debug("Hello %s !", name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Debug(char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "DEBUG" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Debug(loc,"Hello Zeke!");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Debug(Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "DEBUG" severity with source location info.
    ///
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Debug(loc,"Hello %s!",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Debug(Src_Loc loc, char *format, Args &&...args);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log 'message' with "DEBUG" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param message message to Log.
    ///
    /// logger.Debug(time,loc,"Hello Zeke");
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename T>
    LogRecord Debug(clock::time_point log_time, Src_Loc loc, T message);

    /////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Log '..args' with "DEBUG" severity with source and time info.
    ///
    /// \param log_time time of Logging.
    /// \param src_loc source location of Log.
    /// \param format log format.
    /// \param ...args  Arguments to Log.
    ///
    /// logger.Debug(time,loc,"Hello %s",name);
    ///
    /////////////////////////////////////////////////////////////////////////
    template <typename... Args>
    LogRecord Debug(clock::time_point, Src_Loc, char *, Args...);

#pragma endregion // Basics

}; // namespace JeLog

#pragma endregion // Declarations

// O------------------------------------------------------------------------------O
// | Je-Log Definitions                                                        |
// O------------------------------------------------------------------------------O
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

    const char *NameFromLevel(Level level) noexcept
    {
        if (level == Level::trace)
        {
            return JELOG_LEVEL_NAME_TRACE;
        }
        else if (level == Level::warn)
        {
            return JELOG_LEVEL_NAME_WARNING;
        }
        else if (level == Level::error)
        {
            return JELOG_LEVEL_NAME_ERROR;
        }
        else if (level == Level::critical)
        {
            return JELOG_LEVEL_NAME_CRITICAL;
        }
        else if (level == Level::debug)
        {
            return JELOG_LEVEL_NAME_DEBUG;
        }
        else
        {
            return JELOG_LEVEL_NAME_UNKNOWN;
        }
    };

    Level LevelFromName(const char *name) noexcept
    {
        if (name == JELOG_LEVEL_NAME_TRACE)
        {
            return Level::trace;
        }
        else if (name == JELOG_LEVEL_NAME_WARNING)
        {
            return Level::warn;
        }
        else if (name == JELOG_LEVEL_NAME_DEBUG)
        {
            return Level::debug;
        }
        else if (name == JELOG_LEVEL_NAME_ERROR)
        {
            return Level::error;
        }
        else if (name == JELOG_LEVEL_NAME_CRITICAL)
        {
            return Level::critical;
        }
        else
        {
            return Level::unknown;
        }
    };

#pragma endregion // Level

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
    };

    std::chrono::duration<double> StopWatch::Elapsed() const
    {
        return std::chrono::duration<double>(clock::now() - m_Start);
    };

    std::chrono::milliseconds StopWatch::ElapsedMS() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_Start);
    };

    void StopWatch::Reset()
    {
        m_Start = clock::now();
    };

    // #define JE_LOG_JE_TIME
    // #endif // JE_LOG_JE_TIME

#pragma endregion // JeTime

#pragma region SourceLocation

    // #if !defined(JE_LOG_SOURCE_LOCATION)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Src_Loc
    //-----------------------------------------------------------------------------
    // - Src_Loc()
    // - ~Src_Loc()
    // - Empty()
    //-----------------------------------------------------------------------------

    Src_Loc::Src_Loc() = default;

    Src_Loc::Src_Loc(char *filename, int line, char *funcname)
    {
        m_FileName = filename;
        m_Line = line;
        m_FuncName = funcname;
    };

    constexpr bool Src_Loc::Empty() const noexcept
    {
        return m_Line <= 0;
    };

    // #define JE_LOG_SOURCE_LOCATION
    // #endif // JE_LOG_SOURCE_LOCATION

#pragma endregion // SourceLocation

#pragma region LogRecord

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::LogRecord
    //-----------------------------------------------------------------------------
    // - LogRecord()
    // - ~LogRecord()
    // - GetName()
    // - GetLevel()
    // - GetMessage()
    // - GetFunction()
    // - Name()
    // - Level()
    // - Message()
    // - Function()
    // - GetFileName()
    // - GetLineNo()
    // - GetThreadID()
    // - GetThreadName()
    //-----------------------------------------------------------------------------

    // #if !defined(JE_LOG_LOG_RECORD)

    LogRecord::LogRecord()
    {
        m_Name;
        m_Level;
        m_ThreadID;
        m_Msg;
        m_ThreadName;
        m_CreatedTime;
    };

    LogRecord::LogRecord(char *name, JeLog::Level level, JeLog::Src_Loc srcLoc, JeLog::Time creationTime, char *message, uint32_t threadID)
    {
        m_Name = name;
        m_Level = level;
        m_ThreadID = threadID;
        m_Msg = message;
        m_ThreadName = "NULL";
        m_CreatedTime = creationTime;
    };

    LogRecord::~LogRecord() {};

    char *LogRecord::Name()
    {
        return m_Name;
    };

    JeLog::Level LogRecord::Level()
    {
        return m_Level;
    };

    void LogRecord::SetName(char *name)
    {
        // assert if name is not char* type
        m_Name = name;
    };

    void LogRecord::SetLevel(JeLog::Level level)
    {
        // assert if level is not int type
        m_Level = level;
    };

    char *LogRecord::Message()
    {
        return m_Msg;
    };

    void LogRecord::SetMessage(char *message)
    {
        // assert if message is not char* type
        m_Msg = message;
    };

    char *LogRecord::Function()
    {
        return m_SrcLoc.m_FuncName;
    };

    void LogRecord::SetFunction(char *function)
    {
        // assert if function is not char* type
        m_SrcLoc.m_FuncName = function;
    };

    char *LogRecord::FileName()
    {
        return m_SrcLoc.m_FileName;
    };

    void LogRecord::SetFileName(char *filename)
    {
        m_SrcLoc.m_FileName = filename;
    };

    int LogRecord::LineNo()
    {
        return m_SrcLoc.m_Line;
    };

    void LogRecord::SetLineNo(int line)
    {
        m_SrcLoc.m_Line = line;
    };

    int LogRecord::ThreadID()
    {
        return m_ThreadID;
    };

    void LogRecord::SetThreadID(int threadID)
    {
        m_ThreadID = threadID;
    };

    char *LogRecord::ThreadName()
    {
        return m_ThreadName;
    };

    void LogRecord::SetThreadName(char *threadName)
    {
        m_ThreadName = threadName;
    };

    JeLog::Time LogRecord::CreationTime()
    {
        return m_CreatedTime;
    };

    void LogRecord::SetCreationTime(JeLog::Time createdTime)
    {
        m_CreatedTime = createdTime;
    };

    // #define JE_LOG_LOG_RECORD
    // #endif // JE_LOG_LOG_RECORD

#pragma endregion // LogRecord

#pragma region Formatter

    // #if !defined(JE_LOG_FORMATTER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Formatter
    //-----------------------------------------------------------------------------
    // - Formatter()
    // - ~Formatter()
    // - Format()
    // - TimeFormat()
    // - MessageFormat()
    //-----------------------------------------------------------------------------

    Formatter::Formatter(char *fmt = NULL, char *datefmt = NULL)
    {
        m_FMT = fmt;
        m_DateFMT = datefmt;
    };

    Formatter::~Formatter() {};

    LogRecord Formatter::SetPattern(LogRecord &logRecord) {};

    char *Formatter::TimeFormat(LogRecord &logRecord, char *datefmt = NULL) {
    };

    char *Formatter::MessageFormat(LogRecord &logRecord, char *msgfmt = NULL) {};

    // #define JE_LOG_FORMATTER
    // #endif // JE_LOG_FORMATTER

#pragma endregion // Formatter

#pragma region TextFormatter

    // #if !defined(JE_LOG_TEXT_FORMATTER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::TextFormatter
    //-----------------------------------------------------------------------------
    // - TextFormatter()
    // - ~TextFormatter()
    // - Format()
    // - TimeFormat()
    // - MessageFormat()
    // - BeginSession()
    // - EndSession()
    // - WriteHead()
    // - WriteFoot()
    //-----------------------------------------------------------------------------

    TextFormatter::TextFormatter(char *fmt = NULL, char *datefmt = NULL) {};

    TextFormatter::TextFormatter() {};

    TextFormatter::~TextFormatter() {};

    LogRecord TextFormatter::Format(LogRecord &logRecord) {};

    char *TextFormatter::TimeFormat(LogRecord &logRecord, char *datefmt = NULL) {};

    char *TextFormatter::MessageFormat(LogRecord &logRecord, char *msgfmt = NULL) {};

    void TextFormatter::BeginSession() {};

    void TextFormatter::EndSession() {};

    void TextFormatter::WriteHead() {};

    void TextFormatter::WriteFoot() {};

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
    // - Format()
    // - TimeFormat()
    // - MessageFormat()
    // - BeginSession()
    // - EndSession()
    // - WriteHeader()
    // - WriteFooter()
    //-----------------------------------------------------------------------------

    JsonFormatter::JsonFormatter(char *fmt = NULL, char *datefmt = NULL) {};

    JsonFormatter::~JsonFormatter() {};

    LogRecord JsonFormatter::Format(LogRecord &logRecord)
    {
        std::lock_guard<std::mutex> lock(m_lock);

        m_OutputStream << "{";
        m_OutputStream << "\"Name\":\"" << logRecord.Name() << "\",";
        m_OutputStream << "\"Level\":\"" << logRecord.Level() << "\",";
        m_OutputStream << "\"Message\":\"" << logRecord.Message() << "\",";
        m_OutputStream << "\"LineNo\":\"" << logRecord.LineNo() << "\",";
        m_OutputStream << "\"Function\":\"" << logRecord.Function() << "\",";
        m_OutputStream << "\"FileName\":\"" << logRecord.FileName() << "\",";
        m_OutputStream << "\"ThreadID\":\"" << logRecord.ThreadID() << "\",";
        m_OutputStream << "\"ThreadName\":\"" << logRecord.ThreadName() << "\",";
        // m_OutputStream << "\"CreationTime\":\"" << logRecord.CreationTime();
        m_OutputStream << "}\n";

        m_OutputStream.flush();
        return logRecord;
    };

    char *JsonFormatter::TimeFormat(LogRecord &logRecord, char *datefmt = NULL) {};

    char *JsonFormatter::MessageFormat(LogRecord &logRecord, char *msgfmt = NULL) {};

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

#pragma region Filter
    // #if !defined(JE_LOG_FILTER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Filter
    //-----------------------------------------------------------------------------
    // - Filter()
    // - ~Filter()
    // - filter()
    // - Name()
    //-----------------------------------------------------------------------------

    Filter::Filter()
    {
        m_Name = "";
    };

    Filter::Filter(char *name)
    {
        m_Name = name;
    };

    char *Filter::Name()
    {
        return m_Name;
    };

    void Filter::Name(char *name)
    {
        m_Name = name;
    };

    Filter::~Filter() {};

    LogRecord Filter::filter(LogRecord &logRecord) {};

    // #define JE_LOG_FILTER
    // #endif // JE_LOG_FILTER

#pragma endregion // Filter

#pragma region Filterer
    // #if !defined(JE_LOG_FILTERER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Filterer
    //-----------------------------------------------------------------------------
    // - Filterer()
    // - ~Filterer()
    // - AddFilter()
    // - RemoveFilter()
    // - filter()
    //-----------------------------------------------------------------------------

    Filterer::Filterer() {};

    Filterer::~Filterer() {};

    void Filterer::AddFilter(Filter &filter) {};

    void Filterer::RemoveFilter(Filter &filter) {};

    LogRecord Filterer::filter(Filter &filter, LogRecord &logRecord) {};

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
        m_Active = true;
        m_Formatter = 0;
        // m_Filterer = 0;
    };

    // Handler::~Handler() {};

    char *Handler::Name()
    {
        return m_Name;
    };

    void Handler::Format(LogRecord &logRecord) {};

    void Handler::Log(LogRecord &logRecord) {
        // #include <assert.h>
        //         assert(false);
        // static_assert(false);
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

        m_Name;
        m_Level;
        m_Handlers;

        StreamHandler streamHandler;
        m_Handlers.push_back(streamHandler);

        // FileHandler fileHandler;
        // m_Handlers.push_back(fileHandler);
    };

    template <typename T>
    Logger::Logger(T name)
    {
        m_Name = name;
        m_Level;
        m_Handlers;
    };

    template <typename... Args>
    Logger::Logger(Args &&...args){};

    Logger::Logger(const Logger &other) {};

    Logger::Logger(Logger &&other) {};

    template <typename T>
    Logger::Logger(T name, Handler &handler)
    {
        m_Name = name;
        m_Handlers.push_back(handler)
    };

    template <typename T>
    Logger::Logger(T name, std::vector<Handler> &handlers)
    {
        m_Name = name;
        m_Level;
        m_Handlers = handlers
    };

    Logger &Logger::operator=(Logger other) {};

    void Logger::SetName(char *name)
    {
        m_Name = name;
    };

    char *Logger::Name() const
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

    void Logger::SetFormatter(Formatter &formatter)
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
    void Logger::_Log(clock::time_point creationTime, Src_Loc srcLoc, JeLog::Level level, char *fmt, Args &&...args)
    {
        char *message;

        // long long createdTime = std::chrono::time_point_cast<std::chrono::microseconds>(Timepoint).time_since_epoch().count();

        bool isEnabled = IsEnabledFor(level);

        if (!isEnabled)
        {
            return;
        }

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        LogRecord logRecord = MakeLogRecord(m_Name, level, srcLoc, creationTime, message, threadID);

        if (logRecord.m_SrcLoc.m_FileName == "")
        {
            logRecord.m_SrcLoc.m_FileName = __FILE__;
        }
        if (logRecord.m_SrcLoc.m_FuncName == "")
        {
            logRecord.m_SrcLoc.m_FuncName == "Undefined";
        }
        if (logRecord.m_SrcLoc.m_Line == 0)
        {
            logRecord.m_SrcLoc.m_Line = __LINE__;
        }
        if (logRecord.m_CreatedTime.m_MilliSeconds == 0)
        {
            logRecord.m_CreatedTime.m_MilliSeconds = JeLog::StopWatch::ElapsedMS().count();
        }

        for (auto &handler : m_Handlers)
        {
            handler.Log(logRecord);
        }
    };

    template <typename T>
    void Logger::_Log(clock::time_point creationTime, Src_Loc srcLoc, JeLog::Level level, T message)
    {
        // long long createdTime = std::chrono::time_point_cast<std::chrono::microseconds>(Timepoint).time_since_epoch().count();

        bool isEnabled = IsEnabledFor(level);

        if (!isEnabled)
        {
            return;
        }

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        LogRecord logRecord = MakeLogRecord(m_Name, level, srcLoc, creationTime, message, threadID);

        if (logRecord.m_SrcLoc.m_FileName == "")
        {
            logRecord.m_SrcLoc.m_FileName = __FILE__;
        }
        if (logRecord.m_SrcLoc.m_FuncName == "")
        {
            logRecord.m_SrcLoc.m_FuncName == "Undefined"
        }
        if (logRecord.m_SrcLoc.m_Line == 0)
        {
            logRecord.m_SrcLoc.m_Line = __LINE__;
        }
        if (logRecord.m_CreatedTime.m_MilliSeconds == 0)
        {
            logRecord.m_CreatedTime.m_MilliSeconds = JeLog::StopWatch::ElapsedMS().count();
        }

        for (auto &handler : m_Handlers)
        {
            handler.Log(logRecord);
        }
    };

    void Logger::AddHandler(Handler &handler)
    {
        m_Handlers.push_back(handler);
    };

    bool Logger::HasHandlers()
    {
        bool hasHanlders = false;

        if (!m_Handlers.empty())
        {
            hasHanlders = true;
        }

        return hasHanlders;
    };

    LogRecord Logger::Record()
    {
        JeLog::Time creationTime;
        JeLog::Src_Loc srcLoc(__FILE__, __LINE__, "__FUNCSIG__");

        long long createdTime = std::chrono::time_point_cast<std::chrono::microseconds>(Timepoint).time_since_epoch().count();
        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        LogRecord logRecord = MakeLogRecord(m_Name, m_Level, srcLoc, creationTime, "", threadID);

        return logRecord;
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
    LogRecord Logger::Log(Src_Loc srcLoc, JeLog::Level level, T message)
    {
        _Log({}, srcLoc, level, message);
    };

    template <typename... Args>
    LogRecord Logger::Log(Src_Loc srcLoc, JeLog::Level level, char *format, Args &&...args)
    {
        _Log({}, srcLoc, level, format, std::forward<Args>(args)...);
    };

    template <typename T>
    LogRecord Logger::Log(clock::time_point creationTime, Src_Loc srcLoc, JeLog::Level level, T message)
    {
        _Log(creationTime, srcLoc, level, message);
    };

    template <typename... Args>
    LogRecord Logger::Log(clock::time_point creationTime, Src_Loc srcLoc, JeLog::Level level, char *format, Args... args)
    {
        _Log(creationTime, srcLoc, level, format, std::forward<Args>(args)...);
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
    LogRecord Logger::Trace(Src_Loc srcLoc, T message)
    {
        Log(srcLoc, JeLog::Level::trace, message);
    };

    template <typename... Args>
    LogRecord Logger::Trace(Src_Loc srcLoc, char *format, Args &&...args)
    {
        Log({}, srcLoc, JeLog::Level::trace, format, std::forward<Args>(args)...);
    };

    template <typename T>
    LogRecord Logger::Trace(clock::time_point creationTime, Src_Loc srcLoc, T message)
    {
        Log(creationTime, srcLoc, JeLog::Level::trace, message);
    };

    template <typename... Args>
    LogRecord Logger::Trace(clock::time_point creationTime, Src_Loc srcLoc, char *format, Args... args)
    {
        Log(creationTime, srcLoc, JeLog::Level::trace, format, std::forward<Args>(args)...);
    };

    ///// Error

    template <typename T>
    LogRecord Logger::Error(T message) {};

    template <typename... Args>
    LogRecord Logger::Error(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Error(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Error(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Error(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Error(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    //// Warning

    template <typename T>
    LogRecord Logger::Warning(T message) {};

    template <typename... Args>
    LogRecord Logger::Warning(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Warning(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Warning(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Warning(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Warning(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    //// Critical

    template <typename T>
    LogRecord Logger::Critical(T message) {};

    template <typename... Args>
    LogRecord Logger::Critical(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Critical(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Critical(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Critical(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Critical(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    ////// Info

    template <typename T>
    LogRecord Logger::Info(T message) {};

    template <typename... Args>
    LogRecord Logger::Info(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Info(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Info(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Info(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Info(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    ///// Debug

    template <typename T>
    LogRecord Logger::Debug(T message) {};

    template <typename... Args>
    LogRecord Logger::Debug(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Debug(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Debug(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Logger::Debug(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Logger::Debug(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    // #define JE_LOG_LOG_LOGGER
    // #endif // JE_LOG_LOG_LOGGER

#pragma endregion // Logger

#pragma region Configurator
    // #if !defined(JE_LOG_CONFIGURATOR)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Configurator
    //-----------------------------------------------------------------------------
    // - Configurator()
    // - ~Configurator()
    // - Convert()
    //-----------------------------------------------------------------------------

    Configurator::Configurator() {};

    Configurator::~Configurator() {};

    // virtual void Convert() = 0;

    // virtual void HandlerConfig() = 0;

    // virtual void LoggerConfig() = 0;

    // virtual void FilterConfig() = 0;

    // virtual void FormatterConfig() = 0;

    // #define JE_LOG_CONFIGURATOR
    // #endif // JE_LOG_CONFIGURATOR

#pragma endregion // Configurator

#pragma region DefaultLogger

    // #if !defined(JE_LOG_DEFAULT_LOGGER)

    Logger &DefaultLogger::Get()
    {
        static Logger instance;
        instance.SetName("DefaultLogger");
        instance.SetLevel(JeLog::Level::trace);
        return instance;
    };

    // #define JE_LOG_DEFAULT_LOGGER
    // #endif // JE_LOG_DEFAULT_LOGGER

#pragma endregion // DefaultLogger

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

    LogRecord MakeLogRecord(char *name, JeLog::Level level, JeLog::Src_Loc srcLoc,
                            JeLog::Time creationTime, char *message, int threadID) {

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
    LogRecord Log(Src_Loc loc, JeLog::Level level, T message) {};

    template <typename... Args>
    LogRecord Log(Src_Loc loc, JeLog::Level level, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Log(clock::time_point log_time, Src_Loc loc, JeLog::Level level, T message) {};

    template <typename... Args>
    LogRecord Log(clock::time_point log_time, Src_Loc loc, JeLog::Level level, char *format, Args... args) {};

    ////// Trace

    template <typename T>
    LogRecord Trace(T message) {};

    template <typename... Args>
    LogRecord Trace(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Trace(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Trace(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Trace(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Trace(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    ///// Error

    template <typename T>
    LogRecord Error(T message) {};

    template <typename... Args>
    LogRecord Error(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Error(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Error(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Error(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Error(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    //// Warning

    template <typename T>
    LogRecord Warning(T message) {};

    template <typename... Args>
    LogRecord Warning(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Warning(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Warning(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Warning(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Warning(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    //// Critical

    template <typename T>
    LogRecord Critical(T message) {};

    template <typename... Args>
    LogRecord Critical(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Critical(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Critical(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Critical(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Critical(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    ////// Info

    template <typename T>
    LogRecord Info(T message) {};

    template <typename... Args>
    LogRecord Info(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Info(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Info(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Info(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Info(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

    ///// Debug

    template <typename T>
    LogRecord Debug(T message) {};

    template <typename... Args>
    LogRecord Debug(char *format, Args &&...args) {};

    template <typename T>
    LogRecord Debug(Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Debug(Src_Loc loc, char *format, Args &&...args) {};

    template <typename T>
    LogRecord Debug(clock::time_point log_time, Src_Loc loc, T message) {};

    template <typename... Args>
    LogRecord Debug(clock::time_point log_time, Src_Loc loc, char *format, Args... args) {};

#pragma endregion // Basics
}; // namespace JeLog

#pragma endregion // Definitions

#endif // JE_LOG_JE_LOG_H
