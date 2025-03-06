#pragma once

#include "LogRecord.h"

#pragma region Declarations

namespace JeLog
{

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
    protected:
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
        Filter(char *name);

        /////////////////////////////////////////////////////////////////////////
        /// \brief Return the Name for this LogRecord.
        ///
        /////////////////////////////////////////////////////////////////////////
        const char *Name();

        /////////////////////////////////////////////////////////////////////////
        /// \brief Set the Name Log which the LogRecord was Created.
        ///
        /// \param name
        ///
        /////////////////////////////////////////////////////////////////////////
        void Name(char *name);

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

        virtual ~Filter();

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

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

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

    const char *Filter::Name()
    {
        return m_Name;
    };

    void Filter::Name(char *name)
    {
        m_Name = name;
    };

    Filter::~Filter() {};

    // #define JE_LOG_FILTER
    // #endif // JE_LOG_FILTER

#pragma endregion // Filter

} // namespace JeLog

#pragma endregion // Definitions
