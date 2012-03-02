# Install script for directory: /home/shared/Daisy/applet

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/kde4/plasma_applet_daisy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/kde4/plasma_applet_daisy.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/kde4/plasma_applet_daisy.so"
         RPATH "")
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/kde4/plasma_applet_daisy.so")
FILE(INSTALL DESTINATION "/usr/lib/kde4" TYPE MODULE FILES "/home/shared/Daisy/build/lib/plasma_applet_daisy.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/kde4/plasma_applet_daisy.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/kde4/plasma_applet_daisy.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/kde4/plasma_applet_daisy.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kde4/services/plasma-applet-daisy.desktop")
FILE(INSTALL DESTINATION "/usr/share/kde4/services" TYPE FILE FILES "/home/shared/Daisy/applet/plasma-applet-daisy.desktop")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kde4/apps/desktoptheme/default/widgets/circular-background.svgz;/usr/share/kde4/apps/desktoptheme/default/widgets/dock-background-mach.svgz;/usr/share/kde4/apps/desktoptheme/default/widgets/dock-background-mach-2.svgz;/usr/share/kde4/apps/desktoptheme/default/widgets/dock-background.svgz;/usr/share/kde4/apps/desktoptheme/default/widgets/dock-background-shiny-black.svgz;/usr/share/kde4/apps/desktoptheme/default/widgets/dock-background-vidro.svgz;/usr/share/kde4/apps/desktoptheme/default/widgets/tasks-indicators.svgz;/usr/share/kde4/apps/desktoptheme/default/widgets/dock-animations.svgz")
FILE(INSTALL DESTINATION "/usr/share/kde4/apps/desktoptheme/default/widgets" TYPE FILE FILES
    "/home/shared/Daisy/applet/images/circular-background.svgz"
    "/home/shared/Daisy/applet/images/dock-background-mach.svgz"
    "/home/shared/Daisy/applet/images/dock-background-mach-2.svgz"
    "/home/shared/Daisy/applet/images/dock-background.svgz"
    "/home/shared/Daisy/applet/images/dock-background-shiny-black.svgz"
    "/home/shared/Daisy/applet/images/dock-background-vidro.svgz"
    "/home/shared/Daisy/applet/images/tasks-indicators.svgz"
    "/home/shared/Daisy/applet/images/dock-animations.svgz"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/shared/Daisy/build/applet/po/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

