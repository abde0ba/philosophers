/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 07:50:06 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/14 12:47:22 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	int	time;

	time = get_current_time() - philo->start_time;
	printf("%d %d is sleeping\n", time, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	int	time;

	time = get_current_time() - philo->start_time;
	printf("%d %d is thinking\n",  time, philo->id);
}

void	eat(t_philo *philo)
{
	int	time;

	time = get_current_time() - philo->start_time;
	// pthread_mutex_lock(philo->right_fork);
	// if (pthread_mutex_lock(philo->left_fork) != 0)
	// {
	// 	pthread_mutex_unlock(philo->right_fork);
	// 	philo_think(philo);
	// 	return ;
	// }
	printf("%d %d has taken a fork\n", time, philo->id);
	printf("%d %d has taken a fork\n", time, philo->id);
	printf("%d %d is eating\n", time, philo->id);
	ft_usleep(philo->time_to_eat);
	// pthread_mutex_unlock(philo->right_fork);
	// pthread_mutex_unlock(philo->left_fork);
}
void	*routine(void *args)
{
	t_philo	philo;

	philo = *(t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(philo.right_fork);
		if (pthread_mutex_lock(philo.left_fork) != 0)
		{
			pthread_mutex_unlock(philo.right_fork);
			philo_think(&philo);
			return (NULL);
		}
		eat(&philo);
		pthread_mutex_unlock(philo.right_fork);
		pthread_mutex_unlock(philo.left_fork);
		philo_sleep(&philo);
		philo_think(&philo);
	}
	return (NULL);
}

// void *routine(void *args) {
//     t_args arguments = *((t_args *)args);

//     // Try to acquire the right fork first (avoid deadlock)
//     if (pthread_mutex_lock(&(arguments.mutex[arguments.philo.id].mutex)) != 0) {
//     //     Right fork unavailable, return without acquiring any forks
// 	// 	    Philosopher is thinking
// 		printf("%d: %d is thnking\n", arguments.philo.time_to_die, arguments.philo.id);
// 		ft_usleep(arguments.data.time_to_die);
// 		arguments.philo.time_to_die += arguments.data.time_to_die;
//         return (NULL);
//     }

//     // Right fork acquired, try to acquire left fork
//     if (pthread_mutex_lock(&(arguments.mutex[arguments.philo.id + 1].mutex)) != 0) {
//         // Left fork unavailable, release the right fork
//         printf("%d: %d is thnking\n", arguments.philo.time_to_die, arguments.philo.id);
// 		ft_usleep(arguments.data.time_to_die);
// 		arguments.philo.time_to_die += arguments.data.time_to_die;
//         return (NULL);
//     }

//     // Both forks acquired, philosopher is eating
//     printf("%d: %d has taken a fork\n", arguments.philo.time_to_die, arguments.philo.id);
//     printf("%d: %d has taken a fork\n", arguments.philo.time_to_die, arguments.philo.id);
//     printf("%d: %d is eating\n", arguments.philo.time_to_die, arguments.philo.id);
//     ft_usleep(arguments.data.time_to_eat);
// 	arguments.philo.time_to_die += arguments.data.time_to_die;

//     // Done eating, release both forks
//     pthread_mutex_unlock(&(arguments.mutex[arguments.philo.id].mutex));
//     pthread_mutex_unlock(&(arguments.mutex[(arguments.philo.id + arguments.data.philos_number - 1) % arguments.data.philos_number].mutex));

//     // // Philosopher is sleeping
//     // printf("%d: %d is sleeping\n", arguments.philo.time_to_die, arguments.philo.id);
//     // ft_usleep(arguments.data.time_to_sleep);
// 	// arguments.philo.time_to_die += arguments.data.time_to_die;



//     return (NULL);
// }


int	start(t_data data, t_philo *philos)
{
	int		id;

	id = 0;
	while (id < data.philos_number)
	{
		if (pthread_create(&philos[id].philo, NULL, &routine, (void *)&philos[id]) != 0)
			printf("thread N %d failed in creation\n", id + 1);
		id++;
	}
	id = 0;
	while (id < data.philos_number)
	{
		if (pthread_join(philos[id].philo, NULL) != 0)
			printf("thread N %d failed in joining\n", id + 1);
		id++;
	}
	return (1);
}

int	philos_init(t_data data, t_philo *philos, t_mutex *mutex)
{
	int	id;

	id = 0;
	while (id < data.philos_number)
	{
		philos[id].id = id + 1;
		philos[id].time_to_eat = data.time_to_eat;
		philos[id].time_to_sleep = data.time_to_sleep;
		philos[id].time_to_die = 0;
		philos[id].start_time = get_current_time();
		if (pthread_mutex_init(&mutex[id].mutex, NULL) != 0)
		{
			printf("\n mutex init has failed\n"); 
			return 1; 
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