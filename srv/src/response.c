/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/

#include "ftp.h"


void response5(command_t *cmd, state_t *state)
{
	switch (lookup_cmd(cmd->command)) {
	case PORT:
		ftp_port(cmd, state);
		break;
	case CDUP:
		ftp_cdup(state);
		break;
	default:
		default_state(state);
		break;
	}
}

void response4(command_t *cmd, state_t *state)
{
	switch (lookup_cmd(cmd->command)) {
	case ABOR:
		ftp_abor(state);
		break;
	case QUIT:
		ftp_quit(state);
		break;
	case TYPE:
		ftp_type(cmd, state);
		break;
	case NOOP:
		ftp_noop(state);
		break;
	default:
		response5(cmd, state);
		break;
	}
}

void response3(command_t *cmd, state_t *state)
{
	switch (lookup_cmd(cmd->command)) {
	case RETR:
		ftp_retr(cmd, state);
		break;
	case STOR:
		ftp_stor(cmd, state);
		break;
	case DELE:
		ftp_dele(cmd, state);
		break;
	case SIZE:
		ftp_size(cmd, state);
		break;
	default:
		response4(cmd, state);
		break;
	}

}

void response2(command_t *cmd, state_t *state)
{
	switch (lookup_cmd(cmd->command)) {
	case CWD:
		ftp_cwd(cmd, state);
		break;
	case PWD:
		ftp_pwd(cmd, state);
		break;
	case MKD:
		ftp_mkd(cmd, state);
		break;
	case RMD:
		ftp_rmd(cmd, state);
		break;
	default:
		response3(cmd, state);
		break;
	}
}

void response(command_t *cmd, state_t *state)
{
	switch (lookup_cmd(cmd->command)) {
	case USER:
		ftp_user(cmd, state);
		break;
	case PASS:
		ftp_pass(cmd, state);
		break;
	case PASV:
		ftp_pasv(state);
		break;
	case LIST:
		ftp_list(cmd, state);
		break;
	default:
		response2(cmd, state);
		break;
	}
}
