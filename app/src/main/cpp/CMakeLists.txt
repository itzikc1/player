# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.




add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.


add_library(
        speedlive64_armeabi-v7a-lib
        SHARED
        IMPORTED
)

set_target_properties(
        speedlive64_armeabi-v7a-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libspeedlive64_armeabi-v7a.so
)

                       

                        

add_library(
        avcodec-lib
        SHARED
        IMPORTED
)

set_target_properties(
        avcodec-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libavcodec.so
)

add_library(
        avfilter-lib
        SHARED
        IMPORTED
)

set_target_properties(
        avfilter-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libavfilter.so
)

add_library(
        avformat-lib
        SHARED
        IMPORTED
)

set_target_properties(
        avformat-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libavformat.so
)

add_library(
        avutil-lib
        SHARED
        IMPORTED
)

set_target_properties(
        avutil-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libavutil.so
)
add_library(
        swresample-lib
        SHARED
        IMPORTED
)

set_target_properties(
        swresample-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libswresample.so
)

add_library(
        swscale-lib
        SHARED
        IMPORTED
)

set_target_properties(
        swscale-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libswscale.so
)

add_library(
        c++_shared-lib
        SHARED
        IMPORTED
)
set_target_properties(
        c++_shared-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/armeabi-v7a/libc++_shared.so
)


target_link_libraries( # Specifies the target library.
                       native-lib
                        android
                        speedlive64_armeabi-v7a-lib
                        avcodec-lib
                        avfilter-lib
                        avformat-lib
                        avutil-lib
                        swresample-lib
                        swscale-lib
                        c++_shared-lib
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )

add_definitions(-DLINUX)

