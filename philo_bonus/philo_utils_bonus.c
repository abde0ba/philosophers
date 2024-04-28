	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:50:06 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/25 17:02:54 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*program_monitoring(void *arg)
{
	int	i;
	t_philo *philo;

	philo = (t_philo *)arg;

	while (1)
	{
			// sem_wait(philo->death);
			// sem_wait(philo->meals_check);
			// if (philo->data->finished == philo->data->philos_number)
			// {
			// 	sem_post(philo->meals_check);
			// 	sem_unlink("/forks_sem");
			// 	sem_unlink("/lock_sem");
			// 	sem_unlink("/meals_check");
			// 	sem_unlink("/print_sem");
			// 	i = 0;
			// 	while (i < philo->data->philos_number)
			// 	{
			// 		if (philo->id != i + 1)
			// 			kill(philo->data->philos[i].philo, SIGTERM);
			// 		i++;
			// 	}
				
			// 	return (NULL);
			// }
			// sem_post(philo->meals_check);
			sem_wait(philo->lock_sem);
			if (philo->time_to_die < get_current_time() - philo->last_time_meal)
			{
				sem_wait(philo->data->print_sem);
				sem_post(philo->meals_check);
				printf("%d %d died\n", get_current_time() - philo->start_time, philo->id);
				sem_post(philo->death);
				i = 0;
				return (NULL);
			}
			sem_post(philo->lock_sem);
	}
	return (NULL);
}

int routine(t_philo *philo)
{
	pthread_t	monitor;

	philo->start_time = get_current_time();
	pthread_create(&monitor, NULL, &program_monitoring, (void *)philo);
	pthread_detach(monitor);
	while (1)
	{
		// if (philo->meals_limit > -1 && philo->meals_limit <= philo->meals_num)
		// 	return (0);
		eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		// if (program_monitoring(philo) == 0)
		// 	return (0);
	}
	return (0);
}



int	start(t_data *data, t_philo *philos)
{
	int		id;

	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	sem_unlink("/meals_check");
	sem_unlink("/print_sem");
	sem_unlink("/death");

	// program_monitoring(data, philos);
	// while (data->philo_init < data->philos_number)
	// {
	// 	philos[data->philo_init].start_time = get_current_time();
	// 	data->philo_init++;
	// }
	data->philo_init = 0;
	while (data->philo_init < data->philos_number)
	{
		philos[data->philo_init].philo = fork();
		if (philos[data->philo_init].philo == -1)
			printf("child process N %d failed in creation\n", data->philo_init + 1);
		if (philos[data->philo_init].philo == 0)
			if (routine(&philos[data->philo_init]) == 0)
				return (1);
		data->philo_init++;
		usleep(100);
	}
 	// if (program_monitoring(data, philos) == 0)
	// {
	// 	mutex_destroy_all(data, philos);
	// 	return (1);
	// }
	id = 0;
	// while (1)
	// {
	// data->philo_init = 0;
	// while (data->philo_init < data->philos_number)
	// {
	// 	sem_post(data->ready);
	// 	philos[data->philo_init].start_time = get_current_time();
	// 	data->philo_init++;
	// }
	sem_wait(philos[id].death);
	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	sem_unlink("/meals_check");
	sem_unlink("/print_sem");
	id = 0;
	while (id < data->philos_number)
	{
		kill(philos[id].philo, SIGTERM);
		id++;
	}
	// }
	return (1);
}

int	init_each_philo(t_data *data, t_philo *philos, int id, sem_t *forks_sem)
{
	philos[id].id = id + 1;
	philos[id].time_to_eat = data->time_to_eat;
	philos[id].time_to_sleep = data->time_to_sleep;
	philos[id].time_to_die = data->time_to_die;
	philos[id].meals_num = 0;
	philos[id].meals_limit = data->number_of_meals;
	philos[id].start_time = get_current_time();
	philos[id].eating = 0;
	philos[id].data = data;
	philos[id].last_time_meal = get_current_time();
	philos[id].forks = forks_sem;
	philos[id].death = data->death;
	return (0);
}

int	philos_init(t_data *data, t_philo *philos, sem_t *forks_sem)
{
	int	id;

	if (init_sem_data(data) != 0)
		return (1);
	id = 0;
	while (id < data->philos_number)
	{
		if (init_each_philo(data, philos, id, forks_sem) == 1)
			return (1);
		id++;
	}
	return (0);
}
