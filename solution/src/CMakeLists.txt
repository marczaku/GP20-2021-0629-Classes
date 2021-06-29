

add_subdirectory(class_library)

add_executable (main main.cpp)

target_link_libraries (main CLASS_LIBRARY)

