/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:02:43 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/06 12:28:12 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../libft/libft.h" 

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
	char domainname[NI_MAXHOST]; // FQDN - Fully Qualified Domain Name
}	t_data;

extern t_data g_data;


/* MAIN */
void				exit_failure();

/* INIT_DATA */
struct sockaddr_in*	init_sockaddr(void);
int					init_socket(void);
void				get_ipstr(void);
void				get_domainname(void);
void				init_data(char *argv);

/* DISPLAY */
void				display_error(char *error);
void    			print_data(void);
