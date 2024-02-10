/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:06:12 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/08 18:16:23 by lpicciri         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_lock);
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

	philo = (t_philo *)args;
	while(philo->data->dead != 1)
	{
		pthread_mutex_lock(&philo->data->time);
		if (get_time() - philo->last_eat >= philo->t_die)
		{
			pthread_mutex_unlock(&philo->data->time);
			messages("died", philo);
			pthread_mutex_lock(&philo->data->data);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->data);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->time);
	}
	return(NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_create(&philo->monitor_id, NULL, &monitor, philo);
	while(philo->eat_count != philo->n_eat)
	{
		if (philo->data->dead == 1)
		{
			printf("vsr");
			return(NULL);
		}
		pthread_mutex_unlock(&philo->data->data);
		eat(philo);
		messages("is thinking", philo);
	}
	pthread_join(philo->monitor_id, NULL);
	return(NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->n_philo)
	{
		ft_usleep(1);
		if (pthread_create(&data->thread_id[i],
				NULL, &routine, &data->philo[i]))
			return (-1);
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->thread_id[i], NULL);
	return (0);
}
