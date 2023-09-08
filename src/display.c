/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:05:37 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/08 22:25:21 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void    display_ping_header(void)
{
        int packet_size = sizeof(t_packet);
        int data_size = PING_PACKET_SIZE - (sizeof(struct icmphdr) + sizeof(struct iphdr));
        printf("PING %s (%s) %d(%d) bytes of data.\n", g_data.host, g_data.ipstr, data_size, packet_size);
}

void	refresh_ping_info(void)
{
	double time = get_time_ms(&g_data.send_time, &g_data.rec_time);

	if (g_data.sequence == 1)
	{
		g_data.max_time = time;
		g_data.min_time = time;
	}
	time < g_data.min_time ? g_data.min_time = time : (void)time;
	time > g_data.max_time ? g_data.max_time = time : (void)time;
	printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d ",PING_PACKET_SIZE, g_data.domainname, g_data.ipstr, g_data.sequence, TTL);
	if (time < 1.0)
		printf("time=%.3f ms\n", time);
	else
		printf("time=%.2f ms\n", time);
}


void    display_ping_statistics(void)
{
	struct timeval end_time;
	double total_time;
	
	get_timeday(&end_time);
	total_time = get_time_ms(&g_data.start_time, &end_time);
    printf("\n--- %s ping statistics ---\n", g_data.host);
    printf("%d packets transmitted, %d received, %d%% packet loss, ", g_data.sequence, g_data.packet_received, 0);
	printf("time %.0fms\n", total_time);
    printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", g_data.min_time,0.0,g_data.max_time,0.0);
}

void    print_data(void)
{
	printf("sockfd: %d\n", g_data.sockfd);
	printf("pid:    %d\n", g_data.pid);
	printf("host:   %s\n", g_data.host);
	printf("ip:     %s\n", g_data.ipstr);
	printf("FQDN :  %s\n", g_data.domainname);
}
