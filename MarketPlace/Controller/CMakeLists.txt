# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

add_definitions(-lpthread)
FIND_PACKAGE(Threads)

# Optionally glob, but only for CMake 3.12 or later:
set(CONTROLLER_PATH "${PROJECT_SOURCE_DIR}/MarketPlace/Controller")
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CONTROLLER_PATH}/include")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${CONTROLLER_PATH}/src/*.cpp")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(AgriBiz_Controller_Lib main.cpp ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(AgriBiz_Controller_Lib PUBLIC ${HEADER_LIST} ${CONTROLLER_PATH})

# This depends on (header only) boost
target_link_libraries(AgriBiz_Controller_Lib PUBLIC AgriBiz_Model_Lib AgriBiz_Persistence_Lib cpprest)
# target_link_libraries(AgriBiz_Controller_Lib PUBLIC Model_Lib)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${HEADER_LIST})
