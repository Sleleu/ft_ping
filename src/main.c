/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:11:14 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/12 13:24:28 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

t_data g_data;

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		display_ping_statistics();
		close(g_data.sockfd);
		freeaddrinfo(g_data.result);
		exit(EXIT_SUCCESS);
	}
	else if (signal == SIGALRM)
		create_packet();
}

void	exit_failure(int code)
{
	close(g_data.sockfd);
	if (g_data.result != NULL)
		freeaddrinfo(g_data.result);
	exit(code);
}

void	display_man(void)
{
	char *man = "Usage: ping [OPTION...] HOST ...\n\
	\rSend ICMP ECHO_REQUEST packets to network hosts.\n\n\
	\r Options valid for all request types:\n\n\
	\r  -v			verbose output\n\n\
	\r Options valid for --echo requests:\n\n\
	\r  -?			give this help list\n\n";
	printf("%s", man);
	exit(EXIT_SUCCESS);
}

char	*parsing(int argc, char **argv)
{
	int		i = 1;
	char	*ip = NULL;
	if (argc == 2 && argv[i][0] != '-')
		return (argv[1]);
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			for (int j = 1; argv[i][j]; j++) {
				if (argv[i][j] == '?')
					display_man();
				if (argv[i][j] != 'v')
					return (fprintf(stderr, "ft_ping: invalid option -- '%c'\n", argv[i][j]),\
					exit(2), NULL);
			}
			g_data.verbose = true;
		}
		else
		{
			if (ip != NULL)
				return (fprintf(stderr, "ft_ping: bad argument\n"),\
				exit(2), NULL);
			ip = argv[i];
		}
		i++;
	}
	return (ip);
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
	g_data.verbose = false;
	char *ip = parsing(argc, argv);
	signal(SIGINT, signal_handler);
	signal(SIGALRM, signal_handler);
	init_data(ip);
	display_ping_header();
	get_timeday(&g_data.start_time);
	create_packet();
	while(1)
		receive_packet();
	return (0);
}