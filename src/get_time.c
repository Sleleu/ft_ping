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

double	get_time_ms(struct timeval *send_time, struct timeval *rec_time)
{
	double elapsed_time;

	elapsed_time = (rec_time->tv_sec - send_time->tv_sec) * 1000.0;
	elapsed_time += (rec_time->tv_usec - send_time->tv_usec) / 1000.0;
	return elapsed_time;
}