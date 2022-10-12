
###########################
# Version Information
###########################

set(API_VERSION 0)
set(ABI_VERSION 0)

###########################
# Lib
###########################

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(DISPATCHER_HEADERS
lomiri-url-dispatcher.h
)

set(DISPATCHER_SOURCES
lomiri-url-dispatcher.c
)

add_library(dispatcher SHARED ${DISPATCHER_SOURCES})

set_target_properties(dispatcher PROPERTIES
  VERSION ${API_VERSION}.0.0
  SOVERSION ${ABI_VERSION}
  OUTPUT_NAME "lomiri-url-dispatcher"
)

target_link_libraries(dispatcher
service-generated
${GLIB2_LIBRARIES}
${GOBJECT2_LIBRARIES}
-Wl,--no-undefined
)

###########################
# Coverage
###########################
set_property(GLOBAL APPEND PROPERTY COVERAGE_TARGETS dispatcher)

###########################
# Pkg Config
###########################

set(DISPATCHER_PC "lomiri-url-dispatcher.pc")
set(apiversion "${API_VERSION}")
set(libdir "${CMAKE_INSTALL_FULL_LIBDIR}")
set(includedir "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
set(VERSION "${ABI_VERSION}")

configure_file("lomiri-url-dispatcher.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/${DISPATCHER_PC}" @ONLY)

###########################
# Installation
###########################

install(
  FILES ${DISPATCHER_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/liblomiri-url-dispatcher"
)

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${DISPATCHER_PC}"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

install(
  TARGETS dispatcher
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
