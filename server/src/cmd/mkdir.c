/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void need_place(char *cwd, char *res)
{
	memset(cwd, 0, BSIZE);
	memset(res, 0, BSIZE);
	getcwd(cwd, BSIZE);
}

void ftp_mkd(command_t *cmd, state_t *state)
{
	char cwd[BSIZE];
	char res[BSIZE];
	if (state->logged_in) {
		need_place(cwd, res);
		if (cmd->arg[0] == '/') {
			if (mkdir(cmd->arg, S_IRWXU) == 0) {
				sprintf(res, "257 %s\n", cmd->arg);
				state->message = res;
			} else
				state->message = "550 Failed to create \n";
		} else {
			if (mkdir(cmd->arg, S_IRWXU) == 0) {
				sprintf(res, "257 %s\n", cmd->arg);
				state->message = res;
			} else
				state->message = "550 Failed to create\n";
		}
	} else
		state->message = "500 Good news!\n";
	write_state(state);
}