#pragma once
#include <cstdint>

// O------------------------------------------------------------------------------O
// | Je-Log Declarations                                                          |
// O------------------------------------------------------------------------------O
#pragma region Declarations

namespace JeLog
{

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

}; // namespace JeLog

// O------------------------------------------------------------------------------O
// | Je-Log Definitions                                                          |
// O------------------------------------------------------------------------------O
#pragma region Definitions
namespace JeLog
{
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

}; // namespace JeLog

#pragma endregion // Definitions
