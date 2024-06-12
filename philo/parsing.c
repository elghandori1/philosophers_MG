/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <moel-gha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:34:41 by moel-gha          #+#    #+#             */
/*   Updated: 2024/06/10 18:06:07 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(const char *str)
{
	if (*str == '+' || *str == '-')
	{
		if (*(str + 1) == '\0')
			return (0);
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	pars_params(char **av, int num)
{
	int	i;

	i = 1;
	while (i < num)
	{
		if ((*av[i] == '\0') || !is_valid_number(av[i]) || ft_atol(av[i]) < 0
			|| ft_atol(av[i]) >= INT_MAX)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_initial(t_data *data, char **av, int num)
{
	if (pars_params(av, num))
	{
		ft_putstr_fd("Invalid Argument\n", 2);
		return (1);
	}
	data->num_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->times_must_eat = ft_atol(av[5]);
	else
		data->times_must_eat = -1;
	if (data->num_philos == 0 || data->times_must_eat == 0)
		return (1);
	return (0);
}
