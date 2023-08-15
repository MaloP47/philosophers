/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:08:27 by mpeulet           #+#    #+#             */
/*   Updated: 2023/08/15 11:03:02 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	putstr_errendl(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

int	error_exit(char *s)
{
	putstr_errendl(s);
	return (1);
}

uint64_t  time_in_ms(void)
{
	struct timeval  tv;
	
	if (gettimeofday(&tv, 0))
		error_exit(ERR_TIME);
	return (((uint64_t)tv.tv_sec * 1000) + ((uint64_t)tv.tv_usec / 1000));
}

int	ft_usleep(__useconds_t microsec)
{
	uint64_t	time_ms;
	
	time_ms = time_in_ms();
	while (time_in_ms() - time_ms < microsec)
		usleep(microsec / 10);
	return (1);
}
