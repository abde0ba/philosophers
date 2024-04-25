/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:18:24 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/24 10:17:41 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	err_args(void)
{
	write(2, "Error\n", 6);
	write(2, "Please provide the required number of arguments\n", 48);
	return (1);
}

int	check_nums(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' && av[i][j + 1] == '0' && !av[i][j + 2])
				return (1);
			if (!(av[i][j] >= '0' && av[i][j] <= '9')
				&& av[i][j] != ' ' && av[i][j] != '+')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	number;
	int				sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	if ((sign == 1 && number > 2147483647))
		return (-1);
	return (number * sign);
}

int	check_two_in_one(char **av)
{
	char	*num;
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		num = ft_strtrim(av[i], " ");
		j = 0;
		while (num[j])
		{
			if (num[j] == '-' && num[j + 1] == '0' && !num[j + 2])
				return (free(num), 1);
			if (!(num[j] >= '0' && num[j] <= '9') && num[j] != '+')
			{
				free(num);
				return (0);
			}
			j++;
		}
		free(num);
		i++;
	}
	return (1);
}

int	init_data(t_data *data, char **av)
{
	char	*num;

	if (!check_nums(av) || !check_two_in_one(av) || !check_int(av))
		return (0);
	num = ft_strtrim(av[1], " ");
	data->philos_number = ft_atoi(num);
	free(num);
	num = ft_strtrim(av[2], " ");
	data->time_to_die = ft_atoi(num);
	free(num);
	num = ft_strtrim(av[3], " ");
	data->time_to_eat = ft_atoi(num);
	free(num);
	num = ft_strtrim(av[4], " ");
	data->time_to_sleep = ft_atoi(num);
	free(num);
	if (av[5])
	{
		num = ft_strtrim(av[5], " ");
		data->number_of_meals = ft_atoi(num);
		free(num);
	}
	return (1);
}
