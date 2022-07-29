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

// Android
#include <jni.h>
#include <string>
#include <game-activity/GameActivity.cpp>
#include <game-text-input/gametextinput.cpp>

// Game
// Include Logger
#ifndef C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP
#include "engine/public/metrics/Logger.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_LOGGER_HPP

// Include GLRenderer
#ifndef C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_HPP
#include "engine/public/render/GLRenderer.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_HPP

// Include InputSystem
#ifndef C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_HPP
#include "engine/public/input/InputSystem.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_INPUT_SYSTEM_HPP

#define ANDROID_GLUE_APP_DECL
extern "C"
{
    #include <game-activity/native_app_glue/android_native_app_glue.c>

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // MAIN
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    /*!
     * Handles commands sent to this Android application
     * @param pApp the app the commands are coming from
     * @param cmd the command to handle
     */
    void handle_cmd(struct android_app *pApp, int32_t cmd)
    {
        switch (cmd)
        {
            case APP_CMD_INIT_WINDOW:
            {
                // A new window is created, associate a renderer with it. You may replace this with a
                // "game" class if that suits your needs. Remember to change all instances of userData
                // if you change the class here as a reinterpret_cast is dangerous this in the
                // android_main function and the APP_CMD_TERM_WINDOW handler case.
                auto *const renderer( new c0de4un::aliensar::gl::GLRenderer(pApp) );
                renderer->Load();

                pApp->userData = renderer;
            }
                break;

            case APP_CMD_TERM_WINDOW:
                // The window is being destroyed. Use this to clean up your userData to avoid leaking
                // resources.
                //
                // We have to check if userData is assigned just in case this comes in really quickly
                if (pApp->userData) {
                    auto *pRenderer = reinterpret_cast<::arGLRenderer *>(pApp->userData);
                    pApp->userData = nullptr;
                    delete pRenderer;
                }
                break;

            default:
                break;
        }
    }

    // GameActivity entry point
    void android_main(android_app* pApp)
    {
        // Disable events filter to receive them from all devices
        android_app_set_key_event_filter(pApp, nullptr);
        android_app_set_motion_event_filter(pApp, nullptr);

        // register an event handler for Android events
        pApp->onAppCmd = handle_cmd;

        // This sets up a typical game/event loop. It will run until the app is destroyed.
        int events;
        android_poll_source *pSource;

        // Initialize Logger
        arLog::Initialize();
        arLog::info("Starting app ...");

        // Initialize InputSystem
        arInput *const inputSystem(arInput::Initialize(pApp->looper));

        do {
            // Process all pending events before running game logic.
            if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
                if (pSource) {
                    pSource->process(pApp, pSource);
                }
            }

            inputSystem->Update();

            // Check if any user data is associated. This is assigned in handle_cmd
            if (pApp->userData) {
                // We know that our user data is a Renderer, so reinterpret cast it. If you change your
                // user data remember to change it here
                auto *pRenderer = reinterpret_cast<::arGLRenderer *>(pApp->userData);

                // Render a frame
                pRenderer->Render();

                // clear inputs, be careful as this will clear it for anyone listening to these events
                android_app_clear_motion_events(pApp->inputBuffers);
            }
        } while (!pApp->destroyRequested);

        // Terminate InputSystem
        arInput::Terminate();

        // Terminate Logger
        arLog::info("Stopping app ...");
        arLog::Terminate();
    }
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
