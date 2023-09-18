/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:48:31 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/18 13:37:05 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_died(t_data *data, int dead)
{
	pthread_mutex_lock(&data->lock);
		data->dead_philo = dead;
	pthread_mutex_unlock(&data->lock);
}

int	notify_dead_philo(t_philo *philo)
{
	if ((time_in_ms() - philo->time_left) >= philo->data->ttd)
	{
		philo_died(philo->data, 1);
		define_printing(philo, 1, DIED);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	return (0);
}

int	monitoring_table(t_data *data)
{
	int	i;
	int	turns_reached;

	i = -1;
	turns_reached = 1;
	while (++i < (int)data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i]->lock);
		if (notify_dead_philo(data->philos[i]))
			return (1);
		if (data->nb_lunch != 1)
			if (data->philos[i]->eat_count < data->nb_lunch)
				turns_reached = 0;
		pthread_mutex_unlock(&data->philos[i]->lock);
	}
	if ((int)data->nb_lunch != -1 && turns_reached)
	{
		philo_died(data, 1);
		return (1);
	}
	return (0);
}

void	*servant(void *servant)
{
	t_data	*data;

	data = (t_data *)servant;
	while (1)
	{
		if (monitoring_table(data))
			return (0);
		ft_usleep(1000);
	}
	return (0);
}