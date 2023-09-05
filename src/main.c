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

void init_addrinfo(struct addrinfo *hints)
{
	ft_memset(hints, 0, sizeof(*hints)); // use libft
	hints->ai_family = AF_UNSPEC;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
	hints->ai_protocol = 0;
}

void	init_socket(struct addrinfo *ptr_info)
{
	int sockfd = socket(AF_INET, ptr_info->ai_socktype ,ptr_info->ai_protocol);

	if (sockfd == -1)
	{
		display_error("Error on socket");
		freeaddrinfo(ptr_info);
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

void init_structure(t_struct *data, char *argv)
{
	data->socketfd = 0;
	data->result = NULL;
	data->rp = NULL;
	data->host = argv;
}

void	get_data(t_struct *data)
{
	// get ipstr
    void *addr;
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)data->result->ai_addr;
    addr = &(ipv4->sin_addr);
    inet_ntop(data->result->ai_family, addr, data->ipstr, sizeof(data->ipstr));

	// get host name
    inet_pton(AF_INET, data->ipstr, &(ipv4->sin_addr));
    int status = getnameinfo((struct sockaddr *)data->result->ai_addr, sizeof(struct sockaddr_in), data->hostname, NI_MAXHOST, NULL, 0, 0);
    if (status != 0) {
        fprintf(stderr, "ft_ping: getnameinfo: %s\n", gai_strerror(status));
		exit(2);
    }
}

int main(int argc, char **argv)
{
	t_struct data;

	if (argc < 2)
	{
		fprintf(stderr, "ft_ping: usage error: Destination address required\n");
		return (1);
	}
	init_structure(&data, argv[1]);
	init_addrinfo(&data.hints);
	int status = getaddrinfo(data.host, NULL, &data.hints, &data.result);
	if (status != 0)
	{
		fprintf(stderr, "ft_ping: %s: %s\n", data.host, gai_strerror(status));
		return (2);
	}
	get_data(&data);
	printf("PING %s (%s)\n", data.host, data.ipstr);
	printf("Hostname : %s\n", data.hostname);
	//display_ip(data.result);

	// gettimeofday(&data.current_time, NULL);
	// printf("time : %ld\n", data.current_time.tv_sec);

	// data.pid = getpid();
	// printf("PID : %d\n", data.pid);

	freeaddrinfo(data.result);
	// printf("Socket : %d\n", data.socketfd);
	return (0);
}