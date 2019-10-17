cmake_minimum_required(VERSION 2.4 FATAL_ERROR)

project(QnDrawer)

set(CMAKE_BUILD_TYPE debug)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{Qn})

find_package(ROOT REQUIRED COMPONENTS RIO Tree)
find_package(Qn REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall")

include(${ROOT_USE_FILE})

include_directories(
		$ENV{HADDIR}/include
		${CMAKE_SOURCE_DIR}
		${ROOT_INCLUDE_DIRS}
		${Base_INCLUDE_DIR}
		${QnCorrections_INCLUDE_DIR}
		${Correction_INCLUDE_DIR}
		${Correlation_INCLUDE_DIR}
)

link_directories(
		${CMAKE_SOURCE_DIR}
		${Base_SOURCE_DIR}
		${QnCorrections_SOURCE_DIR}
		${Correction_SOURCE_DIR}
		${Correlation_SOURCE_DIR}
)


set (HEADERS
		src/Container.h
		src/SubEvent.h
		src/Method.h
		src/Method3Se.h
		src/CorrelationMananger.h)

set (SOURCES
		src/Container.cpp
		src/SubEvent.cpp
		src/Method.cpp
		src/Method3Se.cpp
		src/CorrelationMananger.cpp
		src/flow.cpp)

add_executable(QnDrawer ${HEADERS} ${SOURCES} )
target_link_libraries(QnDrawer Qn::Base ${ROOT_LIBRARIES})
