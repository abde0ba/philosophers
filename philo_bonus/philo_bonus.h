/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:08:30 by abbaraka          #+#    #+#             */
/*   Updated: 2024/04/25 17:50:17 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

struct s_data;
typedef struct s_data t_data;

// Forward declaration of t_philo to resolve circular dependency
struct s_philo;
typedef struct s_philo t_philo;

typedef struct s_data
{
	int	philos_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	int	finished;
	int	philo_init;
	t_philo	*philos;
	sem_t	*print_sem;
	sem_t	*lock_s;
	sem_t	*meals_check;
}				t_data;

typedef struct s_philo
{
	pid_t		philo;
	int				id;
	sem_t		*forks;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meals_num;
	int				meals_limit;
	int				last_time_meal;
	int				start_time;
	int				eating;
	sem_t	*meals_check;
	sem_t	*print_m;
	sem_t	*lock_sem;
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

int		philos_init(t_data *data, t_philo *philos, sem_t *forks_sem);
int		start(t_data *data, t_philo *philos);
int		get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	print_msg(t_philo *philo, char *msg);

// 		MUTEX UTILS		 //

int		init_sem_data(t_data *data);
int		init_sem_philos(t_philo *philos);
// int		mutex_destroy_philos(t_philo *philos, int id);
int		mutex_destroy_all(t_data *data, t_philo *philos);

// 		ROUTINE UTILS	//

void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

#endif