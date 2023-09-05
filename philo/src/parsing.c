/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:51:32 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/05 14:54:44 by mpeulet          ###   ########.fr       */
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

int	ft_atoi(const char *str)
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

int	check_args(int ac, char **av, t_philo *philo)
{
	int	i;

	i = 1;
	struct_init(philo);
	if (ac < 5 || ac > 6)
		return (error_exit(NB_ARG), 0);
	while (i < ac)
	{
		if (!ft_str_is_digit(av[i]) || ft_atoi(av[i]) == -2147483649);
			return (error_exit(ARG_FORM), 0);
		i++;
	}
	philo->nb_philo = ft_atoi(av[1]);
	philo->ttd = ft_atoi(av[2]);
	philo->tte = ft_atoi(av[3]);
	philo->tts = ft_atoi(av[4]);
	if (ac == 6)
		philo->nb_lunch = ft_atoi(av[5]);
	return (1);
}
