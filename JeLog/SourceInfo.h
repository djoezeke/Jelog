#pragma once

// O------------------------------------------------------------------------------O
// | Je-Log Declarations                                                          |
// O------------------------------------------------------------------------------O
#pragma region Declarations

namespace JeLog
{

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

}; // namespace JeLog

// O------------------------------------------------------------------------------O
// | Je-Log Definitions                                                          |
// O------------------------------------------------------------------------------O
#pragma region Definitions
namespace JeLog
{
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

}; // namespace JeLog

#pragma endregion // Definitions
