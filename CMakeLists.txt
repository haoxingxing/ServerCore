cmake_minimum_required (VERSION 3.8)

project ("ServerCore")

include_directories(${PROJECT_BINARY_DIR})
find_package(Git)
MESSAGE(STATUS "###################################")

execute_process(COMMAND ${GIT_EXECUTABLE} describe --abbrev=6 --dirty --always --tags WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE  GIT_REPO_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE      )
execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=short WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE  GIT_REPO_DATE OUTPUT_STRIP_TRAILING_WHITESPACE                    )
execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%H WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE  GIT_REPO_HASH_L OUTPUT_STRIP_TRAILING_WHITESPACE                                )
file(WRITE ${PROJECT_BINARY_DIR}/repo_version.h "#define REPO_VERSION \"${GIT_REPO_VERSION}\"\n#define REPO_DATE \"${GIT_REPO_DATE}\"\n#define REPO_HASH \"${GIT_REPO_HASH}\"\n"                     )
String(SUBSTRING ${GIT_REPO_HASH_L} 0 5 GIT_REPO_HASH     )
String(TOLOWER ${GIT_REPO_HASH} GIT_REPO_HASH             )
add_definitions(-DARCH=${ARCH})
IF (WIN32)  
    set(PLAT "win32")
	if (MSVC)
    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
		string(REPLACE "/MDd" "/MTd" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif(MSVC)
ELSEIF (APPLE)  
    set(PLAT "macos")
ELSEIF (UNIX)  
    set(PLAT "linux")
ENDIF () 

set(FILENAME_SUFFIX "${PLAT}")

set(CMAKE_CXX_STANDARD 17)
set(OUTDIR "${PROJECT_SOURCE_DIR}/build")
set(EXECUTABLE_OUTPUT_PATH ${OUTDIR})
set(LIBRARY_OUTPUT_PATH ${OUTDIR})
message( STATUS "project: [ ${PROJECT_NAME} ]")
message( STATUS "out:     [ ${OUTDIR} ]")
message( STATUS "git:     [ ${GIT_REPO_HASH} ]")
MESSAGE( STATUS "platform:[ ${PLAT} ]")
MESSAGE(STATUS "###################################")
add_subdirectory ("ServerCore")
