# Testing library
# FetchContent_Declare(
# catch2
# GIT_REPOSITORY https://github.com/catchorg/Catch2.git
# GIT_TAG        v2.9.1
# )
# FetchContent_MakeAvailable(catch2)
# Adds Catch2::Catch2

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/Demystify/lib/googletest/googletest ${PROJECT_SOURCE_DIR}/Test/bin/gtest)
# file(GLOB MODEL_SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/src/*.cpp")
file(GLOB MODEL_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/include/")
file(GLOB MODEL_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Model/")
file(GLOB MODEL_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Test/Model/*.cpp")

# file(GLOB PERSISTENCE_SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Persistence/src/*.cpp")
file(GLOB PERSISTENCE_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Persistence/include/")
file(GLOB PERSISTENCE_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Persistence/")
file(GLOB PERSISTENCE_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Test/Persistence/*.cpp")

file(GLOB CONTROLLER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Controller/include/")
file(GLOB CONTROLLER_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Controller/")
file(GLOB CONTROLLER_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Test/Controller/*.cpp")

file(GLOB NAVIGATION_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Navigation/include/")
file(GLOB NAVIGATION_ROOT CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Navigation/")
file(GLOB NAVIGATION_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Test/Navigation/*.cpp")

# file(GLOB SERVER_SOURCE_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Server/src/*.cpp")
file(GLOB SERVER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Server/include/")
file(GLOB SERVER_SOURCE_LIST_TEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/Test/Server/*.cpp")

# file(GLOB ALL_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/lib/**/include")

# Tests need to be added as executables first
add_executable(antighost_model_test ${MODEL_SOURCE_LIST_TEST}) # ${MODEL_SOURCE_LIST} ${MODEL_SOURCE_LIST_TEST})
add_executable(antighost_controller_test ${CONTROLLER_SOURCE_LIST_TEST}) # ${MODEL_SOURCE_LIST} ${MODEL_SOURCE_LIST_TEST})
add_executable(antighost_persistence_test ${PERSISTENCE_SOURCE_LIST_TEST}) # ${PERSISTENCE_SOURCE_LIST} ${PERSISTENCE_SOURCE_LIST_TEST})
add_executable(antighost_server_test ${SERVER_SOURCE_LIST_TEST}) # ${SERVER_SOURCE_LIST} ${SERVER_SOURCE_LIST_TEST})
add_executable(antighost_navigation_test ${NAVIGATION_SOURCE_LIST_TEST}) # ${SERVER_SOURCE_LIST} ${SERVER_SOURCE_LIST_TEST})
add_executable(antighost_test ${PROJECT_SOURCE_DIR}/Test/main.cpp) # ${ALL_SOURCE_LIST} ${MODEL_SOURCE_LIST})

# I'm using C++17 in the test
target_compile_features(antighost_test PRIVATE cxx_std_17)

target_include_directories(antighost_test PRIVATE ${SERVER_HEADER_LIST}, ${MODEL_HEADER_LIST}, ${PERSISTENCE_HEADER_LIST}, ${SERVER_HEADER_LIST})
target_include_directories(antighost_model_test PRIVATE AntiGhost_Model_Lib ${MODEL_HEADER_LIST} ${PERSISTENCE_ROOT} ${MODEL_ROOT})
target_include_directories(antighost_persistence_test PRIVATE ${PERSISTENCE_HEADER_LIST} ${PERSISTENCE_ROOT} ${CONTROLLER_HEADER_LIST})
target_include_directories(antighost_server_test PRIVATE ${SERVER_HEADER_LIST})

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(antighost_model_test PRIVATE AntiGhost_Model_Lib AntiGhost_Persistence_Lib gtest gtest_main)
target_link_libraries(antighost_persistence_test PRIVATE AntiGhost_Model_Lib AntiGhost_Persistence_Lib Persistence_Lib gtest gtest_main)
target_link_libraries(antighost_controller_test PRIVATE AntiGhost_Persistence_Lib AntiGhost_Controller_Lib Controller_Lib cpprest gtest gtest_main)
target_link_libraries(antighost_server_test PRIVATE AntiGhost_Server_Lib gtest gtest_main)
target_link_libraries(antighost_navigation_test PRIVATE AntiGhost_Navigation_Lib gtest gtest_main)
target_link_libraries(antighost_test PRIVATE Controller_Lib AntiGhost_Model_Lib AntiGhost_Persistence_Lib gtest gtest_main)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME antighost_test COMMAND antighost_test) # Command can be a target
add_test(NAME antighost_model_test COMMAND antighost_model_test) # Command can be a target
add_test(NAME antighost_persistence_test COMMAND antighost_persistence_test) # Command can be a target
add_test(NAME antighost_server_test COMMAND server_test) # Command antighost_can be a target
add_test(NAME antighost_controller_test COMMAND controller_test) # Command antighost_can be a target
add_test(NAME antighost_navigation_test COMMAND antighost_navigation_test) # Command antighost_can be a target
