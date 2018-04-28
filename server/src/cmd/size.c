/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_size(command_t *cmd, state_t *state)
{
	struct stat statbuf;
	char filesize[128];

	if (state->logged_in) {
		memset(filesize, 0, 128);
		if (stat(cmd->arg, &statbuf) == 0) {
			sprintf(filesize, "213 %li\n", statbuf.st_size);
			state->message = filesize;
		} else {
			state->message = "550 Could not get file size.\n";
		}
	} else {
		state->message = "530 Please login with USER and PASS.\n";
	}

	write_state(state);
}