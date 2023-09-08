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