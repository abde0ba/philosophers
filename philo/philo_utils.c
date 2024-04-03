/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:50:06 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/03 09:34:49 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	// if (id == 0)
	// {
	// 	philos[id].
	// }
	(void)args;
	return (NULL);
}

int	start(t_data data, t_philo *philos)
{
	t_args	args;
	int		id;

	id = 0;
	while (id < data.philos_number)
	{
		args.id = id;
		args.philos = philos;
		pthread_create(&philos[id].philo, NULL, &routine, (void *)&args);
		id++;
	}
	return (1);
}

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