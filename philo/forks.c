/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:00:39 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/28 14:34:46 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->fork_m[philo->lfork]);
	print_message(philo, PHILO_FORK);
	pthread_mutex_lock(&philo->game->fork_m[philo->rfork]);
	print_message(philo, PHILO_FORK);
}

void	put_down_forks(t_philo *philo)
{
	print_message(philo, PHILO_SLEEP);
	pthread_mutex_unlock(&philo->game->fork_m[philo->lfork]);
	pthread_mutex_unlock(&philo->game->fork_m[philo->rfork]);
	delay_time(philo->game->tts);
}
