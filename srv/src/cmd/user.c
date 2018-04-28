/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_user(command_t *cmd, state_t *state)
{
	const char *usernames[] = {"ftp", "Anonymous", "public", "anon", "test",
		"foo", "siim"
	}
	;
	const int total_usernames = sizeof(usernames) / sizeof(char *);
	if (lookup(cmd->arg, usernames, total_usernames) >= 0) {
		state->username = malloc(32);
		memset(state->username, 0, 32);
		strcpy(state->username, cmd->arg);
		state->username_ok = 1;
		state->message = "331 User name okay, need password\n";
	} else {
		state->message = "530 Invalid username\n";
	}
	write_state(state);
}