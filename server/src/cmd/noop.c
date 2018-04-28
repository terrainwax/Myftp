/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_noop(state_t *state)
{
	if (state->logged_in) {
		state->message = "200 Nice to NOOP you!\n";
	} else {
		state->message = "530 NOOB hehe.\n";
	}
	write_state(state);
}