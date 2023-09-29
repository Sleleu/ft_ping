/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:23:14 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/12 12:39:28 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void init_sockaddr(void)
{
	struct addrinfo 	hints;
	struct addrinfo		*result;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_ICMP;
	int status = getaddrinfo(g_data.host, NULL, &hints, &result);
    if (status != 0)
	{
		//fprintf(stderr, "ft_ping: %s: %s\n", g_data.host, gai_strerror(status));
		fprintf(stderr, "./ft_ping: unknow host");
		exit_failure(1);
	}
    g_data.result = result;	
    g_data.sockaddr = (struct sockaddr_in *)result->ai_addr;
}

int     init_socket(void)
{
	int sockfd;
	int optval = 1;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd == -1)
		exit_failure(1);
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int)) == -1)
		exit_failure(1);
	return (sockfd);
}

void	get_ipstr(void)
{
    if (g_data.sockaddr->sin_family == AF_INET)
    {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)g_data.sockaddr;
        inet_ntop(AF_INET, &(ipv4->sin_addr), g_data.ipstr, INET_ADDRSTRLEN);
    }
    else
    {
        fprintf(stderr, "ft_ping: Unknown address family\n");
        exit_failure(2);
    }
}

void	get_domainname(void)
{
    int status = getnameinfo((struct sockaddr *)g_data.sockaddr, sizeof(struct sockaddr_storage), g_data.domainname, NI_MAXHOST, NULL, 0, 0);
    if (status != 0) {
        fprintf(stderr, "ft_ping: getnameinfo: %s\n", gai_strerror(status));
        exit_failure(2);
    }
}

void	init_data(char *argv)
{
	g_data.avg_time = 0.0;
	g_data.mdev_time = 0.0;
	g_data.rtt_total = 0.0;
	g_data.rtt_sqrt_total = 0.0;
	g_data.nb_errors = 0;
	g_data.packet_received = 0;
	ft_memset(&g_data.rec_time, 0, sizeof(struct timeval));
	ft_memset(&g_data.send_time, 0, sizeof(struct timeval));
    g_data.signal_code = 0;
    g_data.result = NULL;
    g_data.sequence = 0;
	g_data.sockfd = init_socket();
	g_data.pid = getpid();
	g_data.host = argv;
	init_sockaddr();
	get_ipstr();
	get_domainname();
}
