cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

project(genbb2root)

find_package(Bayeux REQUIRED)
find_package(Boost REQUIRED)
find_package(ROOT REQUIRED)

include_directories(SYSTEM
	${Bayeux_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${ROOT_INCLUDE_DIRS}
	)

add_executable(genbb2root genbb2root.cxx)

target_link_libraries(genbb2root
	Bayeux::Bayeux
	${Boost_LIBRARIES}
	${INCLUDE_DIR}
)	
