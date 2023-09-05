/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:02:43 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/05 12:35:43 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

typedef struct s_data
{
	int					sockfd;
	pid_t 				pid;
	struct addrinfo		*result;
	struct addrinfo 	hints;
	struct timeval		current_time;
	struct sockaddr_in	*sockaddr;
	char ipstr[INET6_ADDRSTRLEN];
	char *host;
	char hostname[NI_MAXHOST];
}	t_data;

extern t_data g_data;

void	display_error(char *error);
void	display_ip(struct addrinfo *result);