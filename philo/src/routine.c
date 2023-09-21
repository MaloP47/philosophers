/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:15:31 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 17:04:42 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_died(t_data *data)
{
	int	died;

	pthread_mutex_lock(&data->one_dead);
	died = data->dead_philo;
	pthread_mutex_unlock(&data->one_dead);
	return (died);
}

int	grab_forks(t_data *data, t_philo *philo)
{
	if (philo->id % 2)
	{
		if (&philo->fork_left == philo->fork_right)
		{
			define_printing(data, philo, FORK_L);
			return (1);
		}
		pthread_mutex_lock(&philo->fork_left);
		define_printing(data, philo, FORK_L);
		pthread_mutex_lock(philo->fork_right);
		define_printing(data, philo, FORK_R);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		define_printing(data, philo, FORK_R);
		pthread_mutex_lock(&philo->fork_left);
		define_printing(data, philo, FORK_L);
	}
	return (0);
}

int	lunch_time(t_data *data, t_philo *philo)
{
	define_printing(data, philo, EATING);
	pthread_mutex_lock(&philo->lunch_time);
	philo->last_meal = time_in_ms();
	pthread_mutex_unlock(&philo->lunch_time);
	ft_usleep(data, data->tte);
	philo->eat_count++;
	if (philo->eat_count == data->nb_lunch)
	{
		pthread_mutex_lock(&data->nb_of_lunch_reached);
		data->philo_has_finish_eating++;
		pthread_mutex_unlock(&data->nb_of_lunch_reached);
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

void	nap_time(t_data *data, t_philo *philo)
{
	define_printing(data, philo, SLEEPING);
	ft_usleep(data, data->tts);
	define_printing(data, philo, THINKING);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	t_data	*data;

	philo = philo_pointer;
	data = philo->data;
	if (philo->id % 2 && data->nb_philo > 1)
		ft_usleep(data, data->tte * 0.25);
	while (!philo_died(data))
	{
		if (data->nb_philo % 2 && philo->eat_count)
			ft_usleep(data, data->ttd * 0.2);
		if (grab_forks(data, philo))
			break ;
		if (lunch_time(data, philo))
			return (0);
		nap_time(data, philo);
	}
	return (0);
}
