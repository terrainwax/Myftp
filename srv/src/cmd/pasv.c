/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void ftp_pasv(state_t *state)
{
	if (state->logged_in) {
		int ip[4];
		char buff[255];
		char *response = "227 Passive Mode (%d,%d,%d,%d,%d,%d)\n";
		port_t *port = malloc(sizeof(port_t));
		gen_port(port);
		getip(state->connection, ip);
		close(state->sock_pasv);
		state->sock_pasv = create_socket((256 * port->p1) + port->p2);
		printf("port: %d\n", 256 * port->p1 + port->p2);
		sprintf(buff, response, ip[0], ip[1], ip[2], ip[3], port->p1,
			port->p2);
		state->message = buff;
		state->mode = SERVER;
		puts(state->message);
	} else {
		state->message = "530 Please login with USER and PASS.\n";
		printf("%s", state->message);
	}
	write_state(state);
}