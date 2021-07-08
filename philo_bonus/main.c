/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:47:32 by bkwag             #+#    #+#             */
/*   Updated: 2021/07/08 10:39:54 by bkwag            ###   ########.fr       */
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
	pthread_detach(tid);
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
	int		i;

	i = 0;
	game->start = get_time();
	while (i < game->philo_num)
	{
		game->philosophers[i].pid = fork();
		if (game->philosophers[i].pid < 0)
			return (1);
		else if (game->philosophers[i].pid == 0)
			routine(&game->philosophers[i]);
		usleep(100);
		i++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_game	game;
	int		i;
	int		ret;

	if (argc < 5 || argc > 6)
		return (ft_error("bad argument\n"));
	if ((ret = read_argv(&game, argc, argv)))
	{
		if (ret != 2)
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
		kill(game.philosophers[i++].pid, SIGKILL);
	clear(&game);
	return (0);
}
