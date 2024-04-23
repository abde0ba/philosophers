/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:31:52 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/23 08:52:42 by abbaraka         ###   ########.fr       */
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
		if (ft_atoi(num) == -1)
		{
			free(num);
			return (0);
		}
		free(num);
		i++;
	}
	return (1);
}
