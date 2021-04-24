idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS ".")

add_subdirectory(helpers)
target_link_libraries(${COMPONENT_LIB} PUBLIC wifi)
