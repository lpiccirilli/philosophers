/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:06:12 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/01 16:07:36 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->eat_lock);
		if (get_time() - philo->last_eat > philo->t_die)
		{
			pthread_mutex_unlock(&philo->eat_lock);
			messages("died", philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->eat_lock);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	messages("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	messages("has taken a fork", philo);
	messages("is eating", philo);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->eat_lock);
	philo->eat_count++;
	ft_usleep(philo->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	messages("is sleeping", philo);
	ft_usleep(philo->t_sleep);
	messages("is thinking", philo);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_create(&philo->monitor_id, NULL, &monitor, philo);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (philo->eat_count == philo->n_eat || philo->data->died == 1)
		{
			pthread_join(philo->monitor_id, NULL);
			return (NULL);
		}
		eat(philo);
	}
	pthread_join(philo->monitor_id, NULL);
	return (NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->thread_id[i],
				NULL, &routine, &data->philo[i]))
			return (-1);
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->thread_id[i], NULL);
	return (0);
}
