/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_help2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:41:28 by moel-gha          #+#    #+#             */
/*   Updated: 2024/06/12 08:32:49 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	philo_write(t_philo *philo, char *s)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->dead_lock);
	time = get_time() - philo->start_time;
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_lock(&philo->data->show);
	printf("%ld %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->data->show);
	return (0);
}

int	destroy_all(t_data *data, t_philo *philos)
{
	int	i;

	if (data->dead == 1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (pthread_join(philos[i].thread, NULL) != 0)
				return (printf("pthread_join failed\n"), 1);
			i++;
		}
		if (pthread_mutex_destroy(&data->show) != 0)
			printf("Failed to destroy print mutex\n");
		if (pthread_mutex_destroy(&data->last_meal_mutex) != 0)
			printf("Failed to destroy last meal mutex\n");
		if (pthread_mutex_destroy(&data->dead_lock) != 0)
			printf("Failed to destroy dead_lock mutex\n");
		if (pthread_mutex_destroy(&data->nb_meals_eaten) != 0)
			printf("Failed to destroy dead_lock mutex\n");
		free(philos);
		free(data->forks);
		return (1);
	}
	return (0);
}
