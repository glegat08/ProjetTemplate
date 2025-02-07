project(mylib)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    ${SOURCE_DIR}/engineExe.cpp
)

set(HEADERS
    ${HEADER_DIR}/mathLib.h
    ${HEADER_DIR}/engineExe.h
    ${HEADER_DIR}/myArray.h
    ${HEADER_DIR}/myIntrusiveList.h
    ${HEADER_DIR}/myList.h
    ${HEADER_DIR}/myMatrix.h
    ${HEADER_DIR}/myVector.h
    ${HEADER_DIR}/myVectorND.h
    ${HEADER_DIR}/helper.h
)

add_library(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")