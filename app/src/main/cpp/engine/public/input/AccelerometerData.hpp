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

#ifndef C0DE4UN_ALIENS_AR_ENGINE_ACCELEROMETER_DATA_HPP
#define C0DE4UN_ALIENS_AR_ENGINE_ACCELEROMETER_DATA_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

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

            struct AccelerometerData final
            {
                float mX;
                float mY;
                float mZ;

                float mAzimuth;
                float mPitch;
                float mRoll;
            };

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        }

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

using arAccelerometerData = c0de4un::aliensar::logic::AccelerometerData;
#define C0DE4UN_ALIENS_AR_ENGINE_ACCELEROMETER_DATA_DECL

#endif //C0DE4UN_ALIENS_AR_ENGINE_ACCELEROMETER_DATA_HPP
