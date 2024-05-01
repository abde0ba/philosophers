/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:32:38 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/29 10:01:49 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "time error\n", 11);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time() + milliseconds;
	// while (1)
	// {
	// 	if ((get_current_time() - start) >= milliseconds)
	// 		break ;
	// 	usleep(50);
	// }
	while (get_current_time() < start)
		usleep(100);
	return (0);
}