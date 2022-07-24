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
#ifndef C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_HPP
#include "../../public/render/GLRenderer.hpp"
#endif // !C0DE4UN_ALIENS_AR_ENGINE_GL_RENDERER_HPP

// Include app_glue only for IDE
#define ANDROID_GLUE_APP_DECL
#include <game-activity/native_app_glue/android_native_app_glue.h>

// Include OpenGL ES3
#include <GLES3/gl3.h>

// Include STL vector
#include <vector>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GLRenderer
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace c0de4un
{

    namespace aliensar
    {

        namespace gl
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR & DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            GLRenderer::GLRenderer(android_app *pApp)
                :
                app_(pApp),
                display_(EGL_NO_DISPLAY),
                surface_(EGL_NO_SURFACE),
                context_(EGL_NO_CONTEXT),
                width_(0),
                height_(0)
            {
            }

            GLRenderer::~GLRenderer() noexcept
            {
                if (display_ != EGL_NO_DISPLAY)
                {
                    eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

                    if (context_ != EGL_NO_CONTEXT)
                    {
                        eglDestroyContext(display_, context_);
                        context_ = EGL_NO_CONTEXT;
                    }

                    if (surface_ != EGL_NO_SURFACE)
                    {
                        eglDestroySurface(display_, surface_);
                        surface_ = EGL_NO_SURFACE;
                    }

                    eglTerminate(display_);

                    display_ = EGL_NO_DISPLAY;
                }
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            void GLRenderer::Load()
            {
                // Choose your render attributes
                constexpr EGLint attrs[] = {
                        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
                        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                        EGL_BLUE_SIZE, 8,
                        EGL_GREEN_SIZE, 8,
                        EGL_RED_SIZE, 8,
                        EGL_DEPTH_SIZE, 24,
                        EGL_NONE
                };

                // The default display is probably what you want on Android
                auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
                eglInitialize(display, nullptr, nullptr);

                // figure out how many configs there are
                EGLint numConfigs;
                eglChooseConfig(display, attrs, nullptr, 0, &numConfigs);

                // get the list of configurations
                std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
                eglChooseConfig(display, attrs, supportedConfigs.get(), numConfigs, &numConfigs);

                // Find a config we like.
                // Could likely just grab the first if we don't care about anything else in the config.
                // Otherwise hook in your own heuristic
                auto config = *std::find_if(
                        supportedConfigs.get(),
                        supportedConfigs.get() + numConfigs,
                        [&display](const EGLConfig &config) {
                            EGLint red, green, blue, depth;
                            if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                                && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                                && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                                && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                                return red == 8 && green == 8 && blue == 8 && depth == 24;
                            }
                            return false;
                        });

                // create the proper window surface
                EGLint format;
                eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
                EGLSurface surface = eglCreateWindowSurface(display, config, app_->window, nullptr);

                // Create a GLES 3 context
                EGLint contextAttrs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
                EGLContext context = eglCreateContext(display, config, nullptr, contextAttrs);

                // get some window metrics
                eglMakeCurrent(display, surface, surface, context);

                display_ = display;
                surface_ = surface;
                context_ = context;

                // make width and height invalid so it gets updated the first frame in @a updateRenderArea()
                width_ = -1;
                height_ = -1;

                // setup any other gl related global states
                glClearColor(0.2f, 0.5f, 0.5f, 1.0f);

                // enable alpha globally for now, you probably don't want to do this in a game
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            void GLRenderer::updateRenderArea()
            {
                EGLint width;
                eglQuerySurface(display_, surface_, EGL_WIDTH, &width);

                EGLint height;
                eglQuerySurface(display_, surface_, EGL_HEIGHT, &height);

                if (width != width_ || height != height_) {
                    width_ = width;
                    height_ = height;
                    glViewport(0, 0, width, height);
                }
            }

            void GLRenderer::Render()
            {
                // Check to see if the surface has changed size. This is _necessary_ to do every frame when
                // using immersive mode as you'll get no other notification that your renderable area has
                // changed.
                updateRenderArea();

                // clear the color buffer
                glClear(GL_COLOR_BUFFER_BIT);

                // Present the rendered image. This is an implicit glFlush.
                eglSwapBuffers(display_, surface_);
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        }

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
