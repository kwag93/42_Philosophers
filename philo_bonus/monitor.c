/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:33:23 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/28 14:46:34 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*monitor_least(void *arg)
{
	t_game	*game;
	int		id;
	int		eat_cnt;

	game = (t_game *)arg;
	eat_cnt = 0;
	while (eat_cnt < game->least_eat_num)
	{
		id = 0;
		while (id < game->philo_num)
			sem_wait(game->philosophers[id++].eat_m);
		eat_cnt++;
	}
	print_message(&game->philosophers[0], PHILO_OVER);
	sem_post(game->somebody_dead_m);
	return ((void *)0);
}

void		*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->starve_time)
		{
			print_message(philo, PHILO_DIED);
			sem_post(philo->mutex);
			sem_post(philo->game->somebody_dead_m);
			return ((void *)0);
		}
		sem_post(philo->mutex);
		usleep(900);
	}
}

int			fork_monitor_thread(t_game *game)
{
	pthread_t	tid;

	if (game->least_eat_num > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_least, (void*)game) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}
