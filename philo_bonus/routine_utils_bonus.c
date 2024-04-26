/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:55:35 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/26 20:02:36 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	print_msg(philo, "has taken a fork");
	sem_wait(philo->forks);
	print_msg(philo, "has taken a fork");
}

void	put_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
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
	sem_wait(philo->lock_sem);
	philo->eating = 1;
	philo->meals_num++;
	philo->last_time_meal = get_current_time();
	sem_post(philo->lock_sem);
	sem_wait(philo->meals_check);
	if (philo->meals_limit > -1 && philo->meals_limit == philo->meals_num)
		philo->data->finished++;
	sem_post(philo->meals_check);
	ft_usleep(philo->time_to_eat);
	put_forks(philo);
}
