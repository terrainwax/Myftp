/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

int accept_connection(int socket)
{
	int addrlen = 0;
	struct sockaddr_in client_address;
	addrlen = sizeof(client_address);
	return accept(socket,(struct sockaddr*) &client_address,
		(socklen_t *)&addrlen);
}

void getip(int sock, int *ip)
{
	socklen_t addr_size = sizeof(struct sockaddr_in);
	struct sockaddr_in addr;
	getsockname(sock, (struct sockaddr *)&addr, &addr_size);

	char* host = inet_ntoa(addr.sin_addr);
	sscanf(host,"%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3]);
}



int lookup(char *needle, const char **haystack, int count)
{
	int i;
	for (i = 0; i < count; i++){
		if (strcmp(needle, haystack[i]) == 0)
			return i;
	}
	return -1;
}

int lookup_cmd(char *cmd)
{
	const char *cmdlist_str[] =
		{
		"ABOR", "CWD", "DELE", "LIST", "MDTM",
		"MKD", "NLST", "PASS", "PASV", "PORT", "PWD", "QUIT", "RETR",
		"RMD", "RNFR", "RNTO", "SITE", "SIZE", "STOR", "TYPE", "USER",
		"NOOP", "CDUP"
		}
		;
	const int cmdlist_count = sizeof(cmdlist_str) / sizeof(char *);
	return lookup(cmd, cmdlist_str, cmdlist_count);
}

void write_state(state_t *state)
{
	write(state->connection, state->message, strlen(state->message));
}