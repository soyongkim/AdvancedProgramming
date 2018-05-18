CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(ReferenceManagement)

SET(
    CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall"
)

# FIND_PACKAGE(OpenCV REQUIRED) # Not used

ADD_EXECUTABLE(ReferenceManagement  main.cpp article.cpp book.cpp inproceedings.cpp Database.cpp UI.cpp)

INCLUDE_DIRECTORIES( Advanced )



# TARGET_LINK_LIBRARIES(ReferenceManagement ) # Not used yet
