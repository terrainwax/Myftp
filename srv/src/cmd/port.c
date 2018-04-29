/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void 	ftp_port(command_t *cmd, state_t *state)
{
	int ip[4];
	char buff[255];
	port_t *port = malloc(sizeof(port_t));
	char *response = "220 Port Mode\n";
	if (state->logged_in) {
		sscanf(cmd->arg, "%d,%d,%d,%d,%d,%d", &ip[0], &ip[1], &ip[2],
			&ip[3], &port->p1, &port->p2);
		close(state->sock_pasv);
		sprintf(buff, "%d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);
		create_socket_port(((256 * port->p1) + port->p2), buff, state);
		state->message = response;
		state->mode = CLIENT;
	} else {
		state->message = "530 Please login with USER and PASS.\n";
		printf("%s", state->message);
	}
	write_state(state);
}