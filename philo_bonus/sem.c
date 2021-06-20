/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 11:21:42 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 12:47:33 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

sem_t	*ft_sem_open(char *name, int value)
{
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char	*ft_sem_name(char *sem_name, char *buffer, int idx)
{
	int	i;

	i = ft_strcpy(buffer, sem_name);
	while (idx > 0)
	{
		buffer[i++] = (idx % 10) + '0';
		idx /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}
