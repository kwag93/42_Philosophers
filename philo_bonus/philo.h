/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 12:56:19 by bkwag             #+#    #+#             */
/*   Updated: 2021/06/20 12:56:30 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

# define PHILO_EAT		0
# define PHILO_SLEEP	1
# define PHILO_FORK		2
# define PHILO_THINK	3
# define PHILO_DIED		4
# define PHILO_OVER		5

# define SEMAPHORE_FORK		"semFork"
# define SEMAPHORE_WRITE	"semWrite"
# define SEMAPHORE_DEAD		"semDead"
# define SEMAPHORE_DEADW	"semDeadWrite"
# define SEMAPHORE_PHILO	"semPhilo"
# define SEMAPHORE_EAT		"semEat"

struct s_game;

typedef struct			s_philo
{
	int					idx;
	pid_t				pid;
	uint64_t			last_eat_time;
	uint64_t			starve_time;// ms 값이 커져서 int를 넘어갈 수 있기때문에 uint를 사용중
	int					is_eating;//bonus에서 각 철학자가 죽었는지 체크하기 위함
	int					eat_cnt;
	struct s_game		*game;
	sem_t				*mutex;
	sem_t				*eat_m;//least_eat_num이 입력되었을 때 한바퀴씩 전체 철학자가 다 먹을때까지 기다리게 하기 위한 뮤텍스
}						t_philo;

typedef struct			s_game
{
	int					philo_num;
	uint64_t			ttd;
	uint64_t			tte;
	uint64_t			tts;
	int					least_eat_num;
	int					dead;
	uint64_t			start;
	t_philo				*philosophers;
	sem_t				*somebody_dead_m;
	sem_t				*write_m;
	sem_t				*dead_write_m;
	sem_t				*fork_m;
}						t_game;

int			ft_strlen(char *str);
int			ft_error(char *msg);
int			ft_atoi(char *str);
void		ft_putstr_fd(char *s, int fd);
int			ft_malloc(void *target, size_t size);
int			init_philosophers(t_game *game);
int			init_semaphores(t_game *game);
int			read_argv(t_game *game, int argc, char **argv);
uint64_t	get_time(void);
void		ft_putnbr_fd(uint64_t n, int fd);
void		print_message(t_philo *philo, int type);
int			clear(t_game *game);
void		take_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		eat(t_philo *philo);
sem_t		*ft_sem_open(char *name, int value);
char		*ft_sem_name(char *sem_name, char *buffer, int idx);
void		*monitor_least(void *arg);
void		*monitor(void *arg);
int			fork_monitor_thread(t_game *game);

#endif
