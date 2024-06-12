/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:34:35 by moel-gha          #+#    #+#             */
/*   Updated: 2024/06/10 18:59:16 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd("Number of params is not correct!\n", 2);
		return (1);
	}
	if (ft_initial(&data, av, ac))
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * data.num_philos);
	philos = malloc(sizeof(t_philo) * data.num_philos);
	if (forks == NULL || philos == NULL)
		return (free(forks), free(philos), 1);
	if (init_forks(&data, forks) == 1)
		return (1);
	data.forks = forks;
	if (initialize_philos(philos, &data) == 1)
		return (free(forks), free(philos), 1);
	ft_monitor(philos);
	destroy_all(&data, philos);
	return (0);
}
