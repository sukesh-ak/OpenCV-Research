add_executable(${CMDARGS_PROJECT_NAME}
        ${CMDARGS_SRC_DIR}/main.cpp)

target_compile_features(${CMDARGS_PROJECT_NAME} PUBLIC
        cxx_std_23)

target_include_directories(${CMDARGS_PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${CMDARGS_INC_DIR}
        )

target_link_libraries(${CMDARGS_PROJECT_NAME} PUBLIC 
        )