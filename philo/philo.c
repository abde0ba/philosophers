/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:17 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/03 08:04:08 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	data.number_of_meals = 0;
	if (((ac > 6 || ac < 5) || !init_data(&data, av)) && err_args())
		return (1);
	philos = malloc(data.philos_number * sizeof(t_philo));
	if (!philos)
		return (1);
	philos_init(data, philos);
	printf("%d", philos[0].time_to_die);
	return (0);
}
