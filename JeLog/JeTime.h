#pragma once

#include <chrono>

#pragma region Declarations

namespace JeLog
{

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

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Declarations

namespace JeLog
{

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

} // namespace JeLog

#pragma endregion // Declarations
