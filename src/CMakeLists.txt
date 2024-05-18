add_executable(${OPENCV_RESEARCH_PROJECT_NAME}
        ${OPENCV_RESEARCH_SRC_DIR}/main.cpp)

find_package(OpenCV REQUIRED)

target_compile_features(${OPENCV_RESEARCH_PROJECT_NAME} PUBLIC
        cxx_std_23)

target_include_directories(${OPENCV_RESEARCH_PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${OPENCV_RESEARCH_INC_DIR}
        ${OpenCV_INCLUDE_DIRS}
        )

target_link_libraries(${OPENCV_RESEARCH_PROJECT_NAME} PUBLIC 
        ${OpenCV_LIBS}
        )

message(STATUS "--------------Compile Info------------")
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "--------------Compile Info------------")