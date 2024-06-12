/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:34:45 by moel-gha          #+#    #+#             */
/*   Updated: 2024/06/11 10:40:34 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (philo_write(philo, "has taken a fork") == 1)
		return (pthread_mutex_unlock(philo->l_fork), 1);
	if (philo->data->num_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		return (pthread_mutex_unlock(philo->l_fork), 1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (philo_write(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	if (philo_write(philo, "is eating") == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	return (0);
}

int	philo_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->nb_meals_eaten);
	philo->eating_count++;
	pthread_mutex_unlock(&philo->data->nb_meals_eaten);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo_write(philo, "is sleeping") == 1)
		return (1);
	ft_usleep(philo->data->time_to_sleep);
	if (philo_write(philo, "is thinking") == 1)
		return (1);
	return (0);
}

void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		if ((start_routine(philo) == 1) || philo_check(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
