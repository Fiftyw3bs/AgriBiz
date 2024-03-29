# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/MarketPlace/*/include")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/MarketPlace/*/src/*.cpp")
set(REALESTATE_PATH "${PROJECT_SOURCE_DIR}/MarketPlace/")

add_subdirectory(Persistence)
add_subdirectory(Model)
add_subdirectory(Controller)
add_subdirectory(Action)
add_subdirectory(Test)

# Make an automatic library - will be static or dynamic based on user setting
add_library(AgriBiz_Market_Lib main.cpp ${SOURCE_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(AgriBiz_Market_Lib PUBLIC ${HEADER_LIST})

# This depends on (header only) boost
target_link_libraries(AgriBiz_Market_Lib PUBLIC AgriBiz_Model_Lib ASU_RealEstate_Persistence_Lib)

# All users of this library will need at least C++11
target_compile_features(AgriBiz_Market_Lib PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${HEADER_LIST})
