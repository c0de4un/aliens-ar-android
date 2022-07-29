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
#ifndef C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_HPP
#include "../../public/input/InputSystem.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_HPP

// Include Android NDK sensor
#ifndef ANDROID_SENSOR_H
#include <android/sensor.h>
#endif // !ANDROID_SENSOR_H

// Include Android NDK looper
#ifndef ANDROID_LOOPER_H
#include <android/looper.h>
#endif // !ANDROID_LOOPER_H

// Include STL assertions
#include <cassert>

// Include Logger
#ifndef C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP
#include "../../public/metrics/Logger.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// InputSystem
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace c0de4un
{

    namespace aliensar
    {

        namespace logic
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // FIELDS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            InputSystem *InputSystem::mInstance(nullptr);

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR & DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            InputSystem::InputSystem() noexcept
                :
                mSensorManager(nullptr),
                mRotationSensor(nullptr),
                mSensorEventsQueue(nullptr),
                mLooper(nullptr),
                mAccelerometerData
                {
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f,
                    0.0f
                }
            {
            }

            InputSystem::~InputSystem() noexcept
            {
                if (mSensorEventsQueue && mRotationSensor)
                {
                    try
                    {
                        ASensorEventQueue_disableSensor(mSensorEventsQueue, mRotationSensor);
                    }
                    catch(...) { }
                }
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            void InputSystem::initialize(ALooper *pLooper)
            {
                mSensorManager = ASensorManager_getInstanceForPackage("com.code4un.aliensar");
                assert(mSensorManager && "InputSystem::initialize: failed to retrieve sensor manager");

                mRotationSensor = ASensorManager_getDefaultSensor(mSensorManager, ASENSOR_TYPE_ACCELEROMETER);

                assert(mRotationSensor && "InputSystem::initialize: failed to retrieve accelerometer");

                // Get or Create ALooper for calling-thread (must be called from main thread when initializing)
                mLooper = pLooper ?: ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
                assert(mLooper && "InputSystem::initialize: failed to retrieve ALooper");

                mSensorEventsQueue = ASensorManager_createEventQueue(mSensorManager, pLooper, LOOPER_ID_USER, nullptr, nullptr);
                assert(mSensorEventsQueue && "InputSystem::initialize: failed to retrieve events queue");

                auto status = ASensorEventQueue_enableSensor(mSensorEventsQueue, mRotationSensor);
                assert(status >= 0 && "InputSystem::initialize: failed to enable accelerometer sensor");
            }

            InputSystem *InputSystem::Initialize(ALooper *pLooper)
            {
                if (mInstance)
                    return mInstance;

                mInstance = new InputSystem();
                if (!mInstance)
                    return mInstance;

                mInstance->initialize(pLooper);

                return mInstance;
            }

            void InputSystem::Terminate() noexcept
            {
                if (!mInstance)
                    return;

                delete mInstance;
                mInstance = nullptr;
            }

            void InputSystem::Update()
            {
                ASensorEvent event;

                while (ASensorEventQueue_getEvents(mSensorEventsQueue, &event, 1) > 0)
                {
                    mAccelerometerData.mAzimuth = event.acceleration.azimuth;
                    mAccelerometerData.mPitch = event.acceleration.pitch;
                    mAccelerometerData.mRoll = event.acceleration.roll;
                }

                std::string logMsg("Accelerometer: Azimuth=");
                logMsg += std::to_string(mAccelerometerData.mAzimuth);
                logMsg += "; Pitch=";
                logMsg += std::to_string(mAccelerometerData.mPitch);
                logMsg += "; Roll=";
                logMsg += std::to_string(mAccelerometerData.mRoll);
                arLog::debug(logMsg.c_str());
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        }

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
