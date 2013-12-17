/**
 * @file purple-connection.c
 *
 * pidgin-sipe
 *
 * Copyright (C) 2010-2013 SIPE Project <http://sipe.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "glib.h"

#include "connection.h"

#include "sipe-backend.h"
#include "sipe-core.h"

#include "purple-private.h"

void sipe_backend_connection_completed(struct sipe_core_public *sipe_public)
{
	purple_connection_set_state(sipe_public->backend_private->gc,
#if PURPLE_VERSION_CHECK(3,0,0)
				    PURPLE_CONNECTION_CONNECTED
#else
				    PURPLE_CONNECTED
#endif
		);
}

static const guint map[SIPE_CONNECTION_ERROR_LAST] = {
	PURPLE_CONNECTION_ERROR_NETWORK_ERROR,
	PURPLE_CONNECTION_ERROR_INVALID_USERNAME,
	PURPLE_CONNECTION_ERROR_INVALID_SETTINGS,
	PURPLE_CONNECTION_ERROR_AUTHENTICATION_FAILED,
	PURPLE_CONNECTION_ERROR_AUTHENTICATION_IMPOSSIBLE,
};

void sipe_backend_connection_error(struct sipe_core_public *sipe_public,
				   sipe_connection_error error,
				   const gchar *msg)
{
#if PURPLE_VERSION_CHECK(3,0,0)
	purple_connection_error(
#else
	purple_connection_error_reason(
#endif
				       sipe_public->backend_private->gc,
				       map[error],
				       msg);
}

gboolean sipe_backend_connection_is_disconnecting(struct sipe_core_public *sipe_public)
{
#if PURPLE_VERSION_CHECK(3,0,0)
	return(purple_account_is_disconnecting(sipe_public->backend_private->account));
#else
	return(sipe_public->backend_private->account->disconnecting);
#endif
}

gboolean sipe_backend_connection_is_valid(struct sipe_core_public *sipe_public)
{
	return PURPLE_CONNECTION_IS_CONNECTED(sipe_public->backend_private->gc);
}

/*
  Local Variables:
  mode: c
  c-file-style: "bsd"
  indent-tabs-mode: t
  tab-width: 8
  End:
*/
