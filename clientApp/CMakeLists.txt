cmake_minimum_required(VERSION 3.20)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_SOURCE_DIR}/thirdParty/mySql/include
    ${stb_src_path}
)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/clientApp)

set(SOURCE_FILES
    main.cpp
    ${CMAKE_SOURCE_DIR}/resources/qrc/images.qrc
    ${CMAKE_SOURCE_DIR}/src/gui/chat/chatPage.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/chat/chatPage.h
    ${CMAKE_SOURCE_DIR}/src/gui/chat/chatPage.ui
    ${CMAKE_SOURCE_DIR}/src/gui/chat/model/availableChatsModel.h
    ${CMAKE_SOURCE_DIR}/src/gui/chat/model/availableChatsModel.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/chat/model/messagesModel.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/chat/model/messagesModel.h
    ${CMAKE_SOURCE_DIR}/src/gui/chat/delegate/availableChatsDelegate.h
    ${CMAKE_SOURCE_DIR}/src/gui/chat/delegate/availableChatsDelegate.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/chat/delegate/messagesDelegate.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/chat/delegate/messagesDelegate.h
    ${CMAKE_SOURCE_DIR}/src/gui/chat/widget/sideBarWidget.h
    ${CMAKE_SOURCE_DIR}/src/gui/chat/widget/sideBarWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/chat/widget/sideBarWidget.ui
    ${CMAKE_SOURCE_DIR}/src/gui/chat/scrollArea/chatScrollArea.h
    ${CMAKE_SOURCE_DIR}/src/gui/chat/scrollArea/chatScrollArea.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/signIn/signInPage.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/signIn/signInPage.h
    ${CMAKE_SOURCE_DIR}/src/gui/signIn/signInPage.ui
    ${CMAKE_SOURCE_DIR}/src/gui/mainWindow.h
    ${CMAKE_SOURCE_DIR}/src/gui/mainWindow.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/mainWindow.ui
    ${CMAKE_SOURCE_DIR}/src/gui/colors/colors.h
    ${CMAKE_SOURCE_DIR}/src/gui/login/loginPage.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/login/loginPage.h
    ${CMAKE_SOURCE_DIR}/src/gui/login/loginPage.ui
    ${CMAKE_SOURCE_DIR}/src/client/client.cpp
    ${CMAKE_SOURCE_DIR}/src/userData/userCredentialsFile.h
    ${CMAKE_SOURCE_DIR}/src/userData/userCredentialsFile.cpp
    ${CMAKE_SOURCE_DIR}/src/userData/user.h
    ${CMAKE_SOURCE_DIR}/src/chatSystem/chatInfo.h
    ${CMAKE_SOURCE_DIR}/src/networkCore/networkCore.h
    ${CMAKE_SOURCE_DIR}/src/networkCore/networkCore.cpp
    ${CMAKE_SOURCE_DIR}/src/common/common.h
    ${CMAKE_SOURCE_DIR}/src/userData/userRepository.h
    ${CMAKE_SOURCE_DIR}/src/userData/userRepository.cpp
)

add_executable(OnlineChat WIN32 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
