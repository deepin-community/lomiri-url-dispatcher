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

#include <lomiri-app-launch.h>
#include "lomiri-app-launch-mock.h"

#include <string.h>

static gchar * last_appid = NULL;
static gchar * last_version = NULL;

gchar *
lomiri_app_launch_triplet_to_app_id (const gchar * pkg, const gchar * app, const gchar * version)
{
    g_return_val_if_fail(pkg != NULL, NULL);
    g_return_val_if_fail(app != NULL, NULL);

    if (version != NULL && strlen(version) != 0) {
        lomiri_app_launch_mock_clear_last_version();
        last_version = g_strdup(version);
    } else if (last_version == NULL) {
        last_version = g_strdup("current-user-version");
    }

    return g_strdup_printf("%s_%s_%s", pkg, app, last_version);
}

void
lomiri_app_launch_mock_clear_last_version ()
{
    g_free(last_version);
    last_version = NULL;
}

gboolean
lomiri_app_launch_start_application (const gchar * appid, const gchar * const * uris)
{
	lomiri_app_launch_mock_clear_last_app_id();
	last_appid = g_strdup(appid);
	return TRUE;
}

void
lomiri_app_launch_mock_clear_last_app_id ()
{
	g_free(last_appid);
	last_appid = NULL;
	return;
}

gchar *
lomiri_app_launch_mock_get_last_app_id ()
{
	return last_appid;
}

LomiriAppLaunchHelperObserver lomiri_app_launch_mock_observer_helper_stop_func = NULL;
gchar * lomiri_app_launch_mock_observer_helper_stop_type = NULL;
void * lomiri_app_launch_mock_observer_helper_stop_user_data = NULL;

gboolean
lomiri_app_launch_observer_add_helper_stop (LomiriAppLaunchHelperObserver func, const gchar * type, gpointer user_data)
{
	lomiri_app_launch_mock_observer_helper_stop_func = func;
	lomiri_app_launch_mock_observer_helper_stop_type = g_strdup(type);
	lomiri_app_launch_mock_observer_helper_stop_user_data = user_data;

	return TRUE;
}

gboolean
lomiri_app_launch_observer_delete_helper_stop (LomiriAppLaunchHelperObserver func, const gchar * type, gpointer user_data)
{
	gboolean same = lomiri_app_launch_mock_observer_helper_stop_func == func &&
		g_strcmp0(lomiri_app_launch_mock_observer_helper_stop_type, type) == 0 &&
		lomiri_app_launch_mock_observer_helper_stop_user_data == user_data;
	
	lomiri_app_launch_mock_observer_helper_stop_func = NULL;
	g_clear_pointer(&lomiri_app_launch_mock_observer_helper_stop_type, g_free);
	lomiri_app_launch_mock_observer_helper_stop_user_data = NULL;

	return same;
}

gchar * lomiri_app_launch_mock_last_start_session_helper = NULL;
MirPromptSession * lomiri_app_launch_mock_last_start_session_session = NULL;
gchar * lomiri_app_launch_mock_last_start_session_appid = NULL;
gchar ** lomiri_app_launch_mock_last_start_session_uris = NULL;

gchar *
lomiri_app_launch_start_session_helper (const gchar * type, MirPromptSession * session, const gchar * appid, const gchar * const * uris)
{
	g_clear_pointer(&lomiri_app_launch_mock_last_start_session_helper, g_free);
	g_clear_pointer(&lomiri_app_launch_mock_last_start_session_appid, g_free);
	g_clear_pointer(&lomiri_app_launch_mock_last_start_session_uris, g_strfreev);

	lomiri_app_launch_mock_last_start_session_helper = g_strdup(type);
	lomiri_app_launch_mock_last_start_session_session = session;
	lomiri_app_launch_mock_last_start_session_appid = g_strdup(appid);
	lomiri_app_launch_mock_last_start_session_uris = g_strdupv((gchar **)uris);

	return g_strdup("instance");
}

gchar * lomiri_app_launch_mock_last_stop_helper = NULL;
gchar * lomiri_app_launch_mock_last_stop_appid = NULL;
gchar * lomiri_app_launch_mock_last_stop_instance = NULL;

gboolean
lomiri_app_launch_stop_multiple_helper (const gchar * helper_type, const gchar * appid, const gchar * instance) {
	g_clear_pointer(&lomiri_app_launch_mock_last_stop_helper, g_free);
	g_clear_pointer(&lomiri_app_launch_mock_last_stop_appid, g_free);
	g_clear_pointer(&lomiri_app_launch_mock_last_stop_instance, g_free);

	lomiri_app_launch_mock_last_stop_helper = g_strdup(helper_type);
	lomiri_app_launch_mock_last_stop_appid = g_strdup(appid);
	lomiri_app_launch_mock_last_stop_instance = g_strdup(instance);

	return TRUE;
}
