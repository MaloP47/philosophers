/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:05:27 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/21 14:04:16 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	static t_data	data = {0};

	if (ac == 1)
		return (putstr_errendl(INIT_EXAMPLE), EXIT_FAILURE);
	if (!check_args(ac, av, &data))
		return (EXIT_FAILURE);
	if (philosopher(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
