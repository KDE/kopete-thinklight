link_directories(${KDE4_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${KDE4_INCLUDES} ${KOPETE_INCLUDES} ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

########### kopete thinklight plugin ###############

set(kopete_thinklight_PART_SRCS thinklightplugin.cpp)

kde4_add_kcfg_files(kopete_thinklight_PART_SRCS kopete_thinklight.kcfgc)
kde4_add_plugin(kopete_thinklight ${kopete_thinklight_PART_SRCS})

target_link_libraries(kopete_thinklight ${KOPETE_LIBRARIES} ${KDE4_KDEUI_LIBS})
install(TARGETS kopete_thinklight DESTINATION ${PLUGIN_INSTALL_DIR})

########### thinklight preferences plugin ###############

set(kcm_kopete_thinklight_PART_SRCS thinklightpreferences.cpp)

kde4_add_ui_files(kcm_kopete_thinklight_PART_SRCS thinklightpreferencesui.ui)
kde4_add_kcfg_files(kcm_kopete_thinklight_PART_SRCS kopete_thinklight.kcfgc)
kde4_add_plugin(kcm_kopete_thinklight ${kcm_kopete_thinklight_PART_SRCS})

target_link_libraries(kcm_kopete_thinklight ${KOPETE_LIBRARIES} ${KDE4_KDEUI_LIBS})
install(TARGETS kcm_kopete_thinklight DESTINATION ${PLUGIN_INSTALL_DIR})

############ kopete_thinklight_fixpermissions ############

kde4_add_executable(kopete_thinklight_fixpermissions kopete_thinklight_fixpermissions.cpp)

install(TARGETS kopete_thinklight_fixpermissions PERMISSIONS SETUID OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############

install(FILES kopete_thinklight.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES kopete_thinklight.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES kopete_thinklight_preferences.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kconfiguredialog)
