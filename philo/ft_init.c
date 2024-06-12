/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:34:32 by moel-gha          #+#    #+#             */
/*   Updated: 2024/06/12 08:20:27 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (printf("mutex_init failed\n"), 1);
	if (pthread_mutex_init(&data->show, NULL) != 0)
		return (printf("Mutex Init Failed\n"), 1);
	if (pthread_mutex_init(&data->nb_meals_eaten, NULL) != 0)
		return (printf("Mutex Init Failed\n"), 1);
	if (pthread_mutex_init(&data->last_meal_mutex, NULL) != 0)
		return (printf("Mutex Init Failed\n"), 1);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (printf("Mutex Init Failed\n"), 1);
		i++;
	}
	return (0);
}

int	initialize_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = get_time();
		philos[i].data = data;
		philos[i].eating_count = 0;
		if (philos[i].id % 2)
		{
			philos[i].l_fork = &data->forks[i];
			philos[i].r_fork = &data->forks[(i + 1) % data->num_philos];
		}
		else
		{
			philos[i].r_fork = &data->forks[i];
			philos[i].l_fork = &data->forks[(i + 1) % data->num_philos];
		}
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (ft_putstr_fd("pthread_create failed\n", 2), 1);
		i++;
	}
	return (0);
}
