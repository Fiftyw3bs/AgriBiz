# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

add_definitions(-lpthread)
FIND_PACKAGE(Threads)

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Controller/include")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Controller/src/*.cpp")
set(CONTROLLER_PATH "${PROJECT_SOURCE_DIR}/Controller")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(AntiGhost_Controller_Lib main.cpp ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(AntiGhost_Controller_Lib PUBLIC ${HEADER_LIST} ${CONTROLLER_PATH})

# This depends on (header only) boost
target_link_libraries(AntiGhost_Controller_Lib PUBLIC AntiGhost_Model_Lib AntiGhost_Persistence_Lib)
# target_link_libraries(AntiGhost_Controller_Lib PUBLIC Model_Lib)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${HEADER_LIST})
