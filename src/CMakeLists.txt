# src/CMakeLists.txt
aux_source_directory(. SRC_FILES)
add_library(MyLibrary ${SRC_FILES})
target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})