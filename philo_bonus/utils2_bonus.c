/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:31:52 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/29 12:52:20 by abbaraka         ###   ########.fr       */
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
	printf("%lu %d %s\n", get_current_time() - philo->start_time, philo->id, msg);
	sem_post(philo->data->print_sem);
}
