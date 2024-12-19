cmake_minimum_required(VERSION 3.28)
project(typist VERSION 0.1 LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH "C:/Packages/Qt/6.6.2/msvc2019_64")

find_package(Qt6 COMPONENTS REQUIRED
        Core
        Gui
        Widgets
)

# Fetch yaml-cpp v0.8.0
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
)

FetchContent_MakeAvailable(yaml-cpp)

# Fetch icu 76.1
FetchContent_Declare(
        icu
        GIT_REPOSITORY https://github.com/unicode-org/icu.git
        GIT_TAG release-76-1
)

FetchContent_MakeAvailable(icu)

add_executable(typist WIN32
        main.cpp
        config.cpp
        config.hpp
        symbol_data.cpp
        symbol_data.hpp
)


target_link_libraries(typist
        Qt::Core
        Qt::Gui
        Qt::Widgets
        yaml-cpp::yaml-cpp
        ICU::uc
        ICU::i18n
)

# Copy configuration, etc. files to the build directory after building the target
add_custom_command(
        TARGET typist POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/config.yml $<TARGET_FILE_DIR:typist>
        #        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/sounds $<TARGET_FILE_DIR:typist>/sounds
)

# Deployment for Windows to include all necessary DLLs and plugins
#if (WIN32)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_custom_command(TARGET typist POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Running windeployqt..."
            COMMAND windeployqt.exe --no-translations --no-compiler-runtime $<TARGET_FILE:typist>
            COMMENT "Deploying Qt runtime dependencies using windeployqt.")
else ()
    add_custom_command(TARGET typist POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Running windeployqt..."
            COMMAND windeployqt.exe --release --no-translations --no-compiler-runtime $<TARGET_FILE:typist>
            COMMENT "Deploying Qt runtime dependencies using windeployqt.")
endif ()
#endif()

# DOES NOT COPY WebEngine - Copy necessary Qt DLL's
#if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#    set(DEBUG_SUFFIX)
#    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(DEBUG_SUFFIX "d")
#    endif ()
#    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
#    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        endif ()
#    endif ()
#    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E make_directory
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/"
#        )
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/"
#        )
#    endif ()
#    foreach (QT_LIB Core Gui Widgets)
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
#        )
#    endforeach (QT_LIB)
#endif ()
