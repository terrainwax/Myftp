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
			perror("srv:read");
	}
	print_info("Client disconnected.\n");
	exit(0);
}

ftp_t *init_ftp(int port)
{
	ftp_t *ftp = malloc(sizeof(ftp_t));

	if (ftp == NULL)
		exit(EXIT_FAIL);
	ftp->sock = create_socket(port);
	ftp->len = sizeof(ftp->client_address);
	ftp->cmd = malloc(sizeof(command_t));
	ftp->state = malloc(sizeof(state_t));
	if (ftp->cmd == NULL || ftp->state == NULL)
		exit(EXIT_FAIL);
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
			exit(EXIT_FAIL);
		}

		if (ftp->pid == 0) {
			fork_client(ftp);
		} else {
			print_info("closing... :(\n");
			close(ftp->connection);
		}
	}
}

int 	main(int ac, char **av)
{
	int port;

	if (ac == 2)
		if (strcmp(av[1], "-help\0") == 0)
			help();
	if (ac != 3)
		return EXIT_FAIL;
	if (is_numeric(av[1]))
		port = atoi(av[1]);
	else
		return EXIT_FAIL;
	if (chdir(av[2]) != 0)
		return EXIT_FAIL;
	server(port);
	return EXIT_SUCCESS;

}