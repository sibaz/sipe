/**
 * @file sipe.h
 *
 *****************************************************************************
 *** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ***
 ***                                                                       ***
 ***                      THIS INTERFACE IS DEPECRATED                     ***
 ***                                                                       ***
 ***                    DO NOT INCLUDE IT IN ANY NEW CODE                  ***
 ***                                                                       ***
 *** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ***
 *****************************************************************************
 *
 * pidgin-sipe
 *
 * Copyright (C) 2010-11 SIPE Project <http://sipe.sourceforge.net/>
 * Copyright (C) 2008 Novell, Inc.
 * Copyright (C) 2007 Anibal Avelar <avelar@gmail.com>
 * Copyright (C) 2005 Thomas Butter <butter@uni-mannheim.de>
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

/*
 * Interface dependencies:
 *
 * <time.h>
 * <glib.h>
 */

/* Forward declarations */
struct _PurpleAccount;
struct _PurpleConnection;
struct sipe_core_private;
struct sipe_buddy;

/** MS-PRES publication */
struct sipe_publication {
	gchar *category;
	guint instance;
	guint container;
	guint version;
	/** for 'state' category */
	int availability;
	/** for 'state:calendarState' category */
	char *cal_event_hash;
	/** for 'note' category */
	gchar *note;
	/** for 'calendarData' category; 300(Team) container */
	char *working_hours_xml_str;
	char *fb_start_str;
	char *free_busy_base64;
};

struct sipe_account_data {
	struct _PurpleConnection *gc;
	gchar *authdomain;
	gchar *authuser;
	gchar *password;
	/** Allowed server events to subscribe. From register OK response. */
	GSList *allow_events;
	struct sip_csta *csta; /* For RCC - Remote Call Control */
	gboolean subscribed_buddies; /* whether subscribed to buddies presence */
	gboolean access_level_set; /* whether basic access level set */
	gboolean initial_state_published; /* whether we published our initial state */
	GSList *our_publication_keys;		/* [MS-PRES] */
	GHashTable *our_publications;		/* [MS-PRES] */
	GHashTable *user_state_publications;	/* [MS-PRES] */
	int presence_method_version;
	time_t do_not_publish[SIPE_ACTIVITY_NUM_TYPES];
	gchar *status;
	gboolean is_oof_note;
	gchar *note;
	time_t note_since;
	time_t idle_switch;
	gboolean batched_support; /*if there is support for batched subscription*/
	GSList *containers; /* MS-PRES containers */
	struct _PurpleAccount *account;
	gchar *regcallid;
	struct sipe_calendar *cal;
	gchar *email;
	/** 2005 Custom XML piece.
	 * Possibly set by other point of presence or just other client at earlier time.
	 * It should be preserved/modified, not overwritten. This implies subscription
	 * to self-contasct.
	 * This XML keeps OC2005:
	 * - User note
	 * - OOF flag
	 * - User status
	 */
	gchar *user_states;
};

/**
 * THE BIG SPLIT - temporary interfaces
 *
 * Previously private functions in sipe.c that are
 *  - waiting to be factored out to an appropriate module
 *  - are needed by the already created new modules
 */

/* ??? module */
void sipe_connection_cleanup(struct sipe_core_private *sipe_private);
void sipe_buddy_free_all(struct sipe_core_private *sipe_private);
#ifdef _SIPE_NEED_ACTIVITIES
/* need to improve or reduce visibility of this interface */
const gchar *sipe_activity_to_token(sipe_activity);
const gchar *sipe_activity_description(sipe_activity);
const gchar *sipe_activity_description_from_token(const gchar *token);
#endif
void sipe_set_unknown_status(struct sipe_core_private *sipe_private);
void sipe_set_initial_status(struct sipe_core_private *sipe_private);
void sipe_set_invisible_status(struct sipe_core_private *sipe_private);
int sipe_get_availability_by_status(const gchar *sipe_status_id,
				    gchar **activity_token);
const gchar *sipe_get_status_by_availability(int avail,
					     gchar **activity);
void sipe_get_act_avail_by_status_2005(const char *status,
				       int *activity,
				       int *availability);
const gchar *sipe_get_status_by_act_avail_2005(const int activity,
					       const int availablity,
					       char **activity_desc);
void send_presence_status(struct sipe_core_private *sipe_private,
			  gpointer unused);
gboolean sipe_is_user_state(struct sipe_core_private *sipe_private);
gboolean sipe_is_user_available(struct sipe_core_private *sipe_private);
void sipe_update_user_info(struct sipe_core_private *sipe_private,
			   const char *uri,
			   sipe_buddy_info_fields propkey,
			   char *property_value);
void sipe_apply_calendar_status(struct sipe_core_private *sipe_private,
				struct sipe_buddy *sbuddy,
				const char *status_id);

/* this should be in backend? */
void sipe_backend_account_status_and_note(struct sipe_core_private *sipe_private,
					  const gchar *status_id);

/**
 * referenced by sipe-notify.c - start
 */
const gchar *sipe_get_buddy_status(struct sipe_core_private *sipe_private,
				   const gchar *uri);
void sipe_buddy_status_from_activity(struct sipe_core_private *sipe_private,
				     const gchar *uri,
				     const gchar *activity,
				     gboolean is_online);
/* referenced by sipe-notify.c - end */


/*** THE BIG SPLIT END ***/
