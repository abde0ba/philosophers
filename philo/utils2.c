/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:31:52 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/02 11:23:49 by abbaraka         ###   ########.fr       */
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

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print_m);
	printf("%d %d %s\n", get_current_time() \
	- philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->print_m);
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
