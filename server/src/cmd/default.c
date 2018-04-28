/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void default_state(state_t *state)
{
	state->message = "500 Unknown command\n";
	write_state(state);
}