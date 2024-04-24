/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:53:20 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/24 14:56:06 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy(pthread_mutex_t mutex)
{
	if (pthread_mutex_destroy(&mutex) != 0)
	{
		pthread_mutex_unlock(&mutex);
		pthread_mutex_destroy(&mutex);
	}
}

int	init_mutex_data(t_data *data)
{
	if (pthread_mutex_init(&data->lock_m, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->print_m, NULL) != 0)
	{
		mutex_destroy(data->lock_m);
		return (-1);
	}
	if (pthread_mutex_init(&data->meals_check, NULL) != 0)
	{
		mutex_destroy(data->lock_m);
		mutex_destroy(data->print_m);
		return (-1);
	}
	return (0);
}

int	init_mutex_philos(t_philo *philo, t_mutex *mutex)
{
	if (pthread_mutex_init(&philo->lock_m, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&mutex[philo->id - 1].mutex, NULL) != 0)
	{
		mutex_destroy(philo->lock_m);
		printf("\n mutex init has failed\n");
		return (-1);
	}
	return (0);
}

int	mutex_destroy_philos(t_philo *philos, int id, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < id)
	{
		init_mutex_philos(&philos[i], mutex);
		i++;
	}
	return (0);
}

int	mutex_destroy_all(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philos_number)
	{
		mutex_destroy(philos[i].lock_m);
		mutex_destroy(*philos[i].left_fork);
		mutex_destroy(*philos[i].right_fork);
		i++;
	}
	mutex_destroy(data->print_m);
	mutex_destroy(data->lock_m);
	mutex_destroy(data->meals_check);
	return (1);
}
