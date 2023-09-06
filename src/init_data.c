/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:23:14 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/06 13:57:49 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void init_sockaddr(void)
{
	struct addrinfo 	hints;
	struct addrinfo		*result;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_ICMP;
	int status = getaddrinfo(g_data.host, NULL, &hints, &result);
    if (status != 0)
	{
		fprintf(stderr, "ft_ping: %s: %s\n", g_data.host, gai_strerror(status));
		exit_failure(2);
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
	printf("DEBUG: Socket successfully initialised\n");
	return (sockfd);
}

void	get_ipstr(void)
{
    if (g_data.sockaddr->sin_family == AF_INET) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)g_data.sockaddr;
        inet_ntop(AF_INET, &(ipv4->sin_addr), g_data.ipstr, INET_ADDRSTRLEN);
    } else if (g_data.sockaddr->sin_family == AF_INET6) {
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)g_data.sockaddr;
        inet_ntop(AF_INET6, &(ipv6->sin6_addr), g_data.ipstr, INET6_ADDRSTRLEN);
    } else {
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
    g_data.result = NULL;
	g_data.sockfd = init_socket();
	g_data.pid = getpid();
	g_data.host = argv;
	init_sockaddr();
	get_ipstr();
	get_domainname();
}
