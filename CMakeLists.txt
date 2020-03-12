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
		QnDrawer/include/correlation_mananger.h
		QnDrawer/include/flow_configuration.h
		QnDrawer/include/flow_builder.h
		QnDrawer/include/flow_helper.h
		QnDrawer/include/comparator.h
		QnDrawer/include/method.h
		QnDrawer/include/observable.h
		QnDrawer/include/systematics.h
		QnDrawer/include/file_manager.h
		QnDrawer/include/painter.h
		)

set(SOURCES
		QnDrawer/correlation_mananger.cc
		QnDrawer/flow_configuration.cc
		QnDrawer/flow_builder.cc
		QnDrawer/comparator.cc
		QnDrawer/method.cc
		QnDrawer/flow_helper.cc
		QnDrawer/systematics.cc
		QnDrawer/observable.cc
		QnDrawer/file_manager.cc
		QnDrawer/painter.cc
		)

set(PCM_FILE_NAME libQnDrawer)
add_library(QnDrawer SHARED ${SOURCES} )
if(ROOT_FOUND)
	ROOT_GENERATE_DICTIONARY( G__QnDrawer ${HEADERS}
			LINKDEF
				QnDrawer/QnDrawerLinkDef.h
			OPTIONS
			-s ${PCM_FILE_NAME}
			-I${CMAKE_SOURCE_DIR}
			-I${Qn_INCLUDE_DIR}
			)
	target_link_libraries(QnDrawer PRIVATE Qn::Base ${ROOT_LIBRARIES})
endif(ROOT_FOUND)


add_executable(Flow src/build_flow.cc G__QnDrawer.cxx)
target_link_libraries(Flow PUBLIC QnDrawer Qn::Base ${ROOT_LIBRARIES})

add_executable(Configure src/configure_flow.cc G__QnDrawer.cxx)
target_link_libraries(Configure PUBLIC QnDrawer Qn::Base ${ROOT_LIBRARIES})

add_executable(CompareFlow src/compare_flow.cc G__QnDrawer.cxx)
target_link_libraries(CompareFlow PUBLIC QnDrawer Qn::Base ${ROOT_LIBRARIES})

#add_executable(CompareResolution src/CompareResolution.cpp G__QnDrawer.cxx)
#target_link_libraries(CompareResolution PUBLIC QnDrawer Qn::Base ${ROOT_LIBRARIES})

add_executable(Systematics src/draw_systematics.cc G__QnDrawer.cxx)
target_link_libraries(Systematics PUBLIC QnDrawer Qn::Base ${ROOT_LIBRARIES})

add_executable(Sectors src/draw_sectors.cc G__QnDrawer.cxx)
target_link_libraries(Sectors PUBLIC QnDrawer Qn::Base ${ROOT_LIBRARIES})