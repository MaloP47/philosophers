/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:05:27 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/18 14:31:07 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	multi_threading(t_data *data)
{
	int			i;

	i = -1;
	data->start_time = time_in_ms();
	while (++i < (int)data->nb_philo)
		pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]);
	if (data->nb_philo > 1)
		pthread_create(&data->servant, NULL, &servant, data);
	i = -1;
	while (++i < (int)data->nb_philo)
		pthread_join(data->tid[i], NULL);
	if (data->nb_philo > 1)
		pthread_join(data->servant, NULL);
	clean_exit(NULL, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (ac == 1)
		return (putstr_errendl(INIT_EXAMPLE), 0);
	if (!check_args(ac, av, &data))
		return (clean_exit(NULL, &data));
	multi_threading(&data);
	return (EXIT_SUCCESS);
}
