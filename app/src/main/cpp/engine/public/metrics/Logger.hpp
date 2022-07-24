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

#ifndef C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP
#define C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TYPES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace c0de4un
{

    namespace aliensar
    {

        namespace logic
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // Logger
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            class Logger final
            {

            private:

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // FIELDS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                static Logger *mInstance;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // CONSTRUCTOR
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                explicit Logger() noexcept;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // METHODS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                static void print(unsigned char level, const char *const pMsg);

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            public:

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // CONSTANTS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                static constexpr const unsigned char LEVEL_INFO     = 1;
                static constexpr const unsigned char LEVEL_DEBUG    = 2;
                static constexpr const unsigned char LEVEL_WARNING  = 3;
                static constexpr const unsigned char LEVEL_ERROR    = 4;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // DESTRUCTOR
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                ~Logger() noexcept;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // METHODS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                static void Initialize() noexcept;
                static void Terminate() noexcept;

                static void info(const char* const pMsg);
                static void debug(const char* const pMsg);
                static void warning(const char* const pMsg);
                static void error(const char* const pMsg);

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            };

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        }

    }

}
using arLog = c0de4un::aliensar::logic::Logger;
#define C0DE4UN_ALIENS_AR_ENGINE_LOGGER_DECL

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif // !C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP
