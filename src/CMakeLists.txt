include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src LDA_SOURCES)

add_executable(main ${LDA_SOURCES})
