/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:03:58 by mpeulet           #+#    #+#             */
/*   Updated: 2023/08/15 21:57:17 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>

# include "messages.h"

typedef struct s_philo
{
	int	nb_philo;
	int	ttd;
	int	tte;
	int	tts;
	int	nb_lunch;
}		t_philo;

/* *** init.c *** */

int			struct_init(t_philo *philo);

/* *** parsing.c *** */

int			ft_str_is_digit(char *s);
int			ft_atoi(const char *str);
int			check_args(int ac, char **av, t_philo *philo);

/* *** utils.c *** */

size_t		ft_strlen(const char *s);
void		putstr_errendl(char *s);
int			error_exit(char *s);
uint64_t	time_in_ms(void);

#endif