#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

struct s_philo;

typedef struct	s_game
{
	struct			timeval tv;
	int				philo_num;
	int				ttd;
	int				tte;
	int				tts;
	int				least_eat_num;
	struct s_philo	*philosophers;
	pthread_mutex_t somebody_dead_m;
	pthread_mutex_t write_m;
	pthread_mutex_t *fork_m;
}				t_game;

typedef struct			s_philo
{
	int					idx;
	uint64_t			last_eat_time;
	uint64_t			starve_time; // ms 값이 커져서 int를 넘어갈 수 있기때문에 uint를 사용중
	int					is_eating; //bonus에서 각 철학자가 죽었는지 체크하기 위함
	int					eat_cnt;
	int					lfork;
	int					rfork;
	t_game				*game;
	pthread_mutex_t		mutex;
	pthread_mutex_t		eat_m; //least_eat_num이 입력되었을 때 한바퀴씩 전체 철학자가 다 먹을때까지 기다리게 하기 위한 뮤텍스
}						t_philo;

int			ft_error(char *msg);
int			ft_atoi(char *str);
void		ft_putstr_fd(char *s, int fd);
int			ft_malloc(void *target, size_t size);
void		init_philosophers(t_game *game);
int			init_mutexes(t_game *game);
int			read_argv(t_game *game, int argc, char *argv[]);
uint64_t	get_time(void);

#endif
