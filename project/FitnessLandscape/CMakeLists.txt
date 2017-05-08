add_executable(FitnessLandscape
    src/EuklidBigramy.cpp
    src/EuklidTrigramy.cpp
    src/FitnessFunctionss.cpp
    src/FitnessLandscape.cpp
    src/main.cpp
    src/ManhattanBigramy.cpp
    src/ManhattanTrigramy.cpp
    src/PocetTrigramy.cpp
    src/PracaSoSubormi.cpp
    src/Statistika.cpp
)

target_link_libraries(FitnessLandscape grid)
install(TARGETS FitnessLandscape DESTINATION ${PROJECT_SOURCE_DIR}/project/FitnessLandscape)
