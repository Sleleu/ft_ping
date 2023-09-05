/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:05:37 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/05 12:16:55 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"
#include "../libft/libft.h" 

void	display_error(char *error)
{
	ft_putstr_fd(RED,2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n"RESET, 2);
}

void display_ip(struct addrinfo *result)
{
        void *addr;
        char ipstr[INET_ADDRSTRLEN];
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
        addr = &(ipv4->sin_addr);
        inet_ntop(result->ai_family, addr, ipstr, sizeof(ipstr));
        printf("%s\n", ipstr);
}