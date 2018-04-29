/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

int create_socket(int port)
{
	int sock;
	int reuse = 1;
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Cannot open socket");
		exit(EXIT_FAIL);
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse);
	if (bind(sock, (struct sockaddr *)&server_address,
		sizeof(server_address)) < 0) {
		exit(EXIT_FAIL);
	}
	listen(sock, 5);
	return sock;
}

void create_socket_port(int port, char *ip, state_t *state)
{
	state->server_address.sin_family = AF_INET;
	state->server_address.sin_port = htons(port);
	state->server_address.sin_addr.s_addr = inet_addr(ip);
	if ((state->sock_port = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <
		0) {
		fprintf(stderr, "Cannot open socket");
		exit(EXIT_FAIL);
	}
}

int connect_port(state_t *state)
{
	int connecte;

	if ((connecte = connect(state->sock_port,
		(const struct sockaddr *)&state->server_address,
		sizeof(state->server_address)) == -1)) {
		close(state->sock_port);
		exit(EXIT_FAIL);
	}
	return connecte;
}