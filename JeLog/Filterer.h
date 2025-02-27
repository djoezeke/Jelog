#pragma once

#include <map>

#include "Filter.h"

#pragma region Declarations

namespace JeLog
{

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

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region Filterer
    // #if !defined(JE_LOG_FILTERER)

    //-----------------------------------------------------------------------------
    // [SECTION] JeLog::Filterer
    //-----------------------------------------------------------------------------
    // - Filterer()
    // - ~Filterer()
    // - AddFilter()
    // - RemoveFilter()
    // - Filter()
    //-----------------------------------------------------------------------------

    Filterer::Filterer() {};

    Filterer::~Filterer() {};

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

} // namespace JeLog

#pragma endregion // Definitions
