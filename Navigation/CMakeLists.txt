# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

add_definitions(-lpthread)
FIND_PACKAGE(Threads)

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB M_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/include")
file(GLOB P_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Navigation/include")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Navigation/src/*.cpp")
set(NAVIGATION_PATH "${PROJECT_SOURCE_DIR}/Navigation/")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(AntiGhost_Navigation_Lib main.cpp ${SOURCE_LIST}) 

# We need this directory, and users of our library will need it too
target_include_directories(AntiGhost_Navigation_Lib PUBLIC ${P_HEADER_LIST} ${NAVIGATION_PATH} ${M_HEADER_LIST})

# This depends on (header only) boost
target_link_libraries(AntiGhost_Navigation_Lib PUBLIC cpprest AntiGhost_Controller_Lib Navigation_Lib Server_Lib)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${P_HEADER_LIST})
