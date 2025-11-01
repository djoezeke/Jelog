#pragma once

#include <Jelog/Logger.h>

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