# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
# 设置生成的so动态库最后输出的路径，set后面两个参数，
# 前面一个是命令，后面是路径。
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
add_library( # Sets the name of the library.
        qq_voicer

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).

        src/main/cpp/common.cpp
        src/main/cpp/common_platform.cpp
        src/main/cpp/effect_fix.cpp
        src/main/cpp/effects.cpp
        src/main/cpp/play_sound.cpp
        )

#3.添加头文件
include_directories(scr/main/cpp/inc)

#1.添加三方库（类型时IMPORTED）
add_library(fmod SHARED IMPORTED)
add_library(fmodL SHARED IMPORTED)
#2.添加库的路径
if (${ANDROID_ABI} STREQUAL "armeabi")
    set_target_properties(fmod
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/src/main/jniLibs/armeabi/libfmod.so)
    set_target_properties(fmodL
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/src/main/jniLibs/armeabi/libfmodL.so)
endif (${ANDROID_ABI} STREQUAL "armeabi")

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set_target_properties(fmod
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/src/main/jniLibs/armeabi-v7a/libfmod.so)
    set_target_properties(fmodL
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/src/main/jniLibs/armeabi-v7a/libfmodL.so)
endif (${ANDROID_ABI} STREQUAL "armeabi-v7a")

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#4.添加链接
target_link_libraries( # Specifies the target library.
        qq_voicer
        fmod
        fmodL
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})