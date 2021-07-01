file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(class_library_tests ${SRCS})
enable_testing()

TARGET_LINK_LIBRARIES(
    class_library_tests
    CLASS_LIBRARY
    gtest_main
)

include(GoogleTest)

gtest_discover_tests(class_library_tests)