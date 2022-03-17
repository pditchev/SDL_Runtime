cmake_minimum_required(VERSION 3.5.1)

project(utils LANGUAGES CXX)

#set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
#set(_INC_DIR ${_BASE_DIR}/utils)

#message(STATUS ${_BASE_DIR})

set(_INC_DIR ${_BASE_DIR}/utils)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
#set(_SRC_DIR ${_BASE_DIR} )

add_library(${PROJECT_NAME} STATIC
										
					${_INC_DIR}/drawing/Point.h
					${_INC_DIR}/drawing/Color.h
					${_INC_DIR}/drawing/Rectangle.h
					${_INC_DIR}/time/Time.h
					${_INC_DIR}/thread/ThreadUtils.h
					${_INC_DIR}/drawing/DrawParams.h

					${_SRC_DIR}/drawing/Point.cpp
					${_SRC_DIR}/drawing/Color.cpp
					${_SRC_DIR}/drawing/Rectangle.cpp
					${_SRC_DIR}/time/Time.cpp
					${_SRC_DIR}/thread/ThreadUtils.cpp
					${_SRC_DIR}/drawing/DrawParams.cpp
			   )

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		${_BASE_DIR}
#		${_INC_DIR}
	)
	
	