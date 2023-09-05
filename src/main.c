/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:11:14 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/05 12:38:13 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"
#include "../libft/libft.h" 

t_data g_data; // global

// void init_addrinfo(void)
// {
// 	struct addrinfo 	hints;
// 	struct addrinfo		*result;

// 	ft_memset(hints, 0, sizeof(*hints));
// 	hints.ai_family = AF_INET;
// 	hints.ai_socktype = SOCK_RAW;
// 	hints.ai_flags = AI_PASSIVE;
// 	hints.ai_protocol = IPPROTO_ICMP;

// 	int status = getaddrinfo(g_data->host, NULL, &hints, &result);
// 	if (status != 0)
// 	{
// 		fprintf(stderr, "ft_ping: %s: %s\n", data.host, gai_strerror(status));
// 		exit (2);
// 	}
// 	g_data->sockaddr = (struct sockaddr_in *)result->ai_addr;
// }

int	init_socket(void)
{
	int sockfd;
	int optval = 1;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd == -1)
	{
		perror("socket");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int)) == -1)
	{
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	printf("DEBUG: Socket successfully initialised\n");
	return (sockfd);
}

void init_data(char *argv)
{
	g_data.sockfd = init_socket();
	g_data.result = NULL;
	g_data.host = argv;
}

// void	get_data(t_struct *data)
// {
// 	// get ipstr
//     void *addr;
//     struct sockaddr_in *ipv4 = (struct sockaddr_in *)data->result->ai_addr;
//     addr = &(ipv4->sin_addr);
//     inet_ntop(data->result->ai_family, addr, data->ipstr, sizeof(data->ipstr));

// 	// get host name
//     inet_pton(AF_INET, data->ipstr, &(ipv4->sin_addr));
//     int status = getnameinfo((struct sockaddr *)data->result->ai_addr, sizeof(struct sockaddr_in), data->hostname, NI_MAXHOST, NULL, 0, 0);
//     if (status != 0) {
//         fprintf(stderr, "ft_ping: getnameinfo: %s\n", gai_strerror(status));
// 		exit(2);
//     }
// }

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
	// init_addrinfo(&data.hints);
	// get_data(&data);
	// printf("PING %s (%s)\n", data.host, data.ipstr);
	// printf("Hostname : %s\n", data.hostname);
	//display_ip(data.result);

	// gettimeofday(&data.current_time, NULL);
	// printf("time : %ld\n", data.current_time.tv_sec);

	// data.pid = getpid();
	// printf("PID : %d\n", data.pid);

	// freeaddrinfo(data.result);
	// printf("Socket : %d\n", data.socketfd);
	return (0);
}