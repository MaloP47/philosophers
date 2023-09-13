/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:51:32 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/13 10:30:19 by mpeulet          ###   ########.fr       */
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
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->tid = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->tid)
		return (clean_exit(ERR_MALLOC_TID, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (clean_exit(ERR_MALLOC_FORKS, data));
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (clean_exit(ERR_MALLOC_PHILOS, data));
	return (0);
}

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (int)data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos[0].left_fork = &data->forks[0];
	data->philos[0].right_fork = &data->forks[data->nb_philo - 1];
	i = 1;
	while (i < (int)data->nb_philo)
	{
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[i - 1];
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < (int)data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_left = data->ttd;
		data->philos[i].eat_count = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
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
	warning_limits(data);
	if(alloc_init(data))
		return (0);
	init_forks(data);
	init_philos(data);
	return (1);
}

int	check_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	memset(data, 0, sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (putstr_errendl(NB_ARG), 0);
	while (i < ac)
	{
		if (!ft_str_is_digit(av[i]) || ft_atol(av[i]) == -2147483649)
			return (putstr_errendl(ARG_FORM), 0);
		i++;
	}
	if (!struct_init(ac, av, data))
		return (0);
	return (1);
}
