/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:02:43 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/05 12:24:43 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define RESET "\e[0m"

typedef struct s_struct
{
	int					socketfd;
	pid_t 				pid;
	struct addrinfo		*result;
	struct addrinfo		*rp;
	struct addrinfo 	hints;
	struct timeval		current_time;
	struct sockaddr_in	sockaddr;

	char ipstr[INET_ADDRSTRLEN];
	char *host;
}	t_struct;

void	display_error(char *error);
void	display_ip(struct addrinfo *result);