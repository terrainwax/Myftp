/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_pass(command_t *cmd, state_t *state)
{
	if (state->username_ok == 1) {
		state->logged_in = 1;
		state->message = "230 Login successful\n";
	} else {
		state->message = "500 Invalid username or password\n";
	}
	write_state(state);
	(void)*cmd;
}
