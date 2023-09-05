/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:11:14 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/05 10:28:03 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../libft/libft.h"

void init_addrinfo(struct addrinfo *address)
{
	memset(address, 0, sizeof(*address)); // use libft
	address->ai_family = AF_UNSPEC;
	address->ai_socktype = SOCK_STREAM;
	address->ai_flags = AI_PASSIVE;
	address->ai_protocol = 0;
}

void print_addrinfo(struct addrinfo *address)
{
	printf("ai_flag : %d\nai_family %d\nai_socktype %d\nai_protocol %d\n", address->ai_flags, address->ai_family, address->ai_socktype, address->ai_protocol);
	printf("ai_addrlen : %d\n", address->ai_addrlen);
}

int main(int argc, char **argv)
{
	struct addrinfo address;
	struct addrinfo *ptr_info;
	struct timeval time;
	char *ip;
	
	if (argc < 2)
	{
		printf("ping: usage error: Destination address required\n"); // print on stderr
		return (1);
	}
	init_addrinfo(&address);
	ip = argv[1];
	if (getaddrinfo(ip, NULL, &address, &ptr_info) != 0)
	{
		printf("getaddrinfo() error\n");
		return (1);
	}
	print_addrinfo(&address);
	gettimeofday(&time, NULL);
	printf("time : %ld\n", time.tv_sec);

	pid_t pid;
	pid = getpid();
	printf("PID : %d\n", pid);

	int sockfd = socket(AF_INET, ptr_info->ai_socktype ,ptr_info->ai_protocol);
	if (sockfd == -1)
	{
		printf("Error on socket\n");
		freeaddrinfo(ptr_info);
		close(sockfd);
		return (1);
	}
	freeaddrinfo(ptr_info);
	printf("Socket : %d\n", sockfd);
	ft_putstr_fd("test\n", 1);
	return (0);
}