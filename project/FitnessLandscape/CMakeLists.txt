add_executable(FitnessLandscape
    EuklidBigramy.cpp
    EuklidTrigramy.cpp
    FitnessFunctionss.cpp
    FitnessLandscape.cpp
    main.cpp
    ManhattanBigramy.cpp
    ManhattanTrigramy.cpp
    PocetTrigramy.cpp
    PracaSoSubormi.cpp
    Statistika.cpp
)

target_link_libraries(FitnessLandscape grid)
install(TARGETS FitnessLandscape DESTINATION ${PROJECT_SOURCE_DIR}/project/FitnessLandscape)
