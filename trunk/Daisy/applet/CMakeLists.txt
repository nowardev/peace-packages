# Project Needs a name ofcourse
project(daisy)

 
# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
 
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )
 
# We add our source code here
set(daisy_SRCS src/daisy.cpp)
 
add_subdirectory(po)

# Now make sure all files get to the right place
kde4_add_ui_files( daisy_SRCS ui/mainConfiguration.ui ui/arrangementConfiguration.ui ui/hidingConfiguration.ui ui/appearanceConfiguration.ui 
ui/advancedConfiguration.ui ui/launcherConfiguration.ui )

kde4_add_plugin(plasma_applet_daisy ${daisy_SRCS})

target_link_libraries(plasma_applet_daisy 
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KUTILS_LIBS} 
		      ${KDE4_KIO_LIBS} taskmanager )
 
install(TARGETS plasma_applet_daisy
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-daisy.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})


install(FILES images/circular-background.svgz 
images/dock-background-mach.svgz 
images/dock-background-mach-2.svgz 
images/dock-background.svgz 
images/dock-background-shiny-black.svgz 
images/dock-background-vidro.svgz 
images/tasks-indicators.svgz images/dock-animations.svgz 

DESTINATION ${DATA_INSTALL_DIR}/desktoptheme/default/widgets/)









