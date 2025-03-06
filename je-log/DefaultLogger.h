#pragma once

#include <Logger.h>

#pragma region Declarations

namespace JeLog
{

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
        virtual ~DefaultLogger() = default;

        static JeLog::Logger &Get();
    };

#define JE_LOG_DEFAULT_LOGGER
#endif // JE_LOG_DEFAULT_LOGGER

#pragma endregion // DefaultLogger

} // namespace JeLog

#pragma endregion // Declarations

#pragma region Definitions

namespace JeLog
{

#pragma region DefaultLogger

    // #if !defined(JE_LOG_DEFAULT_LOGGER)

    JeLog::Logger &DefaultLogger::Get()
    {
        static JeLog::Logger instance;
        instance.SetName("DefaultLogger");
        instance.SetLevel(JeLog::Level::trace);
        return instance;
    };

    // #define defaultLogger() JeLog::DefaultLogger::Get()

    //     defaultLogger();

    // #define JE_LOG_DEFAULT_LOGGER
    // #endif // JE_LOG_DEFAULT_LOGGER

#pragma endregion // DefaultLogger

} // namespace JeLog

#pragma endregion // Definitions
