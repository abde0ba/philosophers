/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:55:35 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/24 10:22:25 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
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

void	philo_think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->lock_m);
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
