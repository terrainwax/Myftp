/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"


void 	ftp_cdup(state_t *state)
{
	if (state->logged_in) {
		if (chdir("../") == 0) {
			state->message = "250 Directory successfully change.\n";
		} else {
			state->message = "550 Failed to change directory.\n";
		}
	} else {
		state->message = "500 Login with USER and PASS.\n";
	}
	write_state(state);
}