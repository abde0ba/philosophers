/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:53:20 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/28 18:09:07 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem_data(t_data *data)
{
	data->lock_s = sem_open("/lock_sem", O_CREAT, 0644, 1);
	data->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	data->meals_check = sem_open("/meals_check", O_CREAT, 0644, 1);
	data->death = sem_open("/death", O_CREAT, 0644, 0);
	data->ready = sem_open("/ready", O_CREAT, 0644, 0);
	return (0);
}

int	init_sem_philos(t_philo *philo)
{
	philo->lock_sem = sem_open("/lock_sem", O_CREAT, 0644, 1);

	return (0);
}

// int	mutex_destroy_philos(t_philo *philos, int id, t_mutex *mutex)
// {
// 	int	i;

// 	i = 0;
// 	while (i < id)
// 	{
// 		init_sem_philos(&philos[i]);
// 		i++;
// 	}
// 	return (0);
// }

// void	mutex_destroy(pthread_mutex_t mutex)
// {
// 	if (pthread_mutex_destroy(&mutex) != 0)
// 	{
// 		pthread_mutex_unlock(&mutex);
// 		pthread_mutex_destroy(&mutex);
// 	}
// }

// int	mutex_destroy_all(t_data *data, t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philos_number)
// 	{
// 		mutex_destroy(philos[i].lock_sem);
// 		mutex_destroy(*philos[i].left_fork);
// 		mutex_destroy(*philos[i].right_fork);
// 		i++;
// 	}
// 	mutex_destroy(data->print_m);
// 	mutex_destroy(data->lock_sem);
// 	mutex_destroy(data->meals_check);
// 	return (1);
// }
