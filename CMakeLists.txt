cmake_minimum_required(VERSION 3.12)
project(cpp-physics
	VERSION 0.0.0.1
	DESCRIPTION "A C++ library for physics simulations"
	LANGUAGES CXX
)

include(CTest)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(CLANG_TIDY NAME clang-tidy REQUIRED)
set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY};
	--quiet;
	-config-file=${CMAKE_SOURCE_DIR}/.clang-tidy;
	-p ${CMAKE_BUILD_DIR};
)

include_directories(PUBLIC ./src/lib/)

add_subdirectory(./src/lib/)
add_subdirectory(./src/test/)
add_subdirectory(./src/demo/)
