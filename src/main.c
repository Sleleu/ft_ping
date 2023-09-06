/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:11:14 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/06 23:58:39 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

t_data g_data; // global

void	exit_failure(int code)
{
	close(g_data.sockfd);
	if (g_data.result != NULL)
		freeaddrinfo(g_data.result);
	exit(code);
}

int main(int argc, char **argv)
{
	if (getuid() != 0)
	{
		fprintf(stderr, "ft_ping: Operation not permitted\n");
		return (1);
	}
	if (argc < 2)
	{
		fprintf(stderr, "ft_ping: usage error: Destination address required\n");
		return (1);
	}
	init_data(argv[1]);
	//print_data();

	while(1)
	{
		create_packet();
		receive_packet();
		refresh_ping_info();
		usleep(1000000);
	}
    freeaddrinfo(g_data.result);
	return (0);
}