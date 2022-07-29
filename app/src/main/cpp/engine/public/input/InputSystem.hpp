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

#ifndef C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_HPP
#define C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include STL numeric
#include <cstdint>

// Include RotationData
#ifndef C0DE4UN_ALIENS_AR_ENGINE_ACCELEROMETER_DATA_HPP
#include "AccelerometerData.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_ACCELEROMETER_DATA_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FORWARD-DECLARATIONS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Forward-Declare ASensor
#if !defined(ANDROID_SENSOR_H) && !defined(ANDROID_ASENSOR_DECL) && !defined(ASensor)
#define ANDROID_ASENSOR_DECL
struct ASensor;
struct ASensorManager;
struct ASensorEventQueue;
#endif // !ANDROID_SENSOR_H

// Forward-Declare ALooper
#if !defined(ANDROID_LOOPER_H) && !defined(ALooper) && !defined(ANDROID_LOOPER_DECL)
#define ANDROID_LOOPER_DECL
struct ALooper;
#endif

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

            class InputSystem final
            {

            private:

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // CONSTANTS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                static constexpr const int LOOPER_ID_USER               = 3;
                static constexpr const int SENSOR_HISTORY_LENGTH        = 100;
                static constexpr const int SENSOR_REFRESH_RATE_HZ       = 100;
                static constexpr const int32_t SENSOR_REFRESH_PERIOD_US = int32_t(1000000 / SENSOR_REFRESH_RATE_HZ);
                static constexpr const float SENSOR_FILTER_ALPHA        = 0.1f;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // FIELDS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                static InputSystem *mInstance;

                ASensorManager    *mSensorManager;
                const ASensor     *mRotationSensor;
                ASensorEventQueue *mSensorEventsQueue;
                ALooper           *mLooper;
                AccelerometerData mAccelerometerData;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // CONSTRUCTOR
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                explicit InputSystem() noexcept;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // METHODS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                void initialize(ALooper *const pLooper);

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            public:

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // DESTRUCTOR
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                ~InputSystem() noexcept;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // METHODS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                static InputSystem *Initialize(ALooper *pLooper);
                static void Terminate() noexcept;

                void Update();

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            };

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        }

    }

}

using arInput = c0de4un::aliensar::logic::InputSystem;
#define C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_DECL

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif // !C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_HPP
