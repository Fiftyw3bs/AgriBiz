# Testing library
# FetchContent_Declare(
# catch2
# GIT_REPOSITORY https://github.com/catchorg/Catch2.git
# GIT_TAG        v2.9.1
# )
# FetchContent_MakeAvailable(catch2)
# Adds Catch2::Catch2

file(GLOB MODEL_SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/src/*.cpp")
file(GLOB MODEL_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/include/")
file(GLOB MODEL_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/")
file(GLOB MODEL_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/*.cpp")

# file(GLOB PERSISTENCE_SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Persistence_Mongo/src/*.cpp")
file(GLOB PERSISTENCE_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Persistence_Mongo/include/")
file(GLOB PERSISTENCE_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Persistence_Mongo/")
file(GLOB PERSISTENCE_SOURCE_LIST_TEST CONFIGURE_DEPENDS "/home/ubuntu/Dokumente/Dev/FarmerServer/MarketPlace/Test/Persistence_Mongo/OrderPersistenceTest.cpp")

file(GLOB CONTROLLER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Controller/include/")
file(GLOB CONTROLLER_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Controller/")
file(GLOB CONTROLLER_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Controller/*.cpp")

file(GLOB NAVIGATION_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Navigation/include/")
file(GLOB NAVIGATION_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Navigation/")
file(GLOB NAVIGATION_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Navigation/*.cpp")

# file(GLOB SERVER_SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Server/src/*.cpp")
file(GLOB SERVER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Server/include/")
file(GLOB SERVER_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Server/*.cpp")

# file(GLOB ALL_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/lib/**/include")

# Tests need to be added as executables first
# add_executable(AgriBiz_model_test ${MODEL_SOURCE_LIST_TEST}) # ${MODEL_SOURCE_LIST} ${MODEL_SOURCE_LIST_TEST})
# add_executable(AgriBiz_controller_test ${CONTROLLER_SOURCE_LIST_TEST}) # ${MODEL_SOURCE_LIST} ${MODEL_SOURCE_LIST_TEST})
add_executable(AgriBiz_persistence_test ${PERSISTENCE_SOURCE_LIST_TEST}) # ${PERSISTENCE_SOURCE_LIST} ${PERSISTENCE_SOURCE_LIST_TEST})
# add_executable(AgriBiz_server_test ${SERVER_SOURCE_LIST_TEST}) # ${SERVER_SOURCE_LIST} ${SERVER_SOURCE_LIST_TEST})
# add_executable(AgriBiz_navigation_test ${NAVIGATION_SOURCE_LIST_TEST}) # ${SERVER_SOURCE_LIST} ${SERVER_SOURCE_LIST_TEST})
add_executable(AgriBiz_test ${PROJECT_SOURCE_DIR}/main.cpp) # ${ALL_SOURCE_LIST} ${MODEL_SOURCE_LIST})

# I'm using C++17 in the test
target_compile_features(AgriBiz_test PRIVATE cxx_std_17)

# target_include_directories(AgriBiz_test PRIVATE ${SERVER_HEADER_LIST}, ${MODEL_HEADER_LIST}, ${PERSISTENCE_HEADER_LIST}, ${SERVER_HEADER_LIST})
# target_include_directories(AgriBiz_model_test PRIVATE AgriBiz_Model_Lib ${MODEL_HEADER_LIST} ${PERSISTENCE_ROOT} ${MODEL_ROOT})
# target_include_directories(AgriBiz_server_test PRIVATE ${SERVER_HEADER_LIST})
target_include_directories(AgriBiz_persistence_test PRIVATE ${PERSISTENCE_HEADER_LIST} ${PERSISTENCE_ROOT} ${CONTROLLER_HEADER_LIST})

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(AgriBiz_persistence_test PRIVATE AgriBiz_Model_Lib AgriBiz_Persistence_Lib Persistence_Lib gtest gtest_main)
# target_link_libraries(AgriBiz_model_test PRIVATE AgriBiz_Model_Lib AgriBiz_Persistence_Lib gtest gtest_main)
# target_link_libraries(AgriBiz_controller_test PRIVATE AgriBiz_Persistence_Lib AgriBiz_Controller_Lib Controller_Lib cpprest gtest gtest_main)
# target_link_libraries(AgriBiz_server_test PRIVATE AgriBiz_Server_Lib gtest gtest_main)
# target_link_libraries(AgriBiz_navigation_test PRIVATE AgriBiz_Navigation_Lib gtest gtest_main)
# target_link_libraries(AgriBiz_test PRIVATE Controller_Lib AgriBiz_Model_Lib AgriBiz_Persistence_Lib gtest gtest_main)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME AgriBiz_persistence_test COMMAND AgriBiz_persistence_test) # Command can be a target
# add_test(NAME AgriBiz_test COMMAND AgriBiz_test) # Command can be a target
# add_test(NAME AgriBiz_model_test COMMAND AgriBiz_model_test) # Command can be a target
# add_test(NAME AgriBiz_server_test COMMAND server_test) # Command AgriBiz_can be a target
# add_test(NAME AgriBiz_controller_test COMMAND controller_test) # Command AgriBiz_can be a target
# add_test(NAME AgriBiz_navigation_test COMMAND AgriBiz_navigation_test) # Command AgriBiz_can be a target
