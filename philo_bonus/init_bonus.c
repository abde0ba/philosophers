/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:54:36 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/05 23:28:17 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem_data(t_data *data)
{
	data->lock_s = sem_open("/lock_sem", O_CREAT, 0644, 1);
	if (data->lock_s == (sem_t *)SEM_FAILED)
		return (1);
	data->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	if (data->print_sem == (sem_t *)SEM_FAILED)
		return (sem_close(data->lock_s), 1);
	data->meals_check = sem_open("/meals_check", O_CREAT, 0644, 1);
	if (data->meals_check == (sem_t *)SEM_FAILED)
		return (sem_close(data->print_sem), sem_close(data->lock_s), 1);
	data->death = sem_open("/death", O_CREAT, 0644, 0);
	if (data->death == (sem_t *)SEM_FAILED)
		return (sem_close(data->print_sem), sem_close(data->lock_s),
			sem_close(data->meals_check), 1);
	data->limit = sem_open("/limit", O_CREAT, 0644, 0);
	if (data->limit == (sem_t *)SEM_FAILED)
		return (sem_close(data->print_sem), sem_close(data->lock_s),
			sem_close(data->meals_check), sem_close(data->death), 1);
	return (0);
}

int	init_each_philo(t_data *data, t_philo *philos, int id, sem_t *forks_sem)
{
	philos[id].id = id + 1;
	philos[id].time_to_eat = data->time_to_eat;
	philos[id].time_to_sleep = data->time_to_sleep;
	philos[id].time_to_die = data->time_to_die;
	philos[id].meals_num = 0;
	philos[id].meals_limit = data->number_of_meals;
	philos[id].start_time = get_current_time();
	philos[id].eating = 0;
	philos[id].data = data;
	philos[id].last_time_meal = get_current_time();
	philos[id].forks = forks_sem;
	philos[id].death = data->death;
	philos[id].lock_sem = data->lock_s;
	philos[id].limit = data->limit;
	return (0);
}

int	philos_init(t_data *data, t_philo *philos, sem_t *forks_sem)
{
	int	id;

	if (init_sem_data(data) != 0)
		return (1);
	id = 0;
	while (id < data->philos_number)
	{
		if (init_each_philo(data, philos, id, forks_sem) == 1)
			return (1);
		id++;
	}
	return (0);
}

void	close_semaphore(t_data *data)
{
	if (sem_close(data->death) < 0)
		dprintf(2, "error\n");
	if (sem_close(data->print_sem) < 0)
		dprintf(2, "error\n");
	if (sem_close(data->lock_s) < 0)
		dprintf(2, "error\n");
	if (sem_close(data->meals_check) < 0)
		dprintf(2, "error\n");
	if (sem_close(data->limit) < 0)
		dprintf(2, "error\n");
	if (sem_close(data->philos[0].forks) < 0)
		dprintf(2, "error\n");
}

void	destroy_semaphore_and_end_program(t_data *data)
{
	int	id;

	sem_wait(data->death);
	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	sem_unlink("/meals_check");
	sem_unlink("/print_sem");
	sem_unlink("/death");
	sem_unlink("/limit");
	close_semaphore(data);
	id = 0;
	while (id < data->philos_number)
	{
		kill(data->philos[id].philo, SIGTERM);
		id++;
	}
}
