execute_process(COMMAND python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
    OUTPUT_VARIABLE PYTHON_PACKAGE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file(
  test_fake_dispatcher.py.in
  test_fake_dispatcher.py
  )

### FIXME: omitting test_fake_dispatcher.py (see below), it contains build time path assumptions
install(FILES fixture_setup.py fake_dispatcher.py
    DESTINATION ${PYTHON_PACKAGE_DIR}/lomiri_url_dispatcher_testability
)

#install(FILES fixture_setup.py fake_dispatcher.py ${CMAKE_CURRENT_BINARY_DIR}/test_fake_dispatcher.py
#    DESTINATION ${PYTHON_PACKAGE_DIR}/lomiri_url_dispatcher_testability
#)

### FIXME: This test requires to use a systemd user session on the Dbus. We don't have that at build time.

#add_test(fake-dispatcher dbus-test-runner --task nosetests3 --parameter ${CMAKE_CURRENT_BINARY_DIR}/test_fake_dispatcher.py)
#set_tests_properties(fake-dispatcher PROPERTIES ENVIRONMENT PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/..)
