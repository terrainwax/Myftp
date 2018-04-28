/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_type(command_t *cmd, state_t *state)
{
	if (state->logged_in) {
		if (cmd->arg[0] == 'I') {
			state->message = "200 Switching to Binary mode.\n";
		} else if (cmd->arg[0] == 'A') {
			state->message = "200 Switching to ASCII mode.\n";
		} else {
			state->message = "504 command not implemented.\n";
		}
	} else {
		state->message = "530 Please login with USER and PASS.\n";
	}
	write_state(state);
}