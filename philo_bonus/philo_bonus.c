/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:36:17 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/03 11:49:17 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;
	sem_t	*forks_sem;

	unlink_semaphore_data();
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->number_of_meals = -1;
	data->finished = 0;
	data->philo_init = 0;
	if (((ac > 6 || ac < 5) || !init_data(data, av)) && err_args())
		return (free(data), 1);
	philos = malloc(data->philos_number * sizeof(t_philo));
	forks_sem = sem_open("/forks_sem", O_CREAT, 0644, data->philos_number);
	if (!philos)
		return (sem_close(forks_sem), unlink_semaphore_data(),
			free(data), free(philos), 1);
	if (philos_init(data, philos, forks_sem) != 0)
		return (free(data), free(philos), 1);
	data->philos = philos;
	if (start(data, philos) != 0)
		return (unlink_semaphore_data(), free(data), free(philos), 1);
	return (free(data), free(philos), 0);
}
