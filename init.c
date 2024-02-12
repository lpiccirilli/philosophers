/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:35:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/10 21:45:21 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = (uint64_t)ft_atoi(argv[2]);
	data->t_eat = (uint64_t)ft_atoi(argv[3]);
	data->t_sleep = (uint64_t)ft_atoi(argv[4]);
	data->dead = 0;
	if (argv[5])
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = -1;
	pthread_mutex_init(&data->data, NULL);
	pthread_mutex_init(&data->time, NULL);
}

int	alloc(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while(i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->thread_id = malloc(sizeof(pthread_t) * data->n_philo);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->philo[0].l_fork = &data->forks[0];
	data->philo[0].r_fork = &data->forks[data->n_philo - 1];
	i = 0;
	while (++i < data->n_philo)
	{
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[i - 1];
	}
	return (0);
}

int	init_philo_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].t_die = data->t_die;
		data->philo[i].last_eat = get_time();
		data->philo[i].eating = 0;
		data->philo[i].n_eat = data->n_eat;
		data->philo[i].died = 0;
		i++;
	}
	return (0);
}

int	init(t_data *data, char **argv)
{
	init_data(data, argv);
	if (alloc (data) == -1)
		return (-1);
	if (init_philo_data (data) == -1)
		return (-1);
	if (init_forks (data) == -1)
		return (-1);
	if (data->n_philo == 1)
		return (case_one(data));
	if (init_threads(data) == -1)
		return (-1);
	return (0);
}
