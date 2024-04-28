/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:17 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/27 21:37:35 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;
	sem_t	*forks_sem;
	int status;

	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	sem_unlink("/meals_check");
	sem_unlink("/print_sem");
	data = malloc(sizeof(t_data));
	data->number_of_meals = -1;
	data->finished = 0;
	data->philo_init = 0;
	if (!data)
		return (1);
	if (((ac > 6 || ac < 5) || !init_data(data, av)) && err_args())
		return (1);
	philos = malloc(data->philos_number * sizeof(t_philo));
	forks_sem = sem_open("/forks_sem", O_CREAT, 0644, data->philos_number);
	if (!philos)
		return (free(philos), 1);
	if (philos_init(data, philos, forks_sem) != 0)
		return (free(philos), 1);
	data->philos = philos;
	start(data, philos);
	sleep(3);
    while (waitpid(-1, &status, 0) > 0)
        ;
		// return (free(philos), free(data), 0);
	return (0);
}
