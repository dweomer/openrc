/*
 * misc.h
 * This is private to us and not for user consumption
*/

/*
 * Copyright (c) 2007-2015 The OpenRC Authors.
 * See the Authors file at the top-level directory of this distribution and
 * https://github.com/OpenRC/openrc/blob/HEAD/AUTHORS
 *
 * This file is part of OpenRC. It is subject to the license terms in
 * the LICENSE file found in the top-level directory of this
 * distribution and at https://github.com/OpenRC/openrc/blob/HEAD/LICENSE
 * This file may not be copied, modified, propagated, or distributed
 *    except according to the terms contained in the LICENSE file.
 */

#ifndef __RC_MISC_H__
#define __RC_MISC_H__

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "helpers.h"
#include "rc.h"

#define RC_LEVEL_BOOT           "boot"
#define RC_LEVEL_DEFAULT        "default"

#define RC_KRUNLEVEL            RC_SVCDIR "/krunlevel"

char *rc_conf_value(const char *var);
bool rc_conf_yesno(const char *var);
void env_filter(void);
void env_config(void);
int signal_setup(int sig, void (*handler)(int));
int signal_setup_restart(int sig, void (*handler)(int));
int svc_lock(const char *, bool);
int svc_unlock(const char *, int);
pid_t exec_service(const char *, const char *);

typedef struct rc_service_state_name {
	RC_SERVICE state;
	const char *const name;
} rc_service_state_name_t;

/* We MUST list the states below 0x10 first
 * The rest can be in any order */
static const rc_service_state_name_t rc_service_state_names[] = {
	{ RC_SERVICE_STARTED,     "started" },
	{ RC_SERVICE_STOPPED,     "stopped" },
	{ RC_SERVICE_STARTING,    "starting" },
	{ RC_SERVICE_STOPPING,    "stopping" },
	{ RC_SERVICE_INACTIVE,    "inactive" },
	{ RC_SERVICE_WASINACTIVE, "wasinactive" },
	{ RC_SERVICE_HOTPLUGGED,  "hotplugged" },
	{ RC_SERVICE_FAILED,      "failed" },
	{ RC_SERVICE_SCHEDULED,   "scheduled"},
	{ RC_SERVICE_CRASHED,     "crashed"},
	{ 0, NULL}
};

/*
 * Check whether path is writable or not,
 * this also works properly with read-only filesystems
 */
int is_writable(const char *);

#define service_start(service) exec_service(service, "start");
#define service_stop(service)  exec_service(service, "stop");

int parse_mode(mode_t *, char *);

/* Handy function so we can wrap einfo around our deptree */
RC_DEPTREE *_rc_deptree_load (int, int *);

RC_SERVICE lookup_service_state(const char *service);
void from_time_t(char *time_string, time_t tv);
time_t to_time_t(char *timestring);
pid_t get_pid(const char *applet, const char *pidfile);

void cloexec_fds_from(int);

struct notify {
	enum {
		NOTIFY_NONE = 0,
		NOTIFY_FD,
		NOTIFY_SOCKET
	} type;

	char *path;
	int pipe[2];
	int fd;
};

struct notify notify_parse(const char *applet, const char *ready_string);
bool notify_wait(const char *applet, struct notify ready);

#endif
