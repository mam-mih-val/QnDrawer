cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(QnDrawer)
set(CMAKE_CXX_FLAGS "-Wall")
set (QnDrawer_VERSION_MAJOR 1)
set (QnDrawer_VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE debug)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)

if (NOT ROOT_FOUND)
	message(WARNING "ROOT was not found with CMAKE_PREFIX_PATH...")
	list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
	find_package(ROOT REQUIRED)
endif ()

if (ROOT_USE_FILE)
	message("-- ROOT_USE_FILE ${ROOT_USE_FILE}")
	include(${ROOT_USE_FILE})
endif()

list(APPEND CMAKE_PREFIX_PATH $ENV{Qn})

find_package(Qn REQUIRED)

include_directories(
		QnDrawer/include
		${CMAKE_SOURCE_DIR}
		${Base_INCLUDE_DIR}
)

set(HEADERS
		QnDrawer/include/Container.h
		QnDrawer/include/SubEvent.h
		QnDrawer/include/Method.h
		QnDrawer/include/Method3Se.h
		QnDrawer/include/CorrelationMananger.h
		QnDrawer/include/FlowConfiguration.h
		QnDrawer/include/MethodRs.h)

set(SOURCES
		QnDrawer/Container.cpp
		QnDrawer/SubEvent.cpp
		QnDrawer/Method.cpp
		QnDrawer/Method3Se.cpp
		QnDrawer/CorrelationMananger.cpp
		QnDrawer/MethodRs.cpp)

add_library(QnDrawer SHARED ${SOURCES} )
if(ROOT_FOUND)
	ROOT_GENERATE_DICTIONARY( G__QnDrawer ${HEADERS} LINKDEF QnDrawer/QnDrawerLinkDef.h )
	target_link_libraries(QnDrawer Qn::Base ${ROOT_LIBRARIES})
endif(ROOT_FOUND)


add_executable(Flow src/flow.cpp)
target_link_libraries(Flow QnDrawer Qn::Base ${ROOT_LIBRARIES})

add_executable(Configure src/ConfigureFlow.cpp)
target_link_libraries(Configure QnDrawer Qn::Base ${ROOT_LIBRARIES})