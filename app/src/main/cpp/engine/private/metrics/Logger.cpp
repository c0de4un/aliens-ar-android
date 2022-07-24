/**
 * All rights reserved.
 * License: see LICENSE.txt
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must display the names 'Denis Zyamaev' and
 * in the credits of the application, if such credits exist.
 * The authors of this work must be notified via email (code4un@yandex.ru) in
 * this case of redistribution.
 * 3. Neither the name of copyright holders nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
*/

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// HEADER
#ifndef C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP
#include "../../public/metrics/Logger.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP

// Android Logcat
#include <android/log.h>
#include <sstream>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Logger
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace c0de4un
{

    namespace aliensar
    {

        namespace logic
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTANTS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            Logger *Logger::mInstance(nullptr);

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR & DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            Logger::Logger() noexcept = default;

            Logger::~Logger() noexcept = default;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            void Logger::print(unsigned char level, const char * pMsg)
            {
                if (!mInstance) // IDE is lying, it can be nullptr
                    return;

                static int converter[4]{
                        ANDROID_LOG_INFO,
                        ANDROID_LOG_DEBUG,
                        ANDROID_LOG_WARN,
                        ANDROID_LOG_ERROR
                };
                const int androidLevel = converter[level];

                __android_log_print(androidLevel, "Aliens-AR", "%s", pMsg);
            }

            void Logger::Initialize() noexcept
            {
                if (mInstance)
                    return;

                mInstance = new Logger();
            }

            void Logger::Terminate() noexcept
            {
                if (mInstance)
                    return;

                mInstance = nullptr;
                delete mInstance;
            }

            void Logger::info(const char* const pMsg)
            {
                mInstance->print(LEVEL_INFO, pMsg);
            }

            void Logger::debug(const char* const pMsg)
            {
                mInstance->print(LEVEL_DEBUG, pMsg);
            }

            void Logger::warning(const char* const pMsg)
            {
                mInstance->print(LEVEL_WARNING, pMsg);
            }

            void Logger::error(const char* const pMsg)
            {
                mInstance->print(LEVEL_ERROR, pMsg);
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        }

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
