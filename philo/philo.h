/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:34:26 by moel-gha          #+#    #+#             */
/*   Updated: 2024/06/11 10:40:39 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	show;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	nb_meals_eaten;
	pthread_mutex_t	last_meal_mutex;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eaten;
	int				eating_count;
	size_t			last_meal;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}					t_philo;

int					is_valid_number(const char *str);
int					pars_params(char **av, int num);
int					ft_initial(t_data *data, char **av, int num);
long				ft_atol(const char *str);
void				ft_putstr_fd(char *s, int fd);
int					ft_isdigit(int digit);
size_t				ft_strlen(const char *theString);
int					init_forks(t_data *data, pthread_mutex_t *forks);
int					initialize_philos(t_philo *philos, t_data *data);
int					start_routine(t_philo *philo);
int					philo_check(t_philo *philo);
void				*routine(void *arg);
int					check_death(t_philo *philos);
void				eat_times(t_philo *philos);
int					ft_monitor(t_philo *philos);
long				get_time(void);
int					philo_write(t_philo *philo, char *s);
int					ft_usleep(size_t milliseconds);
int					destroy_all(t_data *data, t_philo *philos);

#endif
