/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:50:04 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/16 16:08:30 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000)); //초와 마이크로초를 ms로 변환
}
int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !(s))
		return ;
	write(fd, s, ft_strlen(s));
}

int		ft_error(char *msg)
{
	ft_putstr_fd(msg, 1);
	return (1);
}

int		ft_malloc(void *target, size_t size)
{
	void	**pt;

	pt = (void **)target;
	*pt = malloc(size);
	if (*pt == 0)
		return (0);
	return (1);
}

int		ft_atoi(char *str)
{
	int	i;
	int	start;
	int	is_neg;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	is_neg = (str[i] == '-') ? -1 : 1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	start = i;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * is_neg);
}
