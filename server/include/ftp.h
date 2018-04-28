/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <dirent.h>

#ifndef BSIZE
	#define BSIZE 1024
#endif

#ifndef BUF_SIZE
	#define BUF_SIZE 8192
#endif


#ifndef PSU_MYFTP_2017_FTP_H
# define PSU_MYFTP_2017_FTP_H

typedef struct 	port_s
{
	int 	p1;
	int 	p2;
} 		port_t;

typedef struct 	state_s {
	int 	mode;
	int 	logged_in;
	int 	username_ok;
	char 	*username;
	char 	*message;
	int 	connection;
	int 	sock_pasv;
	int 	tr_pid;

} 		state_t;

typedef struct 	command_s
{
	char 	command[5];
	char 	arg[BSIZE - 10];
} 		command_t;

typedef struct ftp_s
{
	int 			sock;
	struct sockaddr_in 	client_address;
	unsigned int 		len;
	int 			connection;
	int 			pid;
	int 			bytesr;
	char 			buffer[BSIZE];
	char 			welcome[BSIZE];
	command_t 		*cmd;
	state_t 		*state;
}		ftp_t;

typedef struct send_s
{
	char 	buf[BUF_SIZE];
	size_t 	toRead;
	size_t	numRead;
	size_t	numSent;
	size_t 	totSent;
}		send_t;

typedef struct stor_s
{
	int 	connection;
	int 	fd;
	off_t 	offset;
	int 	pipefd[2];
	int 	res;
	int 	buff_size;
}		stor_t;

typedef struct 		list_s
{
	struct dirent 	*entry;
	struct stat 	statbuf;
	struct tm 	*time;
	char 		timebuff[80];
	char 		current_dir[BSIZE];
	int 		connection;
	time_t 		rawtime;
	char 		*perms;
	DIR 		*dp;
	char 		cwd[BSIZE];
	char 		cwd_orig[BSIZE];
}			list_t;



typedef enum 	connmode_s
{
		NORMAL,
		SERVER,
		CLIENT
}		connmod_t;

typedef enum 	cmdlist_s
{
		ABOR,
		CWD,
		DELE,
		LIST,
		MDTM,
		MKD,
		NLST,
		PASS,
		PASV,
		PORT,
		PWD,
		QUIT,
		RETR,
		RMD,
		RNFR,
		RNTO,
		SITE,
		SIZE,
		STOR,
		TYPE,
		USER,
		NOOP
} 		cmdlist_t;

void 	gen_port(port_t *);
void 	parse_command(char *, command_t *);
int 	create_socket(int port);
void	 write_state(state_t *);
int 	accept_connection(int);
int 	is_numeric (const char * s);
void	print_info(char *str);
int 	lookup_cmd(char *cmd);
int 	lookup(char *needle, const char **haystack, int count);
void 	getip(int sock, int *ip);

void 	response(command_t *, state_t *);
void 	ftp_user(command_t *, state_t *);
void 	ftp_pass(command_t *, state_t *);
void 	ftp_pwd(command_t *, state_t *);
void 	ftp_cwd(command_t *, state_t *);
void 	ftp_mkd(command_t *, state_t *);
void 	ftp_rmd(command_t *, state_t *);
void 	ftp_pasv( state_t *);
void 	ftp_list(command_t *, state_t *);
void 	ftp_retr(command_t *, state_t *);
void 	ftp_stor(command_t *, state_t *);
void 	ftp_dele(command_t *, state_t *);
void 	ftp_size(command_t *, state_t *);
void 	ftp_quit(state_t *);
void 	ftp_type(command_t *, state_t *);
void 	ftp_abor(state_t *);
void 	ftp_noop(state_t *);
void 	default_state(state_t *);
ssize_t send_file(int, int, off_t *, size_t);

void 	str_perm(int, char *);
void 	my_wait(int);

#endif //PSU_MYFTP_2017_FTP_H