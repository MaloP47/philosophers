/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:51:32 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/11 15:09:26 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_str_is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= 48 && s[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	if (!str)
		return (0);
	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i++] == 45)
			sign *= -1;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		nb = (nb * 10) + (str[i] - 48);
		if (nb * sign > INT_MAX || nb * sign < INT_MIN)
			return (-2147483649);
		i++;
	}
	return (nb * sign);
}

void	warning_limits(t_data *data)
{
	if (data->nb_philo > 200)
	{
		write(1, NB_PHILO, ft_strlen(NB_PHILO));
		ft_usleep(6000);
	}
	if (data->ttd < 60 || data->tte < 60 || data->tts < 60)
	{
		write(1, MS_LOW, ft_strlen(MS_LOW));
		ft_usleep(6000);
	}
}

int	check_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	struct_init(data);
	if (ac < 5 || ac > 6)
		return (error_exit(NB_ARG), 0);
	while (i < ac)
	{
		if (!ft_str_is_digit(av[i]) || ft_atol(av[i]) == -2147483649)
			return (error_exit(ARG_FORM), 0);
		i++;
	}
	data->nb_philo = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	if (ac == 6)
		data->nb_lunch = ft_atol(av[5]);
	warning_limits(data);
	return (1);
}
