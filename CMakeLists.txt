cmake_minimum_required(VERSION 3.8)

project(capstone_js)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory("capstone")

add_executable(${PROJECT_NAME} capstone_js.cc)
target_link_libraries(${PROJECT_NAME} PUBLIC capstone)

# set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

# -Os to reduce size
set_target_properties(capstone_js PROPERTIES LINK_FLAGS "-s WASM_BIGINT -s WASM=1 --no-entry -Os -s STANDALONE_WASM -s EXPORTED_RUNTIME_METHODS=addFunction,removeFunction,writeArrayToMemory -s EXPORTED_FUNCTIONS=_malloc,_free -s ALLOW_MEMORY_GROWTH=1 -s RESERVED_FUNCTION_POINTERS=10")
# for dev
# set_target_properties(capstone_js PROPERTIES LINK_FLAGS " -s EXPORTED_RUNTIME_METHODS=addFunction,removeFunction,writeArrayToMemory -s EXPORTED_FUNCTIONS=_malloc,_free -s ALLOW_MEMORY_GROWTH=1 -s RESERVED_FUNCTION_POINTERS=10")

add_executable(main main.cc)
target_link_libraries(main PUBLIC capstone)
