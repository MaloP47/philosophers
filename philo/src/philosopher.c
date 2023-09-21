/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:07:12 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 16:52:41 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo(t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (putstr_errendl(ERR_MALLOC_PHILOS), 1);
	data->philo = philo;
	init_philo_util(data);
	return (0);
}

int	init_data(t_data *data)
{
	if (pthread_mutex_init(&data->one_dead, NULL))
		return (clean_exit(ERR_INIT_DLOCK, data));
	if (pthread_mutex_init(&data->write, NULL))
		return (clean_exit(ERR_INIT_DWRITE, data));
	if (pthread_mutex_init(&data->nb_of_lunch_reached, NULL))
		return (clean_exit(ERR_INIT_DNBL, data));
	return (0);
}

int	monitoring(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		monitoring_util_lock_lunch(data, i);
		if (data->eating >= data->ttd)
		{
			pthread_mutex_lock(&data->one_dead);
			data->dead_philo = 1;
			pthread_mutex_unlock(&data->one_dead);
			pthread_mutex_lock(&data->write);
			print_state_change(DIED, &data->philo[i]);
			pthread_mutex_unlock(&data->write);
			break ;
		}
		pthread_mutex_lock(&data->nb_of_lunch_reached);
		if (data->philo_has_finish_eating == data->nb_philo)
			return (pthread_mutex_unlock(&data->nb_of_lunch_reached), 0);
		pthread_mutex_unlock(&data->nb_of_lunch_reached);
		if (i == data->nb_philo - 1)
			i = -1;
		usleep(10);
	}
	return (0);
}

int	threading(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].last_meal = data->start_time;
		if (pthread_create(&data->philo[i].philo_tid, NULL,
				routine, &data->philo[i]))
			return (clean_exit(ERR_CREATE_TH, data));
	}
	monitoring(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].philo_tid, NULL))
			return (clean_exit(ERR_JOIN_TH, data));
	}
	return (0);
}

int	philosopher(t_data *data)
{
	if (init_philo(data))
		return (putstr_errendl("init_philo"), 1);
	if (init_data(data))
		return (putstr_errendl("init_data"), 1);
	if (threading(data))
		return (putstr_errendl("threading"), 1);
	clean_exit(NULL, data);
	return (0);
}
