/*
** EPITECH PROJECT, 2021
** PSU_myftp_2017
** File description:
** Created by terrainwax,
*/
#include "ftp.h"

void	print_info(char *str)
{
	fprintf(stdout,"[Myftp/\x1b[34mINFO\x1b[0m] %s",str);
}

void	print_warn(char *str)
{
	fprintf(stdout,"[Myftp/\x1b[33mWARN\\x1b[0m] %s",str);
}

void	print_error(char *str)
{
	fprintf(stdout,"[Myftp/\x1b[31mERROR\x1b[0m] %s",str);
}