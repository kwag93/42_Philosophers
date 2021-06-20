/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:33:09 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 13:11:56 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_message(int type)
{
	if (type == PHILO_EAT)
		return (" is eating\n");
	else if (type == PHILO_SLEEP)
		return (" is sleeping\n");
	else if (type == PHILO_FORK)
		return (" takes a fork\n");
	else if (type == PHILO_THINK)
		return (" is thinking\n");
	else if (type == PHILO_OVER)
		return ("least eat count reached\n");
	else
		return (" died\n");
}

void	print_message(t_philo *philo, int type)
{
	pthread_mutex_lock(&philo->game->write_m);
	if (!philo->game->dead)
	{
		ft_putnbr_fd(get_time() - philo->game->start, 1);
		ft_putstr_fd(" ", 1);
		if (type != PHILO_OVER)
			ft_putnbr_fd(philo->idx + 1, 1);
		if (type == PHILO_DIED || type == PHILO_OVER)
			philo->game->dead = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
	}
	pthread_mutex_unlock(&philo->game->write_m);
}
