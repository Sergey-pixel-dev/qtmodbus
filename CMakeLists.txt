#export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
cmake_minimum_required(VERSION 3.19)
project(qtapp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(qtapp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    qtmodbus.h qtmodbus.cpp
    core.h core.cpp
)



include(GNUInstallDirs)

install(TARGETS qtapp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET qtapp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# Укажите путь к директориям с заголовочными файлами и библиотеками
include_directories("/usr/local/include")

# Добавьте путь к библиотекам
link_directories("/usr/local/lib")
target_link_libraries(qtapp
    PRIVATE
        Qt::Core
        Qt::Widgets
        modbus
)
