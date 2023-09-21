/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:17:23 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 14:35:31 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo_util(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->philo[i].fork_left, NULL))
			return (clean_exit(ERR_INIT_FORK, data));
		if (pthread_mutex_init(&data->philo[i].lunch_time, NULL))
			return (clean_exit(ERR_INIT_LOCK, data));
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
	}
	i = -1;
	while (++i < data->nb_philo - 1)
		data->philo[i].fork_right = &data->philo[i + 1].fork_left;
	data->philo[i].fork_right = &data->philo[0].fork_left;
	return (0);
}

void	monitoring_util_lock_lunch(t_data *data, int i)
{
	pthread_mutex_lock(&data->philo[i].lunch_time);
	data->eating = time_in_ms() - data->philo[i].last_meal;
	pthread_mutex_unlock(&data->philo[i].lunch_time);
}
