project(test)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
cmake_policy(SET CMP0012 NEW)
find_package(SFML REQUIRED)
find_package(OpenCV REQUIRED)

SET(SOURCES
test.cpp
)
 
SET(EXECUTABLE_NAME
test
)
 
 
 
add_executable (
${EXECUTABLE_NAME} ${SOURCES}
)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARY} ${OpenCV_LIBS})
