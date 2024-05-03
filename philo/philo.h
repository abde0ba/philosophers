/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:30 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/03 10:46:30 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// #define malloc(x) NULL

typedef struct s_data
{
	int				philos_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				finished;
	pthread_mutex_t	print_m;
	pthread_mutex_t	lock_m;
	pthread_mutex_t	meals_check;
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
	pthread_mutex_t	*meals_check;
	pthread_mutex_t	*print_m;
	pthread_mutex_t	lock_m;
	t_data			*data;

}				t_philo;

typedef struct s_mutex
{
	int				num;
	pthread_mutex_t	mutex;
}			t_mutex;

int		err_args(void);
int		init_data(t_data *data, char **av);
char	*ft_strtrim(char const *s1, char const *set);
int		check_int(char **av);
int		ft_atoi(const char *str);

int		philos_init(t_data *data, t_philo *philos, t_mutex *mutex);
int		start(t_data *data, t_philo *philos);
int		get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	print_msg(t_philo *philo, char *msg);
int		check_negative_data(t_data *data);
int		meals_arg_set(char *arg, t_data *data);

// 		MUTEX UTILS		 //

int		init_mutex_data(t_data *data);
int		init_mutex_philos(t_philo *philos, t_mutex *mutex);
int		mutex_destroy_all(t_data *data, t_philo *philos, int limit);

// 		ROUTINE UTILS	//

void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

#endif