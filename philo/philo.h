/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:30 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/03 07:53:29 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_data
{
	int	philos_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
}				t_data;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_num;
}				t_philo;

int		err_args(void);
int		init_data(t_data *data, char **av);
char	*ft_strtrim(char const *s1, char const *set);
int		check_int(char **av);
int		ft_atoi(const char *str);

int		philos_init(t_data data, t_philo *philos);

#endif