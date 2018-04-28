/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void exec_retr(state_t *state, int fd, int *connection)
{
	struct stat stat_buf;
	off_t offset = 0;
	int sent_total = 0;

	fstat(fd, &stat_buf);
	state->message = "150 BINARY Mode.\n";
	write_state(state);
	connection[0] = accept_connection(state->sock_pasv);
	close(state->sock_pasv);
	if ((sent_total = (int)send_file(connection[0], fd, &offset,
		(size_t)stat_buf.st_size))) {
		if (sent_total != stat_buf.st_size) {
			perror("sendfile");
			exit(EXIT_SUCCESS);
		}
		state->message = "226 Send.\n";
	} else {
		state->message = "550 Read.\n";
	}
}

void ftp_retr(command_t *cmd, state_t *state)
{
	int connection, fd;
	if (fork() == 0) {
		if (state->logged_in) {
			if (state->mode == SERVER) {
				if (access(cmd->arg, R_OK) == 0 &&
					(fd = open(cmd->arg, O_RDONLY)))
					exec_retr(state, fd, &connection);
				else
					state->message = "550 get file\n";
			} else
				state->message = "550 Please use PASV.\n";
		} else
			state->message = "530 Please login.\n";
		close(fd);
		close(connection);
		write_state(state);
		exit(EXIT_SUCCESS);
	}
	state->mode = NORMAL;
	close(state->sock_pasv);
}