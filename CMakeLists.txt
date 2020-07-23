cmake_minimum_required(VERSION 3.5)
project(abstract_collection)

if( UNIX )
    set(SYSTEM unix)
elseif( WIN32 )
    set(SYSTEM win32)
endif( UNIX )

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${SYSTEM})

set(SOURCES
    main.cpp
    ${INCLUDE_DIR}/termlib.cpp
	${INCLUDE_DIR}/srlz.cpp
)

set(HEADERS
    ${INCLUDE_DIR}/termlib.h
	${INCLUDE_DIR}/srlz.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${INCLUDE_DIR}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)