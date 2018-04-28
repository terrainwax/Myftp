/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_rmd(command_t *cmd, state_t *state)
{
	if (!state->logged_in) {
		state->message = "530 Please login first.\n";
	} else {
		if (rmdir(cmd->arg) == 0) {
			state->message = "250 Requested file completed.\n";
		} else {
			state->message = "550 Cannot delete directory.\n";
		}
	}
	write_state(state);
}