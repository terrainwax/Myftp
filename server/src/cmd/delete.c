/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_dele(command_t *cmd, state_t *state)
{
	if (state->logged_in) {
		if (unlink(cmd->arg) == -1) {
			state->message = "550 File unavailable.\n";
		} else {
			state->message = "250 Requested file action okay.\n";
		}
	} else {
		state->message = "530 Please login with USER and PASS.\n";
	}
	write_state(state);
}
