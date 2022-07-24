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

#ifndef C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_HPP
#define C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include Android EGL
#include <EGL/egl.h>

// Include STL memory
#include <memory>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Forward-Declarations
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifndef ANDROID_GLUE_APP_DECL
#define ANDROID_GLUE_APP_DECL
struct android_app;
#endif // !ANDROID_GLUE_APP_DECL

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TYPES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace c0de4un
{

    namespace aliensar
    {

        namespace gl
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // c0de4un::aliensar::gl::GLRenderer
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            /// GLRenderer
            class GLRenderer final
            {
            private:

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // CONSTANTS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // FIELDS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                android_app *app_;
                EGLDisplay display_;
                EGLSurface surface_;
                EGLContext context_;
                EGLint width_;
                EGLint height_;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // METHODS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                inline void updateRenderArea();

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            public:

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // CONSTRUCTOR & DESTRUCTOR
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                explicit GLRenderer(android_app *pApp);

                ~GLRenderer() noexcept;

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                // METHODS
                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

                /// Handles OpenGL Context
                /// Loads Assets
                void Load();

                /// Render
                void Render();

                // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            };

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        }

    }

}

using arGLRenderer = c0de4un::aliensar::gl::GLRenderer;

#define C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_DECL

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_HPP
