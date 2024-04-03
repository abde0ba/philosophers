/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:50:06 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/03 08:03:46 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_init(t_data data, t_philo *philos)
{
	int	id;

	id = 0;
	while (id < data.philos_number)
	{
		philos[id].id = id;
		philos[id].time_to_eat = data.time_to_eat;
		philos[id].time_to_sleep = data.time_to_sleep;
		philos[id].time_to_die = data.time_to_die;
		id++;
	}
	
	return (0);
}