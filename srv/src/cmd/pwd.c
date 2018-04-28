/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_pwd(command_t *cmd, state_t *state)
{
	if (state->logged_in) {
		char cwd[BSIZE];
		char result[BSIZE];
		memset(result, 0, BSIZE);
		if (getcwd(cwd, BSIZE) != NULL) {
			strcat(result, "257 \"");
			strcat(result, cwd);
			strcat(result, "\"\n");
			state->message = result;
		} else {
			state->message = "550 Failed to get pwd.\n";
		}
		write_state(state);
	}
	(void)*cmd;
}