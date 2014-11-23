CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

PROJECT(SCIBEX_server)

# Viewer executable name
SET(SCIBEX_server_EXE SCIBEX-server)

# Target architectures for MacOS X build
SET(CMAKE_OSX_ARCHITECTURES x86_64) #;i386;ppc;ppc64)

# Automatically preprocess Qt classes with MOC
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# We need C++11 (or C++0x)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Force -fPIC flag, needed to use Qt5 on Linux.
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Find Qt5 Modules
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5Svg REQUIRED)

# IBEX Specifics
include_directories(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/soplex-1.7.2/src ${CMAKE_CURRENT_LIST_DIR}/ibex-dev/include )

find_library(IBEX
 NAMES libibex ibex
 PATHS ${CMAKE_CURRENT_LIST_DIR}/ibex-dev/lib
)

find_library(SOPLEX
 NAMES libsoplex soplex
 PATHS ${CMAKE_CURRENT_LIST_DIR}/soplex-1.7.2/lib
)

find_library(CLP
 NAMES libOsiClp Clp libOsiClp.so.1.12.6
 PATHS ${CMAKE_CURRENT_LIST_DIR}/ibex-dev/lib
)

#find_library(COINUTILS
# NAMES libCoinUtils CoinUtils
# PATHS ${CMAKE_CURRENT_LIST_DIR}/ibex-dev/lib
#)

find_library(PRIM
 NAMES libprim prim
 PATHS ${CMAKE_CURRENT_LIST_DIR}/ibex-dev/lib
)

if(IBEX)
 message("IBEX found")
else(IBEX)
 message("IBEX not found")
endif(IBEX)

if(SOPLEX)
 message("SOPLEX found")
else(SOPLEX)
 message("SOPLEX not found")
endif(SOPLEX)

#if(COINUTILS)
# message("COINUTILS found")
#else(COINUTILS)
# message("COINUTILS not found")
#endif(COINUTILS)

if(CLP)
 message("CLP found")
else(CLP)
 message("CLP not found")
endif(CLP)

if(PRIM)
 message("PRIM found")
else(PRIM)
 message("PRIM not found")
endif(PRIM)
# IBEX Specifics


# Source files
SET(SCIBEX_server_SOURCES main.cpp
                         mainwindow.cpp CtcFactory.cpp)

# Qt designer UI files
SET(SCIBEX_server_FORMS mainwindow.ui)
# Process Qt UI files
QT5_WRAP_UI(SCIBEX_server_FORMS_HEADERS ${SCIBEX_server_FORMS})

# Build and add an application icon
include(MacroAddAppIcon.cmake)
ADD_APP_ICON(SCIBEX_server_SOURCES icons/scibex)

# SCIBEX-server executable
ADD_EXECUTABLE(${SCIBEX_server_EXE} WIN32 MACOSX_BUNDLE ${SCIBEX_server_SOURCES} ${SCIBEX_server_FORMS_HEADERS})

TARGET_LINK_LIBRARIES(${SCIBEX_server_EXE} ${IBEX} ${SOPLEX} ${CLP} ${PRIM}) #${COINUTILS}

# Qt5 Modules
QT5_USE_MODULES(${SCIBEX_server_EXE} Widgets Gui Core Network Svg)

# Packaging
IF(APPLE)
    IF(NOT QT_BINARY_DIR)
        SET(QT_BINARY_DIR ${_qt5Core_install_prefix}/bin)
        message(STATUS "QT_BINARY_DIR was not set. Located it at ${QT_BINARY_DIR}")
    ENDIF(NOT QT_BINARY_DIR)

    # Copy dependencies to the app bundle
    INSTALL(CODE "message(STATUS \"Running ${QT_BINARY_DIR}/macdeployqt on ${SCIBEX_server_EXE}.app\")
                  execute_process(COMMAND ${QT_BINARY_DIR}/macdeployqt ${SCIBEX_server_EXE}.app)
                  ")

    # Copy the Application bundle
    INSTALL(TARGETS ${SCIBEX_server_EXE} BUNDLE DESTINATION .)#${CMAKE_CURRENT_BINARY_DIR})

    # Copy API files
    #install(FILES ../client-api/C/vibes.h ../client-api/C/vibes.c DESTINATION "Vibes C")
    #install(DIRECTORY ../client-api/C/examples DESTINATION "Vibes C")

    #install(DIRECTORY ../client-api/C++/src DESTINATION "Vibes C++")
    #install(DIRECTORY ../client-api/C++/examples DESTINATION "Vibes C++")

    # Setup DMG window appearance: background image, size and icon layout
    #SET(CPACK_DMG_BACKGROUND_IMAGE ${CMAKE_CURRENT_SOURCE_DIR}/VIBes_DMG_bg/VIBes_DMG_bg.jpg)
    #SET(CPACK_DMG_DS_STORE ${CMAKE_CURRENT_SOURCE_DIR}/VIBes_DMG_bg/DS_Store)

    #SET(CPACK_PACKAGE_NAME VIBes)

    #SET(CPACK_GENERATOR "DragNDrop")
    #include(CPack)
ENDIF(APPLE)
