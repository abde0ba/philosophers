/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:30 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/23 08:01:24 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int	philos_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	int	dead;
	int	finished;
	pthread_mutex_t	print_m;
	pthread_mutex_t	lock_m;
	pthread_mutex_t	death_m;
}				t_data;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_num;
	int				meals_limit;
	int				last_time_meal;
	int				start_time;
	int				dead;
	int				eating;
	pthread_mutex_t	eat_m;
	pthread_mutex_t	*death_m;
	pthread_mutex_t	*print_m;
	pthread_mutex_t	lock_m;
	t_data			*data;

}				t_philo;

typedef struct s_mutex
{
	int				num;
	pthread_mutex_t	mutex;
}			t_mutex;

typedef struct s_args
{
	t_philo	philo;
	t_data	data;
	t_mutex	*mutex;
}			t_args;



int		err_args(void);
int		init_data(t_data *data, char **av);
char	*ft_strtrim(char const *s1, char const *set);
int		check_int(char **av);
int		ft_atoi(const char *str);

int		philos_init(t_data *data, t_philo *philos, t_mutex *mutex);
int		start(t_data *data, t_philo *philos);
int		get_current_time(void);
int		ft_usleep(size_t milliseconds);

#endif