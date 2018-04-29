/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"

void gen_port(port_t *port)
{
	if (port == NULL)
	{
		perror("malloc");
		exit(EXIT_FAIL);
	}
	srand(time(NULL));
	port->p1 = 128 + (rand() % 64);
	port->p2 = rand() % 0xff;

}

void parse_command(char *cmdstring, command_t *cmd)
{
	sscanf(cmdstring, "%s %s", cmd->command, cmd->arg);
}

void my_wait(int signum)
{
	int status;
	wait(&status);
	(void)signum;
}

int is_numeric(const char * s)
{
	if (s == NULL || *s == '\0' || isspace(*s))
		return 0;
	char * p;
	strtod (s, &p);
	return *p == '\0';
}

void help(void)
{
	printf("%s%s%s%s%s", "USAGE:  ./srv port path\n",
		"\tport is the port number on which ",
		"the srv socket listens\n", "\tpath is the path to the home ",
		"directory for the Anonymous user\n");
}