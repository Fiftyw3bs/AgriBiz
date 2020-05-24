# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.
# set(PROJECT "AntiGhostWorker")
# project(${PROJECT})
cmake_minimum_required(VERSION 3.10)
PROJECT("AntiGhostWorker")
SET(GCC_COVERAGE_COMPILE_FLAGS "-DWERROR=0 -Werror=redundant-move")
add_definitions(-lpthread)
FIND_PACKAGE(Threads)

set(EVENT__DISABLE_TESTS ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Demystify)
add_subdirectory(Model)
add_subdirectory(Server)
add_subdirectory(Test)
add_subdirectory(Persistence)
add_subdirectory(Controller)
# add_subdirectory(Factory)
add_subdirectory(Navigation)

# Make an automatic library - will be static or dynamic based on user setting
add_executable(AntiGhostWorker ${PROJECT_SOURCE_DIR}/main.cpp)

# This depends on (header only) boost
target_link_libraries(AntiGhostWorker PUBLIC AntiGhost_Model_Lib AntiGhost_Persistence_Lib AntiGhost_Server_Lib Controller_Lib AntiGhost_Controller_Lib) # AntiGhost_Factory_Lib)

# All users of this library will need at least C++11
target_compile_features(AntiGhostWorker PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
# source_group(TREE "${PROJECT_SOURCE_DIR}" PREFIX "Header Files" FILES ${HEADER_LIST})

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
# if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
#     add_subdirectory(${PROJECT_SOURCE_DIR}/FarmerTest)
# endif()
