/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:05:37 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/06 22:03:58 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void	display_error(char *error)
{
	ft_putstr_fd(error, 2);
}

void    print_data(void)
{
	printf("sockfd: %d\n", g_data.sockfd);
	printf("pid:    %d\n", g_data.pid);
	printf("host:   %s\n", g_data.host);
	printf("ip:     %s\n", g_data.ipstr);
	printf("FQDN :  %s\n", g_data.domainname);
}
