/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:50:06 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/24 09:03:59 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat);
	while (1)
	{
		if (philo->meals_limit > -1 && philo->meals_limit <= philo->meals_num)
			return (args);
		eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (args);
}

int	program_monitoring(t_data *data, t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->philos_number)
		{	
			pthread_mutex_lock(philos[i].meals_check);
			if (data->finished == data->philos_number)
			{
				pthread_mutex_unlock(philos[i].meals_check);
				return (0);
			}
			pthread_mutex_unlock(philos[i].meals_check);
			pthread_mutex_lock(&philos[i].lock_m);
			if (philos[i].time_to_die < get_current_time() - philos[i].last_time_meal)
				return (pthread_mutex_lock(philos[i].print_m),
				printf("%d %d died\n", get_current_time() - philos[i].start_time, philos[i].id),
				pthread_mutex_unlock(&philos[i].lock_m), 0);
			pthread_mutex_unlock(&philos[i].lock_m);
			i++;
		}
	}
	return (0);
}

int	start(t_data *data, t_philo *philos)
{
	int		id;

	id = 0;
	while (id < data->philos_number)
	{
		if (pthread_create(&philos[id].philo, NULL, &routine, (void *)&philos[id]) != 0)
			printf("thread N %d failed in creation\n", id + 1);
		id++;
	}
 	if (program_monitoring(data, philos) == 0)
	{
		id = 0;
		while (id < data->philos_number)
		{
			if (pthread_detach(philos[id].philo) != 0)
				printf("thread N %d failed in joining\n", id + 1);
			id++;
		}
		mutex_destroy_all(data, philos);
		return (1);
	}
	return (1);
}

int	init_each_philo(t_data *data, t_philo *philos, int id, t_mutex *mutex)
{
	philos[id].id = id + 1;
	philos[id].time_to_eat = data->time_to_eat;
	philos[id].time_to_sleep = data->time_to_sleep;
	philos[id].time_to_die = data->time_to_die;
	philos[id].meals_num = 0;
	philos[id].meals_limit = data->number_of_meals;
	philos[id].start_time = get_current_time();
	philos[id].dead = 0;
	philos[id].eating = 0;
	philos[id].print_m = &(data->print_m);
	philos[id].meals_check = &(data->meals_check);
	philos[id].data = data;
	philos[id].last_time_meal = get_current_time();
	if (init_mutex_philos(&philos[id], mutex) != 0)
	{
		mutex_destroy_philos(philos, id, mutex);
		return (1);
	}
	mutex[id].num = id + 1;
	philos[id].left_fork = &(mutex[id].mutex);
	if (id == (data->philos_number - 1))
		philos[id].right_fork = &(mutex[0].mutex);
	else
		philos[id].right_fork = &(mutex[id + 1].mutex);
	return (0);
}

int	philos_init(t_data *data, t_philo *philos, t_mutex *mutex)
{
	int	id;

	if (init_mutex_data(data) != 0)
		return (1);
	id = 0;
	while (id < data->philos_number)
	{
		if (init_each_philo(data, philos, id, mutex) == 1)
			return (1);
		id++;
	}
	return (0);
}
