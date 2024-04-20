/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:17 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/19 21:02:17 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;
	t_mutex	*mutex;

	data.number_of_meals = 0;
	if (((ac > 6 || ac < 5) || !init_data(&data, av)) && err_args())
		return (1);
	philos = malloc(data.philos_number * sizeof(t_philo));
	mutex = malloc(data.philos_number * sizeof(t_mutex));
	if (!philos || !mutex)
		return (free(philos), free(mutex), 1);
	philos_init(data, philos, mutex);
	if (start(data, philos) == 1)
		return (free(philos), free(mutex), 0);
	return (0);
}
