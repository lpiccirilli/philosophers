/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:06:12 by lpicciri          #+#    #+#             */
/*   Updated: 2024/01/22 16:34:09 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	messages("has taken a fork", philo);
	messages("has taken a fork", philo);
	messages("is eating", philo);
	pthread_mutex_lock(&philo->data->time);
	pthread_mutex_lock(&philo->data->monitor);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->monitor);
	pthread_mutex_unlock(&philo->data->time);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages("is sleeping", philo);
	ft_usleep(philo->data->t_sleep);
}

void	*monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	while(philo->finished == 0)
	{
		pthread_mutex_lock(&philo->data->monitor);
		if (get_time() - philo->last_eat >= philo->t_die)
		{
			philo->finished = 1;
			messages("died", philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->monitor);
		if (philo->eat_count >= philo->data->n_eat)
		{
			pthread_mutex_lock(&philo->data->monitor);
			philo->finished = 1;
			pthread_mutex_unlock(&philo->data->monitor);
			return (NULL);
		}
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_create(&philo->monitor_id, NULL, &monitor, philo);
	while (1)
	{
		eat(philo);
		messages("is thinking", philo);
	}
	pthread_join(philo->monitor_id, NULL);
	return (NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&data->time);
		data->start_time = get_time();
		ft_usleep(1);
		if (pthread_create(&data->thread_id[i],
				NULL, &routine, &data->philo[i]))
			return (-1);
		pthread_mutex_unlock(&data->time);
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->thread_id[i], NULL);
	return (0);
}
