/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:00:39 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 11:54:07 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->game->fork_m);
	print_message(philo, PHILO_FORK);
	sem_wait(philo->game->fork_m);
	print_message(philo, PHILO_FORK);
}

void	put_down_forks(t_philo *philo)
{
	print_message(philo, PHILO_SLEEP);
	sem_post(philo->game->fork_m);
	sem_post(philo->game->fork_m);
	usleep(philo->game->tts * 1000);
}
