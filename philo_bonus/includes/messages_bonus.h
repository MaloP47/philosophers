/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:52:49 by mpeulet           #+#    #+#             */
/*   Updated: 2023/09/08 14:01:52 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_BONUS_H
# define MESSAGES_BONUS_H

# define ERR_TIME "\033[0;91mError : time_in_ms!\033[0;39m"

# define INIT_EXAMPLE "\033[0;93m\nInstructions : ./philo [Number of philosopher] \
[Time to die (ms)] [Time to eat (ms)] [Time to sleep (ms)] \
(Optional : [Number of lunch per philosopher])\n\n\033[0;39m\
\033[0;92mExample : ./philo 100 300 200 200 25\n\033[0;39m"

# define NB_ARG "\033[0;91mInvalid number or arguments.\033[0;39m"
# define ARG_FORM "\033[0;91mInvalid input : must be positive intagers.\033[0;39m"

# define NB_PHILO "\033[0;91mWARNING!!! : Too many philos! Quit\n\033[0;39m"
# define MS_LOW "\033[0;91mWARNING!!! Do not test time < 60ms\n\033[0;39m"

#endif