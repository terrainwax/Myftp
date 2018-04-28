/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

int send_f(int out_fd, int in_fd, size_t *count, send_t *send)
{
	send->toRead = count[0] < BUF_SIZE ? count[0] : BUF_SIZE;
	send->numRead = (size_t)read(in_fd, send->buf, send->toRead);
	if (send->numRead == 0)
		return 0;
	send->numSent = (size_t)write(out_fd, send->buf, send->numRead);
	if (send->numSent == 0) {
		perror("sendfile: write() transferred 0 bytes");
		exit(-1);
	}
	count[0] -= send->numSent;
	send->totSent += send->numSent;
	return 0;
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
		if (send_f(out_fd, in_fd, &count, &send) == -1)
			return -1;
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