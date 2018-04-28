/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void send_f(int out_fd, int in_fd, size_t *count, send_t *send)
{
	send->toRead = count[0] < BUF_SIZE ? count[0] : BUF_SIZE;
	send->numRead = (size_t)read(in_fd, send->buf, send->toRead);
	send->numSent = (size_t)write(out_fd, send->buf, send->numRead);
	count[0] -= send->numSent;
	send->totSent += send->numSent;
}

ssize_t send_file(int out_fd, int in_fd, off_t *offset, size_t count)
{
	off_t orig;
	send_t send;
	if (offset != NULL) {
		orig = lseek(in_fd, 0, SEEK_CUR);
		if (orig == -1 || lseek(in_fd, *offset, SEEK_SET) == -1)
			return -1;
	}
	send.totSent = 0;
	while (count > 0) {
		send_f(out_fd, in_fd, &count, &send);
	}
	if (offset != NULL) {
		*offset = lseek(in_fd, 0, SEEK_CUR);
		if (*offset == -1 || lseek(in_fd, orig, SEEK_SET) == -1)
			return -1;
	}
	return send.totSent;
}

void str_perm(int perm, char *str_perm)
{
	int curperm = 0;
	int read, write, exec;
	char fbuff[4];
	int i;

	for (i = 6; i >= 0; i -= 3) {
		curperm = ((perm & ALLPERMS) >> i) & 0x7;
		memset(fbuff, 0, 3);
		read = (curperm >> 2) & 0x1;
		write = (curperm >> 1) & 0x1;
		exec = (curperm >> 0) & 0x1;
		sprintf(fbuff, "%c%c%c",
			read ? 'r' : '-',
			write ? 'w' : '-',
			exec ? 'x' : '-');
		strcat(str_perm, fbuff);
	}
}