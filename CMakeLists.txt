#[[                 ********** Boost Software License - Version 1.0 - August 17th, 2003 **********
Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and accompa
nying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute, and transm
it the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the Software is fu
rnished to do so, all subject to the following:

The copyright notices in the Software and this entire statement, including the above license grant, this restriction and
the following disclaimer, must be included in all copies of the Software, in whole or in part, and all derivative works
of the Software, unless such copies or derivative works are solely in the form of machine-executable object code genera
ted by a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WAR
RANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGH
T HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#                           *************** END Boost Software License BLOCK ***************                          ]]
#
#                          *************** This code is part of REY_FetchV4:- ***************                         ]]
#                   *************** The Original Code is Copyright (C) 2025, REYNEP ***************                   ]]
#        *************** https://github.com/REYNEP/REY_LoggerNUtils/tree/main/REY_FetchV4#readme ***************      ]]


#[[
    USAGE:-
        [TERMINAL] 
            git clone https://github.com/cs50/libcs50
        [CMAKE]
            add_subdirectory("path/to/libcs50")
            target_link_libraries  (YOUR_APP_NAME PUBLIC cs50)

    CMake Introduction:-
        https://www.youtube.com/playlist?list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s
        watch first 6/7 videos, these are pretty short

    CMake is just way too powerfull 😉
]]

    # --Error if not GCC/clang--
    if(NOT (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
        message(STATUS "[REY_FetchV4.libcs50.cmake]")
        message(STATUS "FATAL_ERROR:- ")
        message(STATUS "    libcs50 requires GCC or Clang. Your compiler is: ${CMAKE_CXX_COMPILER_ID}")
        message(STATUS "    However tho:- On windows you can use [Visual Studio Build Tools] 'clang-MSVC-toolchain'")
        message(FATAL_ERROR "(Read Message Above)")
    endif()


    cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
    project("cs50_PROJECT" VERSION 0.1)
        set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)


    #set(cs50_SOURCE_DIR "${REY_FETCH_${TN}_BASE_DIR}/${Git_CloneDir_Name}")
     set(cs50_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

    # --------src---------
        set(SRC
            ${cs50_SOURCE_DIR}/src/cs50.c
        )

        message(STATUS "SRC:- ${cs50_SOURCE_DIR}/src/cs50.c")

        set(INC
            ${cs50_SOURCE_DIR}/src
        )
    # --------------------

    # --------lib---------
    add_library                (cs50 ${SRC})
    target_include_directories (cs50 PUBLIC ${INC})
    set_target_properties      (cs50 PROPERTIES OUTPUT_NAME "libcs50" PREFIX "")
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/.install CACHE PATH "" FORCE)



    # ------warning-------
        if (WIN32 OR MSVC)
            # Enable -Wdeprecated-declarations for GCC and Clang
            if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                message(STATUS "[REY_FetchV4.libcs50.cmake] CLANG / GNU compiler")
                target_compile_options(cs50 PRIVATE -Wdeprecated-declarations)
                target_compile_definitions(cs50 PRIVATE _CRT_SECURE_NO_WARNINGS)
            endif()
        endif()
    # -----suppressed-----



    # ------install-------
        install(TARGETS cs50
            DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/.install)
            # Same Destination is used for installing "fmt::fmt" --> Check: `REY_FetchV4.fmt.cmake`

        # Install header files
        install(FILES 
            ${cs50_SOURCE_DIR}/src/cs50.h
            DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/.install)
    # --------------------