cmake_minimum_required(VERSION 3.20)

project(OnlineChat VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# If the MySQL connector submodule wasn't cloned, instruct the user how to
# initialize it. CMake will continue but serverApp/clientApp will emit a
# helpful error during configuration if the connector isn't available.
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/thirdParty/mySql")
	message(STATUS "MySQL connector submodule not present. Run:\n  git submodule update --init --recursive")
endif()

add_subdirectory(clientApp)
add_subdirectory(serverApp)