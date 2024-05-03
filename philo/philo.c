/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:17 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/03 11:07:43 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;
	t_mutex	*mutex;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->number_of_meals = -1;
	data->finished = 0;
	if (((ac > 6 || ac < 5) || !init_data(data, av)) && err_args())
		return (free(data), 1);
	philos = malloc(data->philos_number * sizeof(t_philo));
	mutex = malloc(data->philos_number * sizeof(t_mutex));
	if (!philos || !mutex)
		return (free(data), free(philos), free(mutex), 1);
	if (philos_init(data, philos, mutex) != 0)
		return (free(data), free(philos), free(mutex), 1);
	if (start(data, philos) == 0)
		return (free(philos), free(mutex), free(data), 1);
	else
		return (free(philos), free(mutex), free(data), 0);
	return (0);
}
