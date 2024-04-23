/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:50:06 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/23 10:35:08 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print_m);
	printf("%d %d %s\n", get_current_time() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->print_m);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{

	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(philo->left_fork);
	// 	print_msg(philo, "has taken a fork");
	// 	pthread_mutex_lock(philo->right_fork);
	// 	print_msg(philo, "has taken a fork");
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->right_fork);
	// 	print_msg(philo, "has taken a fork");
	// 	pthread_mutex_lock(philo->left_fork);
	// 	print_msg(philo, "has taken a fork");
	// }
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork");

}

void	put_forks(t_philo *philo)
{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

}
void	eat(t_philo *philo)
{
	take_forks(philo);
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->lock_m);
	philo->eating = 1;
	philo->meals_num++;
	philo->last_time_meal = get_current_time();
	pthread_mutex_unlock(&philo->lock_m);
	pthread_mutex_lock(philo->meals_check);
	if (philo->meals_limit > -1 && philo->meals_limit == philo->meals_num)
		philo->data->finished++;
	pthread_mutex_unlock(philo->meals_check);
	ft_usleep(philo->time_to_eat);
	put_forks(philo);
}


void	*routine(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	// philo_think(philo);
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

int	check_dead(t_philo *philo)
{
	int	time_to_die;
	int	last_time_meal;
	int	eating;

	
	pthread_mutex_lock(&philo->lock_m);
	time_to_die = philo->time_to_die;
	last_time_meal = philo->last_time_meal;
	eating = philo->eating;
	return (time_to_die <= get_current_time() - last_time_meal);
}

int	program_monitoring(t_data *data, t_philo *philos)
{
	int	i;
	int	num;

	
	while (1)
	{
		i = 0;
		num = 0;
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
			{
				pthread_mutex_lock(philos[i].print_m);
				printf("%d %d died\n", get_current_time() - philos[i].start_time, philos[i].id);
				// pthread_mutex_unlock(philos[i].print_m);
				pthread_mutex_unlock(&philos[i].lock_m);
				return (0);
			}
			pthread_mutex_unlock(&philos[i].lock_m);
			i++;
		}
		
	}
	return (0);
}
int	mutex_destroy_all(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philos_number)
	{
		pthread_mutex_destroy(&philos[i].eat_m);
		pthread_mutex_destroy(&philos[i].lock_m);
		if (pthread_mutex_destroy(philos[i].left_fork) != 0)
		{
			pthread_mutex_unlock(philos[i].left_fork);
			pthread_mutex_destroy(philos[i].left_fork);
		}
		if (pthread_mutex_destroy(philos[i].right_fork) != 0)
		{
			pthread_mutex_unlock(philos[i].right_fork);
			pthread_mutex_destroy(philos[i].right_fork);
		}
		i++;
	}
	pthread_mutex_destroy(&data->print_m);
	pthread_mutex_destroy(&data->lock_m);
	pthread_mutex_destroy(&data->meals_check);
	return (1);
}

int	start(t_data *data, t_philo *philos)
{
	int		id;
	// void	*status;

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

int	philos_init(t_data *data, t_philo *philos, t_mutex *mutex)
{
	int	id;

	pthread_mutex_init(&data->lock_m, NULL);
	pthread_mutex_init(&data->print_m, NULL);
	pthread_mutex_init(&data->meals_check, NULL);
	id = 0;
	while (id < data->philos_number)
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
		pthread_mutex_init(&philos[id].eat_m, NULL);
		pthread_mutex_init(&philos[id].lock_m, NULL);
		philos[id].last_time_meal = get_current_time();
		if (pthread_mutex_init(&mutex[id].mutex, NULL) != 0)
		{
			printf("\n mutex init has failed\n"); 
			return (1); 
		}
		mutex[id].num = id + 1;
		philos[id].left_fork = &(mutex[id].mutex);
		if (id == (data->philos_number - 1))
			philos[id].right_fork = &(mutex[0].mutex);
		else
			philos[id].right_fork = &(mutex[id + 1].mutex);
		id++;
	}
	return (0);
}
