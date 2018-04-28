/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_abor(state_t *state)
{
	if (state->logged_in){
		state->message = "226 Closing data connection.\n";
		state->message = "225 Data connection open.\n";
	} else {
		state->message = "530 Please login with USER and PASS.\n";
	}
	write_state(state);

}