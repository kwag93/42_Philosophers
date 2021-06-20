/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:47:32 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 12:01:09 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		routine(t_philo *philo)
{
	pthread_t	tid;

	philo->last_eat_time = get_time();
	philo->starve_time = philo->last_eat_time + philo->game->ttd;
	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
		return (1);
	pthread_detach(tid); //monitor 메서드를 분리시킨다.(별도로 감시시키기 위해서)
	while (1)
	{
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		print_message(philo, PHILO_THINK);
	}
	return (0);
}

int		start(t_game *game)
{
	int 		i;

	i = 0;
	game->start = get_time();
	while (i < game->philo_num)
	{
		game->philosophers[i].pid = fork();
		if (game->philosophers[i].pid < 0) //에러 처리
			return (1);
		else if (game->philosophers[i].pid == 0) //자식(철학자 본인)인 경우
			routine(&game->philosophers[i]);
		usleep(100);
		i++;
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_game	game;
	int		i;

	if (argc < 5 || argc > 6)
		return (ft_error("bad argument\n"));
	if (read_argv(&game, argc, argv))
	{
		clear(&game);
		return (ft_error("init error\n"));
	}
	if (fork_monitor_thread(&game) || start(&game))
	{
		clear(&game);
		return (ft_error("wrong action"));
	}
	sem_wait(game.somebody_dead_m);
	i = 0;
	while (i < game.philo_num)
		kill(game.philosophers[i++].pid, SIGKILL); //다음 철학자 프로세스 순차적으로 죽임
	clear(&game);
	return (0);
}
