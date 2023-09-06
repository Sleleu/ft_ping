/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:11:14 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/06 12:26:17 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

t_data g_data; // global

void	exit_failure()
{
	close(g_data.sockfd);
	exit(EXIT_FAILURE);
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
	print_data();
	// init_addrinfo(&data.hints);
	// get_data(&data);
	// printf("PING %s (%s)\n", data.host, data.ipstr);
	// printf("Hostname : %s\n", data.hostname);
	//display_ip(data.result);

	// gettimeofday(&data.current_time, NULL);
	// printf("time : %ld\n", data.current_time.tv_sec);

	// freeaddrinfo(data.result);
	// printf("Socket : %d\n", data.socketfd);
	return (0);
}