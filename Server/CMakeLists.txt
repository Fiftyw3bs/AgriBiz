# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

add_definitions(-lpthread)
FIND_PACKAGE(Threads)

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Server/include")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Server/src/*.cpp")
set(SERVER_PATH "${PROJECT_SOURCE_DIR}/Server")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(AntiGhost_Server_Lib main.cpp ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(AntiGhost_Server_Lib PUBLIC ${HEADER_LIST} ${SERVER_PATH})

# This depends on (header only) boost
target_link_libraries(AntiGhost_Server_Lib PUBLIC Server_Lib AntiGhost_Controller_Lib AntiGhost_Navigation_Lib Persistence_Lib)
# target_link_libraries(AntiGhost_Server_Lib PUBLIC Model_Lib)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${HEADER_LIST})
