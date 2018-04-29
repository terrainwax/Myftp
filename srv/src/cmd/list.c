/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void loop(list_t *list)
{
	while ((list->entry = readdir(list->dp))) {
		if (stat(list->entry->d_name, &list->statbuf) == -1) {
			fprintf(stderr, "FTP: Error reading file stats...\n");
		} else {
			list->perms = malloc(9);
			memset(list->perms, 0, 9);
			list->rawtime = list->statbuf.st_mtime;
			list->time = localtime(&list->rawtime);
			strftime(list->timebuff, 80, "%b %d %H:%M", list->time);
			str_perm((list->statbuf.st_mode & ALLPERMS),
				list->perms);
			dprintf(list->connection,
				"%c%s %5d %4d %4d %8d %s %s\r\n",
				(list->entry->d_type == DT_DIR) ? 'd' : '-',
				list->perms, (int)list->statbuf.st_nlink,
				list->statbuf.st_uid, list->statbuf.st_gid,
				(int)list->statbuf.st_size, list->timebuff,
				list->entry->d_name);
		}
	}
}

void execute(state_t *state, list_t *list)
{
	if (!list->dp)
		state->message = "550 Failed to open directory.\n";
	else {
		if (state->mode == SERVER)
			list->connection = accept_connection(state->sock_pasv);
		else if (state->mode == CLIENT)
			list->connection = connect_port(state);
		else {
			state->message = "425 Use PASV or PORT first.\n";
			return;
		}
		state->message = "150 listing.\n";
		puts(state->message);
		loop(list);
		write_state(state);
		state->message = "226 Directory send OK.\n";
		close(list->connection);
		state->mode == SERVER ?
			close(state->sock_pasv): close(state->sock_port);
	}
}

void ftp_list(command_t *cmd, state_t *state)
{
	list_t list;

	if (state->logged_in == 1) {
		memset(list.cwd, 0, BSIZE);
		memset(list.cwd_orig, 0, BSIZE);
		getcwd(list.cwd_orig, BSIZE);
		if (strlen(cmd->arg) > 0 && cmd->arg[0] != '-') {
			chdir(cmd->arg);
		}
		getcwd(list.cwd, BSIZE);
		list.dp = opendir(list.cwd);
		execute(state, &list);
		state->mode = NORMAL;
		closedir(list.dp);
		chdir(list.cwd_orig);
	} else {
		state->message = "530 Please login with USER and PASS.\n";
	}
	state->mode = NORMAL;
	write_state(state);
}