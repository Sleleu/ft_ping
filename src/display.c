/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:05:37 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/06 23:56:48 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void	refresh_ping_info(void)
{
	double time = get_time_ms(&g_data.send_time, &g_data.rec_time);
	printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.1f ms\n",PING_PACKET_SIZE, g_data.domainname, g_data.ipstr, g_data.sequence, 64, time);
}

void    print_data(void)
{
	printf("sockfd: %d\n", g_data.sockfd);
	printf("pid:    %d\n", g_data.pid);
	printf("host:   %s\n", g_data.host);
	printf("ip:     %s\n", g_data.ipstr);
	printf("FQDN :  %s\n", g_data.domainname);
}
