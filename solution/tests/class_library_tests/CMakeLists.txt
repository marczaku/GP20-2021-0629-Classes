file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(class_library_tests ${SRCS})

TARGET_LINK_LIBRARIES(
        class_library_tests
    CLASS_LIBRARY
    libgtest
    libgmock
)

add_test(NAME class_library_tests
         COMMAND class_library_tests)