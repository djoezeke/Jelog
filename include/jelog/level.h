#pragma once

#include <string>

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
#define JELOG_LEVEL_OFF 6

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
        off = JELOG_LEVEL_OFF,
        n_levels
    };

#define JELOG_LEVEL_NAME_INFO std::string("off")
#define JELOG_LEVEL_NAME_INFO std::string("INFO")
#define JELOG_LEVEL_NAME_TRACE std::string("TRACE")
#define JELOG_LEVEL_NAME_DEBUG std::string("DEBUG")
#define JELOG_LEVEL_NAME_ERROR std::string("ERROR")
#define JELOG_LEVEL_NAME_UNKNOWN std::string("UNKNOWN")
#define JELOG_LEVEL_NAME_WARNING std::string("WARNING")
#define JELOG_LEVEL_NAME_CRITICAL std::string("CRITICAL")

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

}; // namespace JeLog

#pragma endregion // Declarations

// O------------------------------------------------------------------------------O
// | Je-Log Definitions                                                          |
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

}; // namespace JeLog

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