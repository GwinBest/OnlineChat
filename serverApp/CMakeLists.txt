include_directories(
    ../thirdParty/mySql/include
)

file(COPY 
    ${CMAKE_SOURCE_DIR}/thirdParty/mySql/lib/libssl-1_1-x64.dll
    ${CMAKE_SOURCE_DIR}/thirdParty/mySql/lib/libcrypto-1_1-x64.dll
    DESTINATION ${CMAKE_BINARY_DIR}/serverApp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

add_executable(Server
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/server/server.h
    ${CMAKE_SOURCE_DIR}/src/server/server.cpp
    ${CMAKE_SOURCE_DIR}/src/database/database.h
    ${CMAKE_SOURCE_DIR}/src/database/database.cpp
    ${CMAKE_SOURCE_DIR}/src/networkCore/networkCore.cpp
)

add_compile_definitions(STATIC_CONCPP)

target_link_libraries(Server PUBLIC 
    ${CMAKE_SOURCE_DIR}/thirdParty/mySql/lib/mysqlcppconn-static.lib
)

