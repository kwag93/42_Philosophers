/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:33:23 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 12:04:24 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_least(void *arg)
{
	t_game	*game;
	int		id;
	int		eat_cnt;

	game = (t_game *)arg;
	eat_cnt = 0;
	while (eat_cnt < game->least_eat_num)
	{
		id = 0;
		while (id < game->philo_num) //모든 철학자가 한번씩 먹을때까지 대기
			sem_wait(game->philosophers[id++].eat_m); //만약 아직 안끝난 철학자가 있으면 거기서 멈추게 된다.
		eat_cnt++;
	}
	print_message(&game->philosophers[0], PHILO_OVER); //philo[0]은 message에서 game에 접근하기 위해 임시로 쓰는거. 실제로 안씀
	sem_post(game->somebody_dead_m);
	return ((void *)0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->starve_time) //죽은 거
		{
			print_message(philo, PHILO_DIED);
			sem_post(philo->mutex);
			sem_post(philo->game->somebody_dead_m);
			return ((void *)0);
		}
		sem_post(philo->mutex);
		usleep(1000); //1ms마다 검사(조건에 10ms 안에 죽은거 처리하게 되어있음)
	}
}

int fork_monitor_thread(t_game *game)
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
