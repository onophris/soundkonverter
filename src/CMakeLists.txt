project(soundkonverter)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)

find_package(Cdparanoia REQUIRED)
find_package(Kcddb REQUIRED)

set(TAGLIB_MIN_VERSION "1.4.0")
find_package(Taglib REQUIRED)


include_directories(${KDE4_INCLUDES} ${QT_INCLUDES} ${TAGLIB_INCLUDES} ${CDPARANOIA_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

# all the warnings about constructions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# strict ISO C and ISO C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
# implicit conversions
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion")
# implicit conversions from signed to unsigned
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion")


add_subdirectory(plugins)


include(MacroOptionalAddSubdirectory)
macro_optional_add_subdirectory( po )


set(soundkonvertercore_SRCS
   core/backendplugin.cpp
   core/conversionoptions.cpp
   core/codecwidget.cpp
   core/codecplugin.cpp
   core/filterplugin.cpp
   core/replaygainplugin.cpp
   core/ripperplugin.cpp
)
kde4_add_library(soundkonvertercore SHARED ${soundkonvertercore_SRCS})
target_link_libraries(soundkonvertercore ${KDE4_KDEUI_LIBS} ${KDE4_KFILE_LIBS} ${KDE4_KIO_LIBS})
install(TARGETS soundkonvertercore DESTINATION ${LIB_INSTALL_DIR})


set(soundkonverter_SRCS
   configdialog/configdialog.cpp
   configdialog/configpagebase.cpp
   configdialog/configgeneralpage.cpp
   configdialog/configbackendspage.cpp
   configdialog/configadvancedpage.cpp
   configdialog/configcoverartpage.cpp
   metadata/tagengine.cpp
   metadata/MetaReplayGain.cpp
   opener/fileopener.cpp
   opener/diropener.cpp
   opener/cdopener.cpp
   opener/urlopener.cpp
   opener/playlistopener.cpp
   replaygainscanner/replaygainscanner.cpp
   replaygainscanner/replaygainfilelist.cpp
   replaygainscanner/replaygainfilelistitem.cpp
   replaygainscanner/replaygainprocessor.cpp
   global.cpp
   main.cpp
   soundkonverter.cpp
   soundkonverterapp.cpp
   soundkonverterview.cpp
   codecproblems.cpp
   codecoptimizations.cpp
   combobutton.cpp
   config.cpp
   conversionoptionsmanager.cpp
   convert.cpp
   convertitem.cpp
   filelist.cpp
   filelistitem.cpp
   logger.cpp
   logviewer.cpp
   options.cpp
   optionssimple.cpp
   optionsdetailed.cpp
   optionseditor.cpp
   optionslayer.cpp
   pluginloader.cpp
   progressindicator.cpp
   outputdirectory.cpp
   aboutplugins.cpp
)
kde4_add_executable(soundkonverter ${soundkonverter_SRCS})
target_link_libraries(soundkonverter ${KDE4_KDEUI_LIBS} ${KDE4_KFILE_LIBS} ${KDE4_KIO_LIBS} ${KDE4_SOLID_LIBRARY} ${KDE4_PHONON_LIBS} ${TAGLIB_LIBRARIES} kcddb ${CDPARANOIA_LIBRARIES} soundkonvertercore)
install(TARGETS soundkonverter DESTINATION ${BIN_INSTALL_DIR})


install(FILES soundkonverter.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES soundkonverterui.rc DESTINATION ${DATA_INSTALL_DIR}/soundkonverter)

install(FILES soundkonverter_codecplugin.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR})
install(FILES soundkonverter_filterplugin.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR})
install(FILES soundkonverter_replaygainplugin.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR})
install(FILES soundkonverter_ripperplugin.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR})
install(FILES soundkonverter-rip-audiocd.desktop DESTINATION ${DATA_INSTALL_DIR}/solid/actions)

install(FILES soundkonverter.appdata.xml DESTINATION ${SHARE_INSTALL_PREFIX}/appdata)

add_subdirectory(icons)
add_subdirectory(images)


macro_display_feature_log()


# uninstall target
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
