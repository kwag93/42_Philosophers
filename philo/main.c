/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:47:32 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/16 16:19:46 by bkwag            ###   ########.fr       */
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
			pthread_mutex_lock(&game->philosophers[id++].eat_m); //만약 아직 안끝난 철학자가 있으면 거기서 멈추게 된다.
		eat_cnt++;
	}
	//display_message
	pthread_mutex_unlock(&game->somebody_dead_m);
	return ((void *)0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->is_eating && get_time() > philo->starve_time) //죽은 거
		{
			//display_message
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->game->somebody_dead_m);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000); //1ms마다 검사(조건에 10ms 안에 죽은거 처리하게 되어있음)
	}
	return ((void *)0);
}


void	*routine(void *arg)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)philo;
	philo->last_eat_time = get_time();
	philo->starve_time = philo->last_eat_time + philo->game->ttd;
	if (pthread_create(&tid, NULL, &monitor, arg) != 0)
		return ((void*)1);
}

int start(t_game *game)
{
	pthread_t	tid;
	int 		i;

	if (game->least_eat_num > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_least, (void *)game))
			return (1);
		pthread_detach(tid);
	}
	i = 0;
	while (i < game->philo_num)
	{

		if (pthread_create(&tid, NULL, &routine, (void*)(&game->philosophers[i])))
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}

int	clear(t_game *game)
{
	int i;

	if (game->fork_m)
	{
		i = 0;
		while (i < game->philo_num)
			pthread_mutex_destroy(&game->fork_m[i++]);
		free(game->fork_m);
	}
	if (game->philosophers)
	{
		i = 0;
		while (i < game->philo_num)
		{
			pthread_mutex_destroy(&game->philosophers[i].mutex);
			pthread_mutex_destroy(&game->philosophers[i++].eat_m);
		}
		free(game->philosophers);
	}
	pthread_mutex_destroy(&game->write_m);
	pthread_mutex_destroy(&game->somebody_dead_m);
	return (1);
}


int main(int argc, char *argv[])
{
	t_game game;

	if (argc < 5 || argc > 6)
		return (ft_error("bad argument\n"));
	if (!read_argv(&game, argc, argv))
	{
		clear(&game);
		return (ft_error("init error\n"));
	}
	if (!start(&game))
	{
		clear(&game);
		return (ft_error("wrong action"));
	}
	pthread_mutex_lock(&game.somebody_dead_m); //start가 도는 동안 진행되지 않도록 설정. 이후 lock이 되면 start에서 unlock을 시켜준 것이므로 시뮬 종료.
	pthread_mutex_unlock(&game.somebody_dead_m); //여기서는 진행을 막는 용도로만 쓰기 때문에 lock을 유지할 필요가 없으므로 바로 푼다.
	clear(&game);
	return (0);
}
