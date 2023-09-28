/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:05:37 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/12 14:41:01 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void    display_ping_header(void)
{
        //int packet_size = sizeof(t_packet);
        int data_size = PING_PACKET_SIZE - (sizeof(struct icmphdr) + sizeof(struct iphdr));
        printf("PING %s (%s): %d data bytes\n", g_data.host, g_data.ipstr, data_size);
}

void	refresh_rtt_stats(double time)
{
	int packet_received = g_data.packet_received > 0 ? g_data.packet_received : 1;
	g_data.rtt_total += time;
	g_data.rtt_sqrt_total += time * time;
	g_data.avg_time = g_data.rtt_total / packet_received;
	double variance = (g_data.rtt_sqrt_total / packet_received) - (g_data.avg_time * g_data.avg_time);
    if (variance >= 0)
        g_data.mdev_time = sqrt(variance);
    else
        g_data.mdev_time = 0.0; 
}

void	refresh_ping_info(char *error, int sequence, int ttl)
{
	double time = get_time_ms(&g_data.send_time, &g_data.rec_time);
	refresh_min_max_time(time);
	refresh_rtt_stats(time);
	if (error != NULL)
		printf("From %s icmp_seq=%d %s\n", g_data.ipstr, sequence, error);
	else
	{
		printf("%d bytes from %s: icmp_seq=%d ttl=%d ",PING_PACKET_SIZE - (int)sizeof(struct iphdr), g_data.ipstr, sequence, ttl);
		if (time < 1.0)
			printf("time=%.3f ms\n", time);
		else
			printf("time=%.2f ms\n", time);
	}
}

int		get_percent_loss(void)
{
	int	percent = ((g_data.sequence - g_data.packet_received) * 100) / g_data.sequence;
	return (percent);
}

void    display_ping_statistics(void)
{
	printf("--- %s ping statistics ---\n", g_data.host);
    printf("%d packets transmitted, %d received, ", g_data.sequence, g_data.packet_received);
	if (g_data.nb_errors)
		printf("+%d errors, ", g_data.nb_errors);
	printf("%d%% packet loss\n", get_percent_loss());
	//printf("time %.0fms\n", get_total_time());
    if (g_data.packet_received > 0) {
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n\n", \
		g_data.min_time,g_data.avg_time,g_data.max_time,g_data.mdev_time);
	}
}

void    print_data(void)
{
	printf("sockfd: %d\n", g_data.sockfd);
	printf("pid:    %d\n", g_data.pid);
	printf("host:   %s\n", g_data.host);
	printf("ip:     %s\n", g_data.ipstr);
	printf("FQDN :  %s\n", g_data.domainname);
}
