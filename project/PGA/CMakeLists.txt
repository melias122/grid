# PGA program
add_executable(pga
	src/PGA.cpp
)

target_link_libraries(pga grid PGA)
install(TARGETS pga DESTINATION ${PROJECT_SOURCE_DIR}/project/PGA)

# GA program
add_executable(ga
	src/GA.cpp
	src/main.h
)
install(TARGETS ga DESTINATION ${PROJECT_SOURCE_DIR}/project/PGA)

target_link_libraries(ga grid PGA)

# stat program for GA, PGA
add_executable(stat
	src/stat.cpp
)
install(TARGETS stat DESTINATION ${PROJECT_SOURCE_DIR}/project/PGA)
