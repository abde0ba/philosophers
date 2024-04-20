/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:50:06 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/20 13:27:39 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	int	time;

	time = get_current_time() - philo->start_time;
	// if (philo->dead == 0)
	// {
		pthread_mutex_lock(philo->print_m);
		printf("%d %d is sleeping\n", time, philo->id);
		ft_usleep(philo->time_to_sleep);
		pthread_mutex_unlock(philo->print_m);
	// }
}

void	philo_think(t_philo *philo)
{
	int	time;

	time = get_current_time() - philo->start_time;
	// if (philo->dead == 0)
		pthread_mutex_lock(philo->print_m);
		printf("%d %d is thinking\n",  time, philo->id);
		pthread_mutex_unlock(philo->print_m);
}

void	eat(t_philo *philo)
{
	int	time;

	time = get_current_time() - philo->start_time;

	// printf("%d %d should be dead now.\n", get_current_time() - philo->start_time, philo->id);

	// if (philo->dead == 0)
	// {
		philo->eating = 1;
		// if (philo->time_to_die <= get_current_time() - (philo->last_time_meal))
		// 	philo->dead = 1;
		pthread_mutex_lock(&philo->eat_m);
		pthread_mutex_lock(philo->print_m);
		printf("%d %d has taken a fork\n", time, philo->id);
		printf("%d %d has taken a fork\n", time, philo->id);
		printf("%d %d is eating\n", time, philo->id);
		pthread_mutex_unlock(philo->print_m);
		philo->meals_num++;
		ft_usleep(philo->time_to_eat);
		philo->last_time_meal = get_current_time();
		pthread_mutex_unlock(&philo->eat_m);
		philo->eating = 0;
	// }
}
int	check_dead(int time_to_die, int last_meal, int start_time, int id)
{
	// int	i;

	// i = 0;
	// while (i < data.philos_number)
	// {
	// 	pthread_mutex_lock(&philos[i].eat_m);
	// 	// printf("last %d\n", philos->last_time_meal);
	// 	if (philos[i].dead)
	// 	{
	// 			// printf("time update %d for philo %d from monitor thread\n", philos[i].last_time_meal, philos[i].id);
	// 			philos[i].dead = 1;
	// 			printf("%d %d died\n", get_current_time() - philos[i].start_time, philos[i].id);
	// 			exit(0);
	// 	}
	// 	else
	// 	{
	// 		usleep(1000);
	// 		printf("last meal :%d for philo %d\n", get_current_time() - *philos[i].last_time_meal, philos[i].id);
	// 		usleep(1000);
	// 	}
	// 	pthread_mutex_unlock(&philos[i].eat_m);
	// 	i++;
	// }
	if (time_to_die <= get_current_time() - last_meal)
	{
				printf("%d %d died\n", get_current_time() - start_time, id);
				exit(0);
	}
	return (0);
}

int	program_monitoring(t_data data, t_philo *philos)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < data.philos_number)
		{
			pthread_mutex_lock(&philos[i].eat_m);
			if (philos[i].time_to_die <= get_current_time() - philos[i].last_time_meal)
			{
				pthread_mutex_lock(&data.lock_m);
				while (j < data.philos_number)
				{
					philos[i].dead = 1;
					j++;
				}
				pthread_mutex_unlock(&data.lock_m);
				pthread_mutex_lock(&data.print_m);
				printf("%d %d died\n", get_current_time() - philos[i].start_time, philos[i].id);
				pthread_mutex_unlock(&data.print_m);
				return (0);
			}
			pthread_mutex_unlock(&philos[i].eat_m);
			i++;
		}
	}
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;
	// pthread_t	monitor;
	
	philo = (t_philo *)args;
	// global_eat[philo.id - 1] = get_current_time();
	// pthread_create(&monitor, NULL, &program_monitoring, args);
	// pthread_detach(monitor);
	while (1)
	{
		pthread_mutex_lock(philo->lock_m);
		if (philo->dead)
			return (args);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		// pthread_mutex_lock(philo->right_fork);
		// if (pthread_mutex_lock(philo->left_fork) != 0)
		// {
		// 	pthread_mutex_unlock(philo->right_fork);
		// 	return (NULL);
		// }

		eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_unlock(philo->lock_m);
	}
	return (args);
}

// int	mutex_destroy_all(t_data data, t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data.philos_number)
// 	{
// 		pthread_mutex_destroy(&philos[i].eat_m);
// 		if (pthread_mutex_destroy(philos[i].left_fork) != 0)
// 		{
// 			pthread_mutex_unlock(philos[i].left_fork);
// 			pthread_mutex_destroy(philos[i].left_fork);
// 		}
// 		if (pthread_mutex_destroy(philos[i].right_fork) != 0)
// 		{
// 			pthread_mutex_unlock(philos[i].right_fork);
// 			pthread_mutex_destroy(philos[i].right_fork);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int	start(t_data data, t_philo *philos)
{
	int		id;
	void	*status;

	id = 0;
	while (id < data.philos_number)
	{
		if (pthread_create(&philos[id].philo, NULL, &routine, (void *)&philos[id]) != 0)
			printf("thread N %d failed in creation\n", id + 1);
		id++;
	}
	id = 0;
 	if (program_monitoring(data, philos) == 0)
	{
		// mutex_destroy_all(data, philos);
		return (1);
	}
	while (id < data.philos_number)
	{
		if (pthread_join(philos[id].philo, &status) != 0)
			printf("thread N %d failed in joining\n", id + 1);
		id++;
	}
	return (1);
}

int	philos_init(t_data data, t_philo *philos, t_mutex *mutex)
{
	int	id;
	// int	*last_meal;

	// last_meal = malloc(data.philos_number * sizeof(int));
	pthread_mutex_init(&data.lock_m, NULL);
	pthread_mutex_init(&data.print_m, NULL);
	id = 0;
	while (id < data.philos_number)
	{
		philos[id].id = id + 1;
		philos[id].time_to_eat = data.time_to_eat;
		philos[id].time_to_sleep = data.time_to_sleep;
		philos[id].time_to_die = data.time_to_die;
		philos[id].meals_num = 0;
		philos[id].start_time = get_current_time();
		philos[id].dead = 0;
		philos[id].eating = 0;
		philos[id].print_m = &(data.print_m);
		philos[id].lock_m = &(data.lock_m);
		pthread_mutex_init(&philos[id].eat_m, NULL);
		pthread_mutex_init(&philos[id].death_m, NULL);
		// philos[id]->last_time_meal = *((int *)malloc(sizeof(int)));
		// last_meal[id] = get_current_time();
		// philos[id].last_time_meal = &last_meal[id];
		philos[id].last_time_meal = get_current_time();
		if (pthread_mutex_init(&mutex[id].mutex, NULL) != 0)
		{
			printf("\n mutex init has failed\n"); 
			return (1); 
		}
		mutex[id].num = id + 1;
		philos[id].left_fork = &(mutex[id].mutex);
		if (id == (data.philos_number - 1))
			philos[id].right_fork = &(mutex[0].mutex);
		else
			philos[id].right_fork = &(mutex[id + 1].mutex);
		id++;
	}
	return (0);
}
