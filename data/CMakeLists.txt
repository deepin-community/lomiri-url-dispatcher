
###########################
# Set stuff
###########################

set(datadir "${CMAKE_INSTALL_FULL_DATADIR}")


###########################
# Dbus Interfaces
###########################

install(
FILES
com.lomiri.URLDispatcher.xml
DESTINATION ${DBUSIFACEDIR}
)

###########################
# QML
###########################

install(
FILES
bad-url.qml
DESTINATION ${datadir}/lomiri-url-dispatcher
)
