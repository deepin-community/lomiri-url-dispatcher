
install(FILES
	lomiri-url-dispatcher-gui.qml
	lomiri-url-dispatcher-gui.svg
	DESTINATION "${CMAKE_INSTALL_DATADIR}/lomiri-url-dispatcher/gui/")
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/lomiri-url-dispatcher-gui.desktop
	DESTINATION "${CMAKE_INSTALL_DATADIR}/applications/")

configure_file(
	"lomiri-url-dispatcher-gui.desktop.in"
	"lomiri-url-dispatcher-gui.desktop"
	@ONLY)
