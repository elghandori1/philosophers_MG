/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:34:48 by moel-gha          #+#    #+#             */
/*   Updated: 2024/06/11 09:17:07 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		pthread_mutex_lock(&philos[i].data->last_meal_mutex);
		if ((get_time() - philos[i].last_meal > philos[i].data->time_to_die))
		{
			if (philo_write(&philos[i], "died") == 1)
			{
				pthread_mutex_unlock(&philos[i].data->last_meal_mutex);
				return (1);
			}
			pthread_mutex_lock(&philos[i].data->dead_lock);
			philos[i].data->dead = 1;
			pthread_mutex_unlock(&philos[i].data->dead_lock);
			pthread_mutex_unlock(&philos[i].data->last_meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].data->last_meal_mutex);
		i++;
	}
	return (0);
}

void	eat_times(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		pthread_mutex_lock(&philos[i].data->nb_meals_eaten);
		if (philos[i].data->times_must_eat != -1
			&& philos[i].eating_count >= philos[i].data->times_must_eat)
		{
			pthread_mutex_lock(&philos[i].data->dead_lock);
			philos->eaten++;
			pthread_mutex_unlock(&philos[i].data->dead_lock);
		}
		pthread_mutex_unlock(&philos[i].data->nb_meals_eaten);
		i++;
	}
}

int	ft_monitor(t_philo *philos)
{
	while (1)
	{
		if (check_death(philos) == 1)
			return (1);
		philos->eaten = 0;
		eat_times(philos);
		if (philos->eaten == philos->data->num_philos)
		{
			pthread_mutex_lock(&philos->data->dead_lock);
			philos->data->dead = 1;
			pthread_mutex_unlock(&philos->data->dead_lock);
		}
	}
	return (0);
}
