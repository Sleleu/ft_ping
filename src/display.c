/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:05:37 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/09 00:38:59 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void    display_ping_header(void)
{
        int packet_size = sizeof(t_packet);
        int data_size = PING_PACKET_SIZE - (sizeof(struct icmphdr) + sizeof(struct iphdr));
        printf("PING %s (%s) %d(%d) bytes of data.\n", g_data.host, g_data.ipstr, data_size, packet_size);
}

void	refresh_ping_info(char *error, int sequence)
{
	double time = get_time_ms(&g_data.send_time, &g_data.rec_time);

	refresh_min_max_time(time);
	if (error != NULL)
		printf("From %s icmp_seq=%d %s\n", g_data.ipstr, sequence, error);
	else
	{
		printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d ",PING_PACKET_SIZE, g_data.domainname, g_data.ipstr, g_data.sequence, TTL);
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
	printf("\n--- %s ping statistics ---\n", g_data.host);
    printf("%d packets transmitted, %d received, ", g_data.sequence, g_data.packet_received);
	if (g_data.nb_errors)
		printf("+%d errors, ", g_data.nb_errors);
	printf("%d%% packet loss, ", get_percent_loss());
	printf("time %.0fms\n", get_total_time());
    printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n\n", g_data.min_time,0.0,g_data.max_time,0.0);
}

void    print_data(void)
{
	printf("sockfd: %d\n", g_data.sockfd);
	printf("pid:    %d\n", g_data.pid);
	printf("host:   %s\n", g_data.host);
	printf("ip:     %s\n", g_data.ipstr);
	printf("FQDN :  %s\n", g_data.domainname);
}
