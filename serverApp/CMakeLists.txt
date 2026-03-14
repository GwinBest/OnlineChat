include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

# Require the connector submodule to be present. The project no longer ships
# prebuilt binaries; initialize the submodule if it's missing.
if (EXISTS "${CMAKE_SOURCE_DIR}/thirdParty/mySql/CMakeLists.txt")
    add_subdirectory(${CMAKE_SOURCE_DIR}/thirdParty/mySql thirdParty_mysql_build)
    include_directories(${CMAKE_SOURCE_DIR}/thirdParty/mySql/include)
else()
    message(FATAL_ERROR "MySQL connector submodule not found. Initialize it with:\n  git submodule update --init --recursive")
endif()

add_executable(Server
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/server/server.h
    ${CMAKE_SOURCE_DIR}/src/server/server.cpp
    ${CMAKE_SOURCE_DIR}/src/database/database.h
    ${CMAKE_SOURCE_DIR}/src/database/database.cpp
    ${CMAKE_SOURCE_DIR}/src/networkCore/networkCore.cpp
)

add_compile_definitions(STATIC_CONCPP)

if (TARGET mysqlcppconn-static)
    target_link_libraries(Server PUBLIC mysqlcppconn-static)
elseif (TARGET mysqlcppconn)
    target_link_libraries(Server PUBLIC mysqlcppconn)
else()
    message(FATAL_ERROR "MySQL connector target not available after adding submodule. Ensure the connector subproject provides a target named 'mysqlcppconn' or 'mysqlcppconn-static'.")
endif()

