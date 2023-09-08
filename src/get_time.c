/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 23:54:38 by sleleu            #+#    #+#             */
/*   Updated: 2023/09/06 23:54:49 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ping.h"

void	refresh_min_max_time(double time)
{
	if (g_data.sequence == 1)
	{
		get_timeday(&g_data.start_time);
		g_data.max_time = time;
		g_data.min_time = time;
	}
	time < g_data.min_time ? g_data.min_time = time : (void)time;
	time > g_data.max_time ? g_data.max_time = time : (void)time;
}

double	get_total_time(void)
{
	struct timeval end_time;
	double total_time;
	
	get_timeday(&end_time);
	total_time = get_time_ms(&g_data.start_time, &g_data.rec_time);
	if (g_data.rec_time.tv_sec == 0) // no packet received
		total_time = get_time_ms(&g_data.start_time, &end_time);
	if (g_data.sequence == 1) // only 1 packet sent
		total_time = 0.0;
	return (total_time);
}

void	get_timeday(struct timeval *timeval)
{
	if (gettimeofday(timeval, NULL) == -1)
	{
		fprintf(stderr, "ft_ping: gettimeofday error\n");
		exit_failure(1);
	}
}

double	get_time_ms(struct timeval *start, struct timeval *end)
{
	double elapsed_time;

	elapsed_time = (end->tv_sec - start->tv_sec) * 1000.0;
	elapsed_time += (end->tv_usec - start->tv_usec) / 1000.0;
	return elapsed_time;
}