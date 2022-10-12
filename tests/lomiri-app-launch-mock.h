/**
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef UPSTART_APP_LAUNCH_MOCK
#define UPSTART_APP_LAUNCH_MOCK 1

#include <glib.h>
#include <lomiri-app-launch.h>

G_BEGIN_DECLS

void lomiri_app_launch_mock_clear_last_version ();

void lomiri_app_launch_mock_clear_last_app_id ();
gchar * lomiri_app_launch_mock_get_last_app_id ();

extern LomiriAppLaunchHelperObserver lomiri_app_launch_mock_observer_helper_stop_func;
extern gchar * lomiri_app_launch_mock_observer_helper_stop_type;
extern void * lomiri_app_launch_mock_observer_helper_stop_user_data;
extern gchar * lomiri_app_launch_mock_last_start_session_helper;
extern MirPromptSession * lomiri_app_launch_mock_last_start_session_session;
extern gchar * lomiri_app_launch_mock_last_start_session_appid;
extern gchar ** lomiri_app_launch_mock_last_start_session_uris;
extern gchar * lomiri_app_launch_mock_last_stop_helper;
extern gchar * lomiri_app_launch_mock_last_stop_appid;
extern gchar * lomiri_app_launch_mock_last_stop_instance;

G_END_DECLS

#endif /* UPSTART_APP_LAUNCH_MOCK */
