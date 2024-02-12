/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:46:57 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/12 19:38:56 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/types.h>
# include <stdbool.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				eat_count;
	int				eating;
	int				n_eat;
	int				died;
	u_int64_t		last_eat;
	u_int64_t		t_die;
	u_int64_t		t_eat;
	u_int64_t		t_sleep;
	pthread_t		monitor_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	eat_lock;
}	t_philo;

typedef struct s_data
{
	int					n_philo;
	u_int64_t			t_die;
	u_int64_t			t_eat;
	u_int64_t			t_sleep;
	u_int64_t			start_time;
	int					n_eat;
	int					died;
	pthread_t			*thread_id;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		data;
	pthread_mutex_t		time;
}	t_data;

int			check_args(int argc, char **argv);
bool		is_in_strings(char c, char *str);
long		ft_atoi(const char *str);
int			init(t_data *data, char **argv);
int			init_threads(t_data *data);
void		init_data(t_data *data, char **argv);
int			alloc(t_data *data);
void		eat(t_philo *philo);
int			ft_usleep(useconds_t time);
u_int64_t	get_time(void);
void		*routine(void *arg);
void		free_data(t_data *data);
void		messages(char *str, t_philo *philo);
int			ft_strcmp(char *s1, char *s2);
int			case_one(t_data *data);
void		*monitor(void *args);

#endif
