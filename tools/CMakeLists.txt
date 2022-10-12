
###########################
# URL Dispatcher
###########################

include_directories(${CMAKE_SOURCE_DIR}/liblomiri-url-dispatcher)

add_executable(lomiri-url-dispatcher url-dispatcher.cpp)

target_link_libraries(lomiri-url-dispatcher
  dispatcher
)

install(
  TARGETS lomiri-url-dispatcher
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
  PROGRAMS lomiri-url-dispatcher-dump
  DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

##########################
# Coverage
###########################
set_property(GLOBAL APPEND PROPERTY COVERAGE_TARGETS lomiri-url-dispatcher)
