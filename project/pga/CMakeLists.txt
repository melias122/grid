add_executable(pga
    src/main.cpp

    # add additional .cpp files here
)

target_link_libraries(pga grid PGA)
install(TARGETS pga DESTINATION ${PROJECT_SOURCE_DIR}/project/pga)
