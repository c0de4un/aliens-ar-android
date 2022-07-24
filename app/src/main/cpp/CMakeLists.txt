# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# CMAKE
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# CMake Version
cmake_minimum_required(VERSION 3.18.1)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# PROJECT
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

project("Aliens-AR")

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# HEADERS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( ENGINE_PUBLIC_DIR "${CMAKE_SOURCE_DIR}/engine/public/" )
set( GAME_PUBLIC_DIR "${CMAKE_SOURCE_DIR}/game/public/" )
set( HEADERS
    # OpenGL Render
    "${ENGINE_PUBLIC_DIR}render/GLRenderer.hpp" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# SOURCES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( ENGINE_PRIVATE_DIR "${CMAKE_SOURCE_DIR}/engine/private/" )
set( GAME_PRIVATE_DIR "${CMAKE_SOURCE_DIR}/game/private/" )
set( SOURCES
    # Game.Android
    "native-lib.cpp"
    # OpenGL Render
    "${ENGINE_PRIVATE_DIR}render/GLRenderer.cpp" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# BUILD
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# GameActivity package
find_package(game-activity REQUIRED CONFIG)

# Add SHARED Library Object
add_library(aliensar SHARED ${HEADERS} ${SOURCES} )
    # app_glue from GameActivity
    #${game-activity-include}/game-activity/native_app_glue/android_native_app_glue.c
    #${game-activity-include}/game-activity/GameActivity.cpp
    #${game-activity-include}/game-text-input/gametextinput.cpp)

# Find Libraries
find_library(
    log-lib
    log )

# Link Libraries
target_link_libraries(
    aliensar
    # Android API
    android
    # The game activity
    game-activity::game-activity
    # EGL, required for configuring the display context
    EGL
    # GL ES 3, used for the sample renderer
    GLESv3
    # for AImageDecoder, to load images from resources
    jnigraphics
    ${log-lib} )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =