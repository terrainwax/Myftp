/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_quit(state_t *state)
{
	state->message = "221 Goodbye.\n";
	write_state(state);
	close(state->connection);
	exit(0);
}