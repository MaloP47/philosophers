/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:51:32 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/18 15:04:49 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	warning_limits(t_data *data)
{
	int	i;

	if (data->nb_philo > 200)
	{
		i = -1;
		while (++i < 3)
		{
			write(1, NB_PHILO, ft_strlen(NB_PHILO));
			ft_usleep(3000);
		}
	}
	if (data->ttd < 60 || data->tte < 60 || data->tts < 60)
	{
		i = -1;
		while (++i < 3)
		{
			write(1, MS_LOW, ft_strlen(MS_LOW));
			ft_usleep(3000);
		}
	}
}

int	alloc_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->tid = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->tid)
		return (clean_exit(ERR_MALLOC_TID, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (clean_exit(ERR_MALLOC_FORKS, data));
	data->philos = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!data->philos)
		return (clean_exit(ERR_MALLOC_PHILOS, data));
	while (++i < (int)data->nb_philo)
	{
		data->philos[i] = malloc(sizeof(t_philo));
		if (!data->philos[i])
			return (clean_exit(ERR_MALLOC_PHILOS, data));
	}
	return (0);
}

void	assign_forks(t_philo *philo)
{
	philo->forks[0] = philo->id;
	philo->forks[1] = philo-> id % philo->data->nb_philo;
	if (philo->id % 2)
	{
		philo->forks[1] = philo->id;
		philo->forks[0] = philo-> id % philo->data->nb_philo;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < (int)data->nb_philo)
	{
		data->philos[i]->data = data;
		data->philos[i]->id = i + 1;
		data->philos[i]->time_left = data->ttd;
		data->philos[i]->eat_count = 0;
		assign_forks(data->philos[i]);
		pthread_mutex_init(&data->philos[i]->lock, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	struct_init(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	if (ac == 6)
		data->nb_lunch = ft_atol(av[5]);
	else
		data->nb_lunch = -1;
	if (data->nb_lunch == 0)
		return (0);
	warning_limits(data);
	if(alloc_init(data))
		return (0);
	init_philos(data);
	return (1);
}

