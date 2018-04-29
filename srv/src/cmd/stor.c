/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void exec_stor(stor_t *stor, state_t *state, FILE *fp)
{
	stor->buff_size = 8192;
	stor->fd = fileno(fp);
	stor->connection = accept_connection(state->sock_pasv);
	close(state->sock_pasv);
	if (pipe(stor->pipefd) == -1)
		perror("ftp_stor: pipe");
	state->message = "125 transfer starting.\n";
	write_state(state);
	while ((stor->res = splice(stor->connection, 0, stor->pipefd[1], NULL,
		stor->buff_size, SPLICE_F_MORE | SPLICE_F_MOVE)) > 0) {
		splice(stor->pipefd[0], NULL, stor->fd, 0, stor->buff_size,
			SPLICE_F_MORE | SPLICE_F_MOVE);
	}
	if (stor->res == -1) {
		perror("ftp_stor: splice");
		exit(EXIT_SUCCESS);
	} else
		state->message = "226 File send OK.\n";
	close(stor->connection);
	close(stor->fd);
}

void exec_stor_port(stor_t *stor, state_t *state, FILE *fp)
{
	stor->buff_size = 8192;
	stor->fd = fileno(fp);
	stor->connection = connect_port(state);

	if (pipe(stor->pipefd) == -1)
		perror("ftp_stor: pipe");
	state->message = "125 transfer starting.\n";
	write_state(state);
	while ((stor->res = splice(stor->connection, 0, stor->pipefd[1], NULL,
		stor->buff_size, SPLICE_F_MORE | SPLICE_F_MOVE)) > 0) {
		splice(stor->pipefd[0], NULL, stor->fd, 0, stor->buff_size,
			SPLICE_F_MORE | SPLICE_F_MOVE);
	}
	close(state->sock_pasv);
	if (stor->res == -1) {
		exit(EXIT_SUCCESS);
	} else
		state->message = "226 File send OK.\n";
	close(stor->connection);
	close(stor->fd);
}

void ftp_stor(command_t *cmd, state_t *state)
{
	stor_t stor;
	FILE *fp = fopen(cmd->arg, "w");
	stor.res = 1;
	stor.offset = 0;
	if (fork() == 0) {
		if (fp == NULL) {
			perror("ftp_stor:fopen");
		} else if (state->logged_in) {
			if (!(state->mode == SERVER))
				exec_stor_port(&stor, state, fp);
			else
				exec_stor(&stor, state, fp);
		} else
			state->message = "530 Please login.\n";
		close(stor.connection);
		write_state(state);
		exit(EXIT_SUCCESS);
	}
	state->mode = NORMAL;
	close(state->sock_pasv);
}