
###########################
# URL Overlay Exec Tool
###########################

add_executable(url-overlay-exec-tool exec-tool.c)
set_target_properties(url-overlay-exec-tool PROPERTIES OUTPUT_NAME "exec-tool")
target_link_libraries(url-overlay-exec-tool ${GIO2_LIBRARIES} ${LOMIRI_APP_LAUNCH_LIBRARIES})

install(
  TARGETS url-overlay-exec-tool
  RUNTIME DESTINATION "${CMAKE_INSTALL_FULL_LIBEXECDIR}/lomiri-app-launch/url-overlay"
)

