/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:26:14 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 16:48:57 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (putstr_errendl(NB_ARG), 0);
	while (i < ac)
	{
		if (!ft_str_is_digit(av[i]) || ft_atol(av[i]) == -2147483649)
			return (putstr_errendl(ARG_FORM), 0);
		i++;
	}
	struct_init(ac, av, data);
	return (1);
}

void	warning_limits(t_data *data)
{
	int	i;

	if (data->nb_philo > 200)
	{
		i = -1;
		while (++i < 3)
		{
			write(1, NB_PHILO, ft_strlen(NB_PHILO));
			ft_usleep(data, 3000);
		}
	}
	if ((data->ttd < 60 && data->ttd > 0)
		|| (data->tte < 60 && data->tte > 0)
		|| (data->tts < 60 && data->tts > 0))
	{
		i = -1;
		while (++i < 3)
		{
			write(1, MS_LOW, ft_strlen(MS_LOW));
			ft_usleep(data, 3000);
		}
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
	data->start_time = time_in_ms();
	return (1);
}

void	print_state_change(char *s, t_philo *philo)
{
	uint64_t	time;

	time = time_in_ms() - philo->data->start_time;
	printf(STATE_CHANGE, time, philo->id, s);
}

void	define_printing(t_data *data, t_philo *philo, char *action)
{
	pthread_mutex_lock(&data->write);
	if (philo_died(data))
	{
		pthread_mutex_unlock(&data->write);
		return ;
	}
	print_state_change(action, philo);
	pthread_mutex_unlock(&data->write);
}
