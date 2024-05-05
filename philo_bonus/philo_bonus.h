/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:56:19 by abbaraka          #+#    #+#             */
/*   Updated: 2024/05/05 15:00:41 by abbaraka         ###   ########.fr       */
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

struct					s_data;
typedef struct s_data	t_data;

struct					s_philo;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int		philos_number;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_meals;
	int		finished;
	int		philo_init;
	t_philo	*philos;
	sem_t	*print_sem;
	sem_t	*lock_s;
	sem_t	*meals_check;
	sem_t	*death;
	sem_t	*limit;
}				t_data;

typedef struct s_philo
{
	pthread_t	thread;
	pid_t		philo;
	int			id;
	sem_t		*forks;
	int			time_to_eat;
	int			time_to_sleep;
	size_t		time_to_die;
	int			meals_num;
	int			meals_limit;
	size_t		last_time_meal;
	size_t		start_time;
	int			eating;
	sem_t		*meals_check;
	sem_t		*print_m;
	sem_t		*lock_sem;
	sem_t		*death;
	sem_t		*limit;
	t_data		*data;
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

int		philos_init(t_data *data, t_philo *philos, sem_t *forks_sem);
int		start(t_data *data, t_philo *philos);
size_t	get_current_time(void);
size_t	ft_usleep(size_t milliseconds);
void	print_msg(t_philo *philo, char *msg);
int		meals_arg_set(char *arg, t_data *data);
int		check_negative_data(t_data *data);

// 		SEMAPHORE UTILS		 //
int		init_sem_data(t_data *data);
void	destroy_semaphore_and_end_program(t_data *data);
void	close_semaphore(t_data *data);
void	unlink_semaphore_data(void);
// 		ROUTINE UTILS	//

void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

#endif