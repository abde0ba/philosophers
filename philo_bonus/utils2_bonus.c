/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:31:52 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/07 00:30:39 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_msg(t_philo *philo, char *msg)
{
	sem_wait(philo->data->print_sem);
	ft_putnbr_fd((int)(get_current_time() - philo->start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	sem_post(philo->data->print_sem);
}

int	meals_arg_set(char *arg, t_data *data)
{
	char	*num;

	num = ft_strtrim(arg, " ");
	if (ft_atoi(num) < 0)
		return (0);
	data->number_of_meals = ft_atoi(num);
	free(num);
	return (1);
}

int	check_negative_data(t_data *data)
{
	if (data->philos_number == -1
		|| data->time_to_die == -1
		|| data->time_to_eat == -1
		|| data->time_to_sleep == -1)
		return (0);
	return (1);
}

void	unlink_semaphore_data(void)
{
	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	sem_unlink("/meals_check");
	sem_unlink("/print_sem");
	sem_unlink("/death");
	sem_unlink("/limit");
}
