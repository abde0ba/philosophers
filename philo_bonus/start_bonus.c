/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:59:30 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/05 23:37:21 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*program_monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->lock_sem);
		if (philo->time_to_die < get_current_time() - philo->last_time_meal)
		{
			sem_wait(philo->data->print_sem);
			printf("%lu %d died\n", get_current_time() \
			- philo->start_time, philo->id);
			sem_post(philo->data->death);
		}
		sem_post(philo->lock_sem);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	pthread_t	monitor;
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->philo = fork();
	if (!philo->philo < 0)
		return (NULL);
	if (!philo->philo)
	{
		if (pthread_create(&monitor, NULL, &program_monitoring, arg) != 0)
			printf("Error in creating monitor thread\n");
		pthread_detach(monitor);
		while (1)
		{
			if (philo->meals_limit > -1
				&& philo->meals_num == philo->meals_limit)
				sem_post(philo->data->limit);
			if (philo->meals_limit == 0)
				break ;
			eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}
	}
	return (NULL);
}

void	*check_meals(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	i = 0;
	while (i < data->philos_number)
	{
		sem_wait(data->limit);
		i++;
	}
	sem_post(data->death);
	return (NULL);
}

int	start(t_data *data, t_philo *philos)
{
	int			id;
	pthread_t	monitor_meals;

	id = 0;
	while (id < data->philos_number)
	{
		if (pthread_create(&philos[id].thread, NULL, \
		&routine, (void *)&philos[id]) != 0)
			return (printf("Failed to create thread"), 1);
		pthread_detach(philos[id].thread);
		id++;
	}
	if (philos[0].meals_limit != -1)
	{
		if (pthread_create(&monitor_meals, NULL, \
		&check_meals, (void *)data) != 0)
			return (printf("Failed to create thread"), 1);
		pthread_detach(monitor_meals);
	}
	destroy_semaphore_and_end_program(data);
	return (0);
}
