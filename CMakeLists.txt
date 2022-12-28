cmake_minimum_required(VERSION 3.24)
project(Ex3)

set(CMAKE_CXX_STANDARD 17)

#set(PROJECT_HEADERS
#        distance_functions.h
#        KNeighborsClassifier.h
#        DataProcessor.h
#        input_validation.h
#        )
#set(PROJECT_SOURCES
#        Server.cpp
#        distance_functions.cpp
#        KNeighborsClassifier.cpp
#        DataProcessor.cpp
#        input_validation.cpp
#        )
add_executable(Ex3 main.cpp includes/input_validation.h Server.cpp distance_functions.cpp includes/distance_functions.h KNeighborsClassifier.cpp includes/KNeighborsClassifier.h DataProcessor.cpp includes/DataProcessor.h input_validation.cpp)
