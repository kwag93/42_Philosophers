/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:33:09 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 11:53:52 by bkwag            ###   ########.fr       */
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
	sem_wait(philo->game->write_m);
	sem_wait(philo->game->dead_write_m); //프로세스가 달라서 game 내 변수로 선언해두면 공유가 안되므로 세마포어를 사용.
	ft_putnbr_fd(get_time() - philo->game->start, 1); //실행 후 지난 시간
	ft_putstr_fd(" ", 1);
	if (type != PHILO_OVER)
		ft_putnbr_fd(philo->idx + 1, 1);
	write(1, get_message(type), ft_strlen(get_message(type)));
	if (!(type == PHILO_DIED || type == PHILO_OVER)) //시뮬레이션이 안 끝난 경우
		sem_post(philo->game->dead_write_m); //뒤에 오는 프로세스들이 출력할 수 있도록 자원 반환(죽은 경우 계속 가지고 있어서 다른 프로세스가 출력을 진행할 수 없다.)
	sem_post(philo->game->write_m);
}

