# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/*/include")
file(GLOB CPPREST_HEADER CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/**/include/")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/**/src/*.cpp")
set(MODEL_PATH "${PROJECT_SOURCE_DIR}/Model/")
SET(GCC_COVERAGE_LINK_FLAGS    "-lno-pie")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(Farmer_Model_Lib main.cpp ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(Farmer_Model_Lib PUBLIC ${HEADER_LIST} ${MODEL_PATH} ${CPPREST_HEADER})

# This depends on (header only) boost
target_link_libraries(Farmer_Model_Lib PUBLIC Boost::boost)
# target_link_libraries(Farmer_Model_Lib PUBLIC -lboost_system)

# All users of this library will need at least C++11
target_compile_features(Farmer_Model_Lib PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${HEADER_LIST})
