/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:31:52 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/23 20:01:25 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_int(char **av)
{
	int		i;
	char	*num;

	i = 0;
	while (av[i])
	{
		num = ft_strtrim(av[i], " ");
		if (num[0] == '\0' || ft_atoi(num) == -1)
		{
			free(num);
			return (0);
		}
		free(num);
		i++;
	}
	return (1);
}

int	init_mutex_data(t_data *data)
{
	if (pthread_mutex_init(&data->lock_m, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->print_m, NULL) != 0)
	{
		pthread_mutex_destroy(&data->lock_m);
		return (-1);
	}
	if (pthread_mutex_init(&data->meals_check, NULL) != 0)
	{
		pthread_mutex_destroy(&data->lock_m);
		pthread_mutex_destroy(&data->print_m);
		return (-1);
	}
	return (0);
}

int	init_mutex_philos(t_philo *philo, t_mutex *mutex)
{
	if (pthread_mutex_init(&philo->eat_m, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&philo->lock_m, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->eat_m);
		return (-1);
	}
	if (pthread_mutex_init(&mutex[philo->id].mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->lock_m);
		pthread_mutex_destroy(&philo->eat_m);
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