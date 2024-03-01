/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:50:34 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/01 13:58:50 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ciao(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->data->start_time = get_time();
	messages ("has taken a fork", philo);
	ft_usleep(philo->t_die);
	printf("%llu %d died\n", philo->t_die, philo->id);
	return (NULL);
}

int	case_one(t_data *data)
{
	pthread_t	one;

	data->start_time = get_time();
	if (pthread_create(&one, NULL, &ciao, &data->philo[0]))
		return (-1);
	pthread_join(one, NULL);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].eat_lock);
		i++;
	}
	pthread_mutex_destroy(&data->died_lock);
	free(data->forks);
	free(data->thread_id);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == -1)
		return (write(1, "Error: wrong arguments\n", 24));
	if (init(&data, argv) == -1)
		return (printf("Error: init_data\n"));
	free_data(&data);
	return (0);
}
