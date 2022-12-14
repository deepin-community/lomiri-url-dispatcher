
include(UseConstantBuilder)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions( -DOVERLAY_SYSTEM_DIRECTORY="${CMAKE_INSTALL_FULL_DATADIR}/lomiri-url-dispatcher/url-overlays" )

###########################
# Generated Lib
###########################

add_gdbus_codegen(
  SERVICE_GENERATED
  service-iface
  com.lomiri.URLDispatcher.
  ${CMAKE_SOURCE_DIR}/data/com.lomiri.URLDispatcher.xml
  NAMESPACE ServiceIface
)

add_library(service-generated STATIC ${SERVICE_GENERATED_SOURCES})

target_link_libraries(service-generated
  ${GLIB2_LIBRARIES}
  ${GOBJECT2_LIBRARIES}
  ${GIO2_LIBRARIES}
)

###########################
# Dispatcher Lib
###########################

add_library(dispatcher-lib STATIC
	dispatcher.h
	dispatcher.c
	glib-thread.h
	glib-thread.cpp
	overlay-tracker.h
	overlay-tracker.cpp
	overlay-tracker-iface.h
	overlay-tracker-mir.h
	overlay-tracker-mir.cpp
)

target_link_libraries(dispatcher-lib
	url-db-lib
	service-generated
	-pthread
	${APPARMOR_LIBRARIES}
	${GLIB2_LIBRARIES}
	${GOBJECT2_LIBRARIES}
	${GIO2_LIBRARIES}
	${SQLITE_LIBRARIES}
	${LOMIRI_APP_LAUNCH_LIBRARIES}
)

###########################
# URL DB Lib
###########################

set(URL_DB_SOURCES
	url-db.c
	url-db.h
	create-db-sql.h
)

add_constant_template(URL_DB_SOURCES
	create-db-sql
	create_db_sql
	"${CMAKE_CURRENT_SOURCE_DIR}/create-db.sql"
)

add_library(url-db-lib STATIC
	${URL_DB_SOURCES}
)

target_link_libraries(url-db-lib
	${GLIB2_LIBRARIES}
	${SQLITE_LIBRARIES}
)

###########################
# Service Executable
###########################

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(service-exec service.cpp)

set_target_properties(service-exec PROPERTIES OUTPUT_NAME "lomiri-url-dispatcher")

target_link_libraries(service-exec dispatcher-lib)

###########################
# Update Directory
###########################

add_executable(update-directory update-directory.c)
set_target_properties(update-directory PROPERTIES OUTPUT_NAME "lomiri-update-directory")
target_link_libraries(update-directory ${GIO2_LIBRARIES} ${JSONGLIB_LIBRARIES} url-db-lib)

###########################
# Coverage
###########################
set_property(
  GLOBAL
  APPEND
  PROPERTY
  COVERAGE_TARGETS dispatcher-lib url-db-lib service-exec update-directory)

###########################
# Installation
###########################

install(
  TARGETS service-exec update-directory
  RUNTIME DESTINATION "${CMAKE_INSTALL_FULL_LIBEXECDIR}/lomiri-url-dispatcher"
)

###########################
# Exec Tools
###########################

add_subdirectory(url-overlay)
add_subdirectory(bad-url)
