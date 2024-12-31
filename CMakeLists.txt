cmake_minimum_required(VERSION 3.19)
project(Casino LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Concurrent)
qt_standard_project_setup()

qt6_add_resources(RESOURCES res.qrc)


qt_add_executable(Casino
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    slots.h slots.cpp slots.ui
    roulette.h roulette.cpp roulette.ui
    about.h about.cpp about.ui
    paymentform.h paymentform.cpp paymentform.ui
    ${RESOURCES}
)
target_link_libraries(Casino
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Concurrent
)
include(GNUInstallDirs)

install(TARGETS Casino
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Casino
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
