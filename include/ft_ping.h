/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:02:43 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/08 21:49:52 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include "../libft/libft.h" 

#define PING_PACKET_SIZE 64
#define TTL 64

typedef	struct s_icmp_code_list
{
    int     code;
    char    *diag;
}	t_icmp_code_list;

typedef struct s_icmp_diag
{
    int     type;
    char    *description;
}	t_icmp_diag;

typedef struct s_packet
{
	struct iphdr	ip_header;
	struct icmphdr	icmp_header;
	char 			data[PING_PACKET_SIZE - (sizeof(struct icmphdr) + sizeof(struct iphdr))];
}	t_packet;

typedef struct s_data
{
	int					sockfd;
	pid_t 				pid;
	struct addrinfo		*result;
	struct addrinfo 	hints;
	struct timeval		current_time;
	struct sockaddr_in	*sockaddr;
	char 				ipstr[INET6_ADDRSTRLEN];
	char 				*host;
	char 				domainname[NI_MAXHOST]; // FQDN - Fully Qualified Domain Name
	int					sequence;
	t_packet			packet;
	struct timeval		start_time;
	struct timeval		send_time;
	struct timeval		rec_time;
	int					signal_code;
	int					packet_received;
}	t_data;

extern t_data g_data;


/* MAIN */
void				exit_failure(int code);

/* INIT_DATA */
void				init_sockaddr(void);
int					init_socket(void);
void				get_ipstr(void);
void				get_domainname(void);
void				init_data(char *argv);

/* DISPLAY */
void				display_ping_header(void);
void				display_ping_statistics(void);
void				refresh_ping_info(void);
void    			print_data(void);

/* PACKET */
void				create_packet(void);
void				receive_packet(void);

/* ANALYSE_PACKET */
char	*get_icmp_code(uint8_t code, t_icmp_code_list *code_list, int size);
void	analyse_packet(void *packet);

/* GET_TIME */
double	get_time_ms(struct timeval *start, struct timeval *end);
void	get_timeday(struct timeval *timeval);