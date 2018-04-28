/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void fork_client(ftp_t *ftp)
{
	close(ftp->sock);
	strcat(ftp->welcome, "220 Welcome.\n\0");
	write(ftp->connection, ftp->welcome, strlen(ftp->welcome));
	while ((ftp->bytesr = (int)read(ftp->connection, ftp->buffer, BSIZE))) {
		signal(SIGCHLD, my_wait);
		if (ftp->bytesr <= BSIZE) {
			ftp->buffer[BSIZE - 1] = '\0';
			printf("[Myftp/\x1b[34mINFO\x1b[0m]User %s %s %s",
				ftp->state->username, "command:", ftp->buffer);
			parse_command(ftp->buffer, ftp->cmd);
			ftp->state->connection = ftp->connection;
			if (ftp->buffer[0] >= 0)
				response(ftp->cmd, ftp->state);
			memset(ftp->buffer, 0, BSIZE);
			memset(ftp->cmd, 0, 1 * sizeof(ftp->cmd));
		} else
			perror("server:read");
	}
	print_info("Client disconnected.\n");
	exit(0);
}

ftp_t *init_ftp(int port)
{
	ftp_t *ftp = malloc(sizeof(ftp_t));

	if (ftp == NULL)
		exit(EXIT_FAILURE);
	ftp->sock = create_socket(port);
	ftp->len = sizeof(ftp->client_address);
	ftp->cmd = malloc(sizeof(command_t));
	ftp->state = malloc(sizeof(state_t));
	if (ftp->cmd == NULL || ftp->state == NULL)
		exit(EXIT_FAILURE);
	return ftp;
}

void server(int port)
{
	ftp_t *ftp = init_ftp(port);
	while (1) {
		ftp->connection = accept(ftp->sock,
			(struct sockaddr *)&ftp->client_address,
			(socklen_t *)&ftp->len);
		ftp->pid = fork();
		memset(ftp->buffer, 0, BSIZE);
		if (ftp->pid < 0) {
			fprintf(stderr, "Cannot create child process.");
			exit(EXIT_FAILURE);
		}

		if (ftp->pid == 0) {
			fork_client(ftp);
		} else {
			print_info("closing... :(\n");
			close(ftp->connection);
		}
	}
}

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
		exit(EXIT_FAILURE);
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse);
	if (bind(sock, (struct sockaddr *)&server_address,
		sizeof(server_address)) < 0) {
		exit(EXIT_FAILURE);
	}
	listen(sock, 5);
	return sock;
}

int 	main(int ac, char **av)
{
	int port;

	if (ac != 2)
		return EXIT_FAILURE;
	if (is_numeric(av[1]))
		port = atoi(av[1]);
	else
		return EXIT_FAILURE;
	server(port);
	return EXIT_SUCCESS;

}