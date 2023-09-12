/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:03:58 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/12 16:27:55 by mpeulet          ###   ########.fr       */
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
# include <limits.h>
# include <string.h>

# include "messages.h"

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data			*data;
	
	pthread_t		philo_tid;
	
	unsigned int	id;
	unsigned int	eat_count;

	uint64_t		time_left;

	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

}		t_philo;

typedef struct s_data
{
	pthread_t		*tid;

	unsigned int	nb_philo;
	int				nb_lunch;

	t_philo			*philos;

	uint64_t		start_time;
	uint64_t		ttd;
	uint64_t		tte;
	uint64_t		tts;

	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	
	pthread_t		monitor;
}		t_data;

/* *** parsing.c *** */

int			struct_init(int ac, char **av, t_data *data);
void		warning_limits(t_data *data);
int			check_args(int ac, char **av, t_data *main);

/* *** utils.c *** */

size_t		ft_strlen(const char *s);
int			ft_str_is_digit(char *s);
long		ft_atol(char *str);
void		free_all(t_data *data);
void		destroy_mutex(t_data *data);
void		putstr_errendl(char *s);
int			clean_exit(char *s, t_data *data);
void		*ft_memset(void *s, int c, size_t n);
uint64_t	time_in_ms(void);
int			ft_usleep(__useconds_t microsec);

#endif