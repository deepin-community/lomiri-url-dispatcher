# -*- Mode: Python; coding: utf-8; indent-tabs-mode: nil; tab-width: 4 -*-
#
# Copyright (C) 2014 Canonical Ltd.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

import dbus
import dbusmock
import subprocess


class FakeDispatcherException(Exception):
    pass


class FakeURLDispatcherService:

    """Fake URL Dispatcher service using a dbusmock interface."""

    def __init__(self):
        super(FakeURLDispatcherService, self).__init__()
        self.dbus_connection = dbusmock.DBusTestCase.get_dbus(system_bus=False)

    def start(self):
        """Start the fake URL Dispatcher service."""
        self.dbus_mock_server = dbusmock.DBusTestCase.spawn_server(
            'com.lomiri.URLDispatcher',
            '/com/lomiri/URLDispatcher',
            'com.lomiri.URLDispatcher',
            system_bus=False,
            stdout=subprocess.PIPE)
        self.mock = self._get_mock_interface()
        self.mock.AddMethod(
            'com.lomiri.URLDispatcher', 'DispatchURL', 'ss', '', '')

    def _get_mock_interface(self):
        return dbus.Interface(
            self.dbus_connection.get_object(
                'com.lomiri.URLDispatcher',
                '/com/lomiri/URLDispatcher'),
            dbusmock.MOCK_IFACE)

    def stop(self):
        """Stop the fake URL Dispatcher service."""
        self.dbus_mock_server.terminate()
        self.dbus_mock_server.wait()

    def get_last_dispatch_url_call_parameter(self):
        """Return the parameter used in the last call to dispatch URL."""
        calls = self.mock.GetCalls()
        if len(calls) == 0:
            raise FakeDispatcherException(
                'URL dispatcher has not been called.')
        last_call = self.mock.GetCalls()[-1]
        return last_call[2][0]
