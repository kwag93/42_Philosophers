/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:23:37 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 11:43:43 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear(t_game *game)
{
	int i;
	char buffer[50];

	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	sem_unlink(SEMAPHORE_DEADW);
	if (game->philosophers)
	{
		i = 0;
		while (i < game->philo_num)
		{
			ft_sem_name(SEMAPHORE_PHILO, (char*)buffer, i); //철학자가 같은 세마포어를 공유하지 않도록 세마포어 문자열을 일부 수정
			sem_unlink(buffer);
			ft_sem_name(SEMAPHORE_EAT, (char*)buffer, i); //철학자가 같은 세마포어를 공유하지 않도록 세마포어 문자열을 일부 수정
			sem_unlink(buffer);
			i++;
		}
		free(game->philosophers);
	}
	return (1);
}

int		ft_error(char *msg)
{
	ft_putstr_fd(msg, 1);
	return (1);
}
